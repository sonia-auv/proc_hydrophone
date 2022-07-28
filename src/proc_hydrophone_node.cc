/**
 * \file	proc_hydrophone_node.cc
 * \author	Marc-Antoine Couture <coumarc9@outlook.com>
 * \date	07/16/2017
 *
 * \copyright Copyright (c) 2017 S.O.N.I.A. All rights reserved.
 *
 * \section LICENSE
 *
 * This file is part of S.O.N.I.A. software.
 *
 * S.O.N.I.A. software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * S.O.N.I.A. software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with S.O.N.I.A. software. If not, see <http://www.gnu.org/licenses/>.
 */

#include <filter_strategy/CompositeFilter.h>
#include <filter_strategy/SNRFilter.h>
#include <filter_strategy/phaseDiff.h>
#include "proc_hydrophone_node.h"

namespace proc_hydrophone {

    //==============================================================================
    // C / D T O R S   S E C T I O N

    //------------------------------------------------------------------------------
    //
    ProcHydrophoneNode::ProcHydrophoneNode(const ros::NodeHandlePtr &nh)
        : nh_(nh),
          configuration_(nh)
    {
        // Subscriber
        providerHydrophoneSubscriber_ = nh_->subscribe("/provider_hydrophone/ping", 100, &ProcHydrophoneNode::PingCallback, this);

        // Publishers
        pingAnglesPublisher_ = nh_->advertise<sonia_common::PingAngles>("/proc_hydrophone/ping", 100);

        // Filtering strategies
        std::shared_ptr<IFilterStrategy> snrFilter(new SNRFilter(configuration_.getSNRFilter()));
        std::shared_ptr<IFilterStrategy> maxAngleDiff(new phaseDiff(configuration_.getMaxAngle()));

        // Add pre-filtering strategies to the filter list
        std::shared_ptr<std::vector<std::shared_ptr<IFilterStrategy>>> prefilters(new std::vector<std::shared_ptr<IFilterStrategy>>);
        prefilters->push_back(snrFilter);
        prefilters->push_back(maxAngleDiff);

        // Create a Composite filter (cycles through all filters)
        std::shared_ptr<IFilterStrategy> prefilterStrategy(new CompositeFilter(prefilters));
        prefilterStrategy_ = prefilterStrategy;
    }

    //------------------------------------------------------------------------------
    //
    ProcHydrophoneNode::~ProcHydrophoneNode() {}

    //==============================================================================
    // M E T H O D   S E C T I O N
    //------------------------------------------------------------------------------
    //
    void ProcHydrophoneNode::Spin()
    {
        ros::Rate r(15);  // 15 hz
        
        while (ros::ok()) 
        {
            ros::spinOnce();
            r.sleep();
        }
    }

    void ProcHydrophoneNode::PingCallback(const sonia_common::PingMsgConstPtr &ping) 
    {
        std::vector<sonia_common::PingMsgConstPtr> newping;
        sonia_common::PingAngles outping = sonia_common::PingAngles();
        sonia_common::PingAngles secondfilterping = sonia_common::PingAngles();
        
        ROS_DEBUG_STREAM("Pre-Filtering received ping");

        newping.push_back(ping);
        std::vector<sonia_common::PingMsgConstPtr> prefilteredPing = prefilterStrategy_->Process(newping);

        if(!prefilteredPing.empty())
        {
            ROS_DEBUG_STREAM("Received Ping is correct");
            
            DOAAlgorithm *doa = new DOAAlgorithm(configuration_.getAbsoluteElevation());

            doa->setValues(prefilteredPing.front()->phaseRef, prefilteredPing.front()->phase1, prefilteredPing.front()->phase2,
                            prefilteredPing.front()->phase3, prefilteredPing.front()->frequency, prefilteredPing.front()->debug);

            doa->compute();
            
            outping.header = prefilteredPing.front()->header;
            outping.heading = doa->getHeading();
            outping.elevation = doa->getElevation();
            outping.frequency = doa->getFrequency();
            outping.snr = doa->getSnr();

            elevationCheck *check = new elevationCheck(configuration_.getMaxAngle(), configuration_.getAbsoluteElevation());

            secondfilterping = check->Process(outping);
            
            pingAnglesPublisher_.publish(secondfilterping);

            delete doa;
        }
    }

}  // namespace proc_hydrophone
