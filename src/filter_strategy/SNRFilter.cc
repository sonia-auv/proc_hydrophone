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
#include "SNRFilter.h"

namespace proc_hydrophone
{
    SNRFilter::SNRFilter(uint32_t min_SNR)
        : minimum_SNR(min_SNR)
    {
        
    }

    SNRFilter::~SNRFilter()
    {

    }

    std::vector<sonia_common::PingMsgConstPtr>
    SNRFilter::Process(std::vector<sonia_common::PingMsgConstPtr> pings)
    {
        std::vector<sonia_common::PingMsgConstPtr> filteredPings;

        if(pings.empty()) return filteredPings;

        auto snr = pings.front()->debug;

        if (snr >= minimum_SNR)
        {
            filteredPings.push_back(pings.front());
            ROS_DEBUG_STREAM("Ping has a signal to noise ratio higher than " << minimum_SNR << ". Ping is accepted");
        }
        else
        {
            ROS_DEBUG_STREAM("Ping has a signal to noise ratio lower than " << minimum_SNR << ". Ping rejeted");
        }

        return filteredPings;
    }
}
