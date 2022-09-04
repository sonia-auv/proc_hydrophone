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
    elevationCheck::elevationCheck(double angle, bool flipElevation, bool removeElevation)
        : angle_(angle),
          flipElevation_(flipElevation),
          removeElevation_(removeElevation)
    {   
    }

    elevationCheck::~elevationCheck()
    {

    }

    void elevationCheck::setValues(double_t heading, double_t elevation, double_t frequency, uint16_t snr)
    {
        heading_ = heading;
        elevation_ = elevation;
        ping.frequency = frequency;
        ping.snr = snr;
    }

    bool elevationCheck::compute()
    {
        if(removeElevation_)
        {
            if(elevation_ >= angle_)
            {
                ping.heading = heading_;
                if(flipElevation_)
                {
                    ping.elevation = M_PI_2 - (M_PI - elevation_);
                }
                else
                {
                   ping.elevation = M_PI - elevation_; 
                }
                return true;
            }
            else
            {
                return false;
            }
        }
        return true;
    }

    bool elevationCheck::resetValues()
    {
        heading_ = 0;
        elevation_ = 0;
        ping.frequency = 0;
        ping.snr = 0;    
        ping.heading = 0;
        ping.elevation = 0;
        return true;
    }

    double_t elevationCheck::unWrap(double_t angle)
    {
        double_t new_angle = angle;

        if(angle > M_PI)
        {
            new_angle -= 2 * M_PI;
        }
        if(angle < -M_PI)
        {
            new_angle += 2 * M_PI;
        }
        return new_angle;
    }
}
