/**
 * \file	Configuration.cc
 * \author	Coumarc9
 * \date	24/07/2017
 * 
 * \copyright Copyright (c) 2021 S.O.N.I.A. All rights reserved.
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

#include "Configuration.h"

namespace proc_hydrophone
{
    Configuration::Configuration(const ros::NodeHandlePtr &nh)
        : nh(nh),
          absoluteElevation(true),
          flipElevation(false),
          removeElevation(true),
          SNRfilter(10),
          maxDiffAngle(1.57079632679),
          elevationAngle(1.57079632679)
    {
        Deserialize();
    }

    Configuration::~Configuration() {}

    void Configuration::Deserialize() {

        ROS_INFO("Deserialize params");

        FindParameter("/algorithm/absoluteElevation", absoluteElevation);
        FindParameter("/filters/SNR", SNRfilter);
        FindParameter("/filters/maxDiffAngle", maxDiffAngle);
        FindParameter("/filters/elevationAngle", elevationAngle);
        FindParameter("/filters/flipElevation", flipElevation);
        FindParameter("/filters/removeElevation", removeElevation);
        FindParameter("/filters/minAngle", minAngle);
        FindParameter("/filters/maxAngle", maxAngle);

        ROS_INFO("End deserialize params");
    }

    template <typename TType>
    void Configuration::FindParameter(const std::string &paramName, TType &attribute) {
        if (nh->hasParam("/proc_hydrophone" + paramName)) {
            nh->getParam("/proc_hydrophone" + paramName, attribute);
        } else {
            ROS_WARN_STREAM("Did not find /proc_hydrophone" + paramName
                                    << ". Using default.");
        }
    }
}