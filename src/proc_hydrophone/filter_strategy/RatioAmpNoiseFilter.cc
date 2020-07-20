//
// Created by Francis on 7/17/19.
//

#include "RatioAmpNoiseFilter.h"

namespace proc_hydrophone {

    RatioAmpNoiseFilter::RatioAmpNoiseFilter(uint32_t maxRatio, uint32_t minRatio) :
                maxRatio(maxRatio),
                minRatio(minRatio) {}

    RatioAmpNoiseFilter::~RatioAmpNoiseFilter() {}

    std::vector<sonia_msgs::PingMsgConstPtr>
    RatioAmpNoiseFilter::Process(std::vector<sonia_msgs::PingMsgConstPtr> pings) {

        std::vector<sonia_msgs::PingMsgConstPtr> filteredPings;

        for (auto ping : pings) {

            double Ratio = (ping->amplitude)/(ping->noise);

            if (Ratio <= maxRatio && Ratio >= minRatio ) // Not NaN
            {
                filteredPings.push_back(ping);
            }
        }

        ROS_DEBUG_STREAM("ElevationNaNFilter strategy result Previous : " << pings.size() << " After : "
                                                                          << filteredPings.size());

        return filteredPings;
    }
}