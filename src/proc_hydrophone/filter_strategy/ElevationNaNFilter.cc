//
// Created by coumarc9 on 3/18/18.
//

#include "ElevationNaNFilter.h"

namespace proc_hydrophone
{

    ElevationNaNFilter::ElevationNaNFilter() {}

    ElevationNaNFilter::~ElevationNaNFilter() {

    }

    std::vector<provider_hydrophone::PingMsgConstPtr>
    ElevationNaNFilter::Process(std::vector<provider_hydrophone::PingMsgConstPtr> pings) {

        std::vector<provider_hydrophone::PingMsgConstPtr> filteredPings;

        for (auto ping : pings)
        {

            auto elevation = ping->elevation;

            if (elevation == elevation) // Not NaN
            {
                filteredPings.push_back(ping);
                ROS_DEBUG("Ping elevation has value. Ping is accepted");
            }
            else
            {
                ROS_DEBUG("Ping elevation was NAN. Ping is rejected");
            }


        }

        ROS_DEBUG_STREAM("ElevationNaNFilter strategy result Previous : " << pings.size() << " After : " << filteredPings.size());

        return filteredPings;
    }
}