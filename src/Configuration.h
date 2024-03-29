/**
 * \file	Configuration.h
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

#ifndef INTERFACE_CONFIGURATION_H
#define INTERFACE_CONFIGURATION_H

#include <cstdint>
#include <cmath>
#include <ros/ros.h>

namespace proc_hydrophone
{
    class Configuration {

    public:

        Configuration(const ros::NodeHandlePtr &nh);
        ~Configuration();

        bool getAbsoluteElevation() const {return absoluteElevation;}
        int getSNRFilter() const {return SNRfilter;}
        double getMaxDiffAngle() const {return maxDiffAngle;}
        double getElevationAngle() const {return elevationAngle;}
        bool getFlipElevation() const {return flipElevation;}
        bool getRemoveElevation() const {return removeElevation;}
        double getMinAngle() const {return minAngle;}
        double getMaxAngle() const {return maxAngle;}

    private:

        ros::NodeHandlePtr nh;

        bool absoluteElevation;
        int SNRfilter;
        double maxDiffAngle;
        double elevationAngle;
        bool flipElevation;
        bool removeElevation;
        double minAngle;
        double maxAngle;

        void Deserialize();
        void SetParameter();

        template <typename TType>
        void FindParameter(const std::string &paramName, TType &attribute);
    };
}

#endif //INTERFACE_CONFIGURATION_H