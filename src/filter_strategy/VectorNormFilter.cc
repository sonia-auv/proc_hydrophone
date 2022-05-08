/**
 * \file	VectorNormFilter.cc
 * \author	Francis Alonzo <francisalonzo@gmail.com>
 * \date	07/05/2022
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
#include "VectorNormFilter.h"

namespace proc_hydrophone
{
    VectorNormFilter::VectorNormFilter()
    {
        
    }

    VectorNormFilter::~VectorNormFilter()
    {

    }

    std::vector<sonia_common::PingMsgConstPtr>
    VectorNormFilter::Process(std::vector<sonia_common::PingMsgConstPtr> pings)
    {

        std::vector<sonia_common::PingMsgConstPtr> filteredPings;

        auto z = pings.front()->z;

        if (z >= 0)
        {
            filteredPings.push_back(pings.front());
            ROS_DEBUG_STREAM("Ping has Z positive. Ping is accepted");
        }
        else
        {
            ROS_ERROR_STREAM("Ping has Z negative. Ping rejeted");
        }

        return filteredPings;
    }
}
