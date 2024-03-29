/**
 * \file	frontOnly.cc
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
#include "frontOnly.h"

namespace proc_hydrophone
{
    frontOnly::frontOnly(double minangle, double maxangle)
        : minAngle_(minangle),
          maxAngle_(maxangle)
    {   
    }

    frontOnly::~frontOnly()
    {

    }

    void frontOnly::setValues(double_t heading, double_t elevation, double_t frequency, uint16_t snr)
    {
        heading_ = heading;
        elevation_ = elevation;
        ping.frequency = frequency;
        ping.snr = snr;
    }

    bool frontOnly::compute()
    {
        if(heading_ >= minAngle_ && heading_ <= maxAngle_)
        {
            ping.heading = heading_;
            ping.elevation = elevation_;
            return true;
        }
        else
        {
            return false;
        }
    }

    bool frontOnly::resetValues()
    {
        heading_ = 0;
        elevation_ = 0;
        ping.frequency = 0;
        ping.snr = 0;    
        ping.heading = 0;
        ping.elevation = 0;
        return true;
    }
}
