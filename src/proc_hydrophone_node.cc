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
#include <filter_strategy/NegativeZFilter.h>
#include <filter_strategy/VectorNormFilter.h>
#include "proc_hydrophone_node.h"

namespace proc_hydrophone {

    //==============================================================================
    // C / D T O R S   S E C T I O N

    //------------------------------------------------------------------------------
    //
    ProcHydrophoneNode::ProcHydrophoneNode(const ros::NodeHandlePtr &nh)
        : nh_(nh)
    {

        // Subscriber
        providerHydrophoneSubscriber = nh_->subscribe("/provider_hydrophone/ping", 100, &ProcHydrophoneNode::PingCallback, this);

        // Publishers
        pingPosePublisher = nh_->advertise<sonia_common::PingMsg>("/proc_hydrophone/ping", 100);

        // Filtering strategies
        std::shared_ptr<IFilterStrategy> negativeZFilter(new NegativeZFilter());
        std::shared_ptr<IFilterStrategy> vectorNormFilter(new VectorNormFilter(500));
        // std::shared_ptr<IFilterStrategy> keepFirstPingFilter(new KeepFirstPingFilter());
        // std::shared_ptr<IFilterStrategy> elevationNaNFilter(new ElevationNaNFilter());
        // std::shared_ptr<IFilterStrategy> amplitudeFilter(new AmplitudeFilter(20000000, 375000));
        // std::shared_ptr<IFilterStrategy> ratioAmpNoiseFilter(new RatioAmpNoiseFilter(10, 8));

        std::shared_ptr<std::vector<std::shared_ptr<IFilterStrategy>>> filters(new std::vector<std::shared_ptr<IFilterStrategy>>);
        filters->push_back(negativeZFilter);
        filters->push_back(vectorNormFilter);
        //filters->push_back(keepFirstPingFilter);
        //filters->push_back(elevationNaNFilter);
        //filters->push_back(amplitudeFilter);
        //filters->push_back(ratioAmpNoiseFilter);

        std::shared_ptr<IFilterStrategy> filterStrategy(new CompositeFilter(filters));

        pingHandler = std::shared_ptr<PingHandler>(new PingHandler(filterStrategy, pingPosePublisher));

        // ping25kHzHandler_ = std::shared_ptr<PingHandler>(new PingHandler(25, filterStrategy, std::shared_ptr<IPingMergeStrategy>(new MeanMergeStrategy()), configuration, pingPosePublisher));
        // ping30kHzHandler_ = std::shared_ptr<PingHandler>(new PingHandler(30, filterStrategy, std::shared_ptr<IPingMergeStrategy>(new MeanMergeStrategy()), configuration, pingPosePublisher));
        // ping35kHzHandler_ = std::shared_ptr<PingHandler>(new PingHandler(35, filterStrategy, std::shared_ptr<IPingMergeStrategy>(new MeanMergeStrategy()), configuration, pingPosePublisher));
        // ping40kHzHandler_ = std::shared_ptr<PingHandler>(new PingHandler(40, filterStrategy, std::shared_ptr<IPingMergeStrategy>(new MeanMergeStrategy()), configuration, pingPosePublisher));        
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
        pingHandler->AddPing(ping);
    }

}  // namespace proc_hydrophone
