/**
 * \file	elevationCheck.cc
 * \author	Francis Alonzo <francisalonzo@gmail.com>
 * \date	23/07/2022
 *
 * \copyright Copyright (c) 2022 S.O.N.I.A. All rights reserved.
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
#include "elevationCheck.h"

namespace proc_hydrophone
{
    elevationCheck::elevationCheck(double angle, bool keepElevation)
        : angle(angle),
          keepElevation(keepElevation)
    {   
    }

    elevationCheck::~elevationCheck()
    {

    }

    sonia_common::PingAnglesPtr elevationCheck::Process(sonia_common::PingAnglesPtr pings)
    {
        sonia_common::PingAnglesPtr filteredpings;

        if(pings.empty()) return pings;

        double_t heading = pings->heading;
        double_t elevation = pings->elevation;

        if(elevation >= angle)
        {
            ROS_DEBUG_STREAM("Ping has an elevation over pi/2");
            
            filteredpings->heading = unWrap(heading + M_PI);
            filteredpings->elevation = M_PI - (M_PI - elevation);
        }
        else
        {
            if(keepElevation)
            {
                ROS_DEBUG_STREAM("Keeping ping");
                filteredpings->heading = pings->heading;
                filteredpings->elevation = pings->elevation;
            }
        }

        filteredpings->header = pings->header;
        fitteredpings->snr = pings->snr;

        return filteredPings;
    }

    double_t elevationCheck::unWrap(double_t angle)
    {
        double_t new_angle = angle;

        while(angle > M_PI)
        {
            new_angle -= 2 * M_PI;
        }
        while(angle < -M_PI)
        {
            new_angle += 2 * M_PI;
        }
        return new_angle;
    }
}
