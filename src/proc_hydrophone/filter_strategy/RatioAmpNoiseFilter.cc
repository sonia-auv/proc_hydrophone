//
// Created by Francis on 7/17/19.
//

#include "RatioAmpNoiseFilter.h"

namespace proc_hydrophone {

    RatioAmpNoiseFilter::RatioAmpNoiseFilter(uint32_t maxRatio) :
                maxRatio(maxRatio) {}

    RatioAmpNoiseFilter::~RatioAmpNoiseFilter() {}

    std::vector<provider_hydrophone::PingMsgConstPtr>
    RatioAmpNoiseFilter::Process(std::vector<provider_hydrophone::PingMsgConstPtr> pings) {

        std::vector<provider_hydrophone::PingMsgConstPtr> filteredPings;

        for (auto ping : pings) {

            u_int32_t Ratio = ((ping->amplitude) - (ping->noise)) / 10000;

            if (Ratio < maxRatio) // Not NaN
            {
                filteredPings.push_back(ping);
            }
        }

        ROS_DEBUG_STREAM("ElevationNaNFilter strategy result Previous : " << pings.size() << " After : "
                                                                          << filteredPings.size());

        return filteredPings;
    }
}