//
// Created by coumarc9 on 7/16/19.
//

#include "AmplitudeFilter.h"

namespace proc_hydrophone {

    AmplitudeFilter::AmplitudeFilter(uint32_t maxAmplitude, uint32_t minAmplitude) :
            minAmplitude(minAmplitude),
            maxAmplitude(maxAmplitude) {}

    AmplitudeFilter::~AmplitudeFilter() {}

    std::vector<provider_hydrophone::PingMsgConstPtr>
    AmplitudeFilter::Process(std::vector<provider_hydrophone::PingMsgConstPtr> pings) {

        std::vector<provider_hydrophone::PingMsgConstPtr> filteredPings;

        for (auto ping : pings) {

            uint64_t amplitude = ping->amplitude;

            if ((amplitude <= maxAmplitude && amplitude >= minAmplitude)) // Not NaN
            {
                filteredPings.push_back(ping);
            }


        }

        ROS_DEBUG_STREAM("ElevationNaNFilter strategy result Previous : " << pings.size() << " After : "
                                                                          << filteredPings.size());

        return filteredPings;
    }
}