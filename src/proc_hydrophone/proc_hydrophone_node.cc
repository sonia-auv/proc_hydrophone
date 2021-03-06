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

#include <proc_hydrophone/filter_strategy/CompositeFilter.h>
#include <proc_hydrophone/ping_merge_strategy/MeanMergeStrategy.h>
#include <proc_hydrophone/filter_strategy/KeepFirstPingFilter.h>
#include <proc_hydrophone/filter_strategy/ElevationNaNFilter.h>
#include <proc_hydrophone/filter_strategy/AmplitudeFilter.h>
#include <proc_hydrophone/filter_strategy/RatioAmpNoiseFilter.h>
#include "proc_hydrophone/proc_hydrophone_node.h"

namespace proc_hydrophone {

    //==============================================================================
    // C / D T O R S   S E C T I O N

    //------------------------------------------------------------------------------
    //
    ProcHydrophoneNode::ProcHydrophoneNode(const ros::NodeHandlePtr &nh)
        : nh_(nh),
          configuration(new Configuration()),
          pingPosePublisher(nh_->advertise<sonia_common::PingPose>("/proc_hydrophone/ping", 100))
    {

        std::shared_ptr<IFilterStrategy> keepFirstPingFilter(new KeepFirstPingFilter());
        std::shared_ptr<IFilterStrategy> elevationNaNFilter(new ElevationNaNFilter());
        std::shared_ptr<IFilterStrategy> amplitudeFilter(new AmplitudeFilter(20000000, 375000));
        std::shared_ptr<IFilterStrategy> ratioAmpNoiseFilter(new RatioAmpNoiseFilter(10, 8));

        std::shared_ptr<std::vector<std::shared_ptr<IFilterStrategy>>> filters(new std::vector<std::shared_ptr<IFilterStrategy>>);
        filters->push_back(keepFirstPingFilter);
        filters->push_back(amplitudeFilter);
        //filters->push_back(ratioAmpNoiseFilter);
        filters->push_back(elevationNaNFilter);

        std::shared_ptr<IFilterStrategy> filterStrategy(new CompositeFilter(filters));

        ping25kHzHandler_ = std::shared_ptr<PingHandler>(new PingHandler(25, filterStrategy, std::shared_ptr<IPingMergeStrategy>(new MeanMergeStrategy()), configuration, pingPosePublisher));
        ping30kHzHandler_ = std::shared_ptr<PingHandler>(new PingHandler(30, filterStrategy, std::shared_ptr<IPingMergeStrategy>(new MeanMergeStrategy()), configuration, pingPosePublisher));
        ping35kHzHandler_ = std::shared_ptr<PingHandler>(new PingHandler(35, filterStrategy, std::shared_ptr<IPingMergeStrategy>(new MeanMergeStrategy()), configuration, pingPosePublisher));
        ping40kHzHandler_ = std::shared_ptr<PingHandler>(new PingHandler(40, filterStrategy, std::shared_ptr<IPingMergeStrategy>(new MeanMergeStrategy()), configuration, pingPosePublisher));

        odomSubscriber = nh_->subscribe("/proc_navigation/odom", 100, &ProcHydrophoneNode::OdomCallback, this);
        providerHydrophoneSubscriber = nh_->subscribe("/provider_hydrophone/ping", 100, &ProcHydrophoneNode::PingCallback, this);
    }

    //------------------------------------------------------------------------------
    //
    ProcHydrophoneNode::~ProcHydrophoneNode() {}

    //==============================================================================
    // M E T H O D   S E C T I O N
    //------------------------------------------------------------------------------
    //
    void ProcHydrophoneNode::Spin() {

      ros::Rate r(15);  // 15 hz
      while (ros::ok()) {
        ros::spinOnce();
        r.sleep();
      }
    }

    void ProcHydrophoneNode::OdomCallback(const nav_msgs::OdometryConstPtr &odom) {
        // Simply save the last odom msg
        this->configuration->setOdometry(odom);
    }

    void ProcHydrophoneNode::PingCallback(const sonia_common::PingMsgConstPtr &ping) {


        if (ping->frequency >= 39 && ping->frequency <= 41)
        {
            ping40kHzHandler_->AddPing(ping);
        }
        else if (ping->frequency >= 34 && ping->frequency <= 36)
        {
            ping35kHzHandler_->AddPing(ping);
        }
        else if (ping->frequency >= 29 && ping->frequency <= 31)
        {
            ping30kHzHandler_->AddPing(ping);
        }
        else if (ping->frequency >= 24 && ping->frequency <= 26)
        {
            ping25kHzHandler_->AddPing(ping);
        }

    }

}  // namespace proc_hydrophone
