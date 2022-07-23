/**
 * \file	SNRFilter.cc
 * \author	Francis Alonzo <francisalonzo@gmail.com>
 * \date	09/05/2022
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
#include "phaseDiff.h"

namespace proc_hydrophone
{
    phaseDiff::phaseDiff(double_t angle)
        : angle(angle)
    {   
    }

    phaseDiff::~phaseDiff()
    {

    }

    std::vector<sonia_common::PingMsgConstPtr>
    phaseDiff::Process(std::vector<sonia_common::PingMsgConstPtr> pings)
    {
        std::vector<sonia_common::PingMsgConstPtr> filteredPings;

        if(pings.empty()) return filteredPings;

        double_t phaseRef = pings.front()->phaseRef;
        double_t phase1 = pings.front()->phase1;
        double_t phase2 = pings.front()->phase2;
        double_t phase3 = pings.front()->phase3;

        if(abs(phase3 - phaseRef) >= angle || abs(phase2 - phaseRef) >= angle || abs(phase1 - phaseRef) >= angle)
        {
            ROS_DEBUG_STREAM("Ping phase are out of bonds (" << angle << "). Ping rejeted");    
        }
        else
        {
            filteredPings.push_back(pings.front());   
        }

        return filteredPings;
    }
}
