//
// Created by coumarc9 on 7/16/17.
//

#include "LimitationStrategy.h"

namespace proc_hydrophone
{

    LimitationStrategy::LimitationStrategy() {}

    LimitationStrategy::~LimitationStrategy() {}

    /*std::vector<sonia_common::PingMsgConstPtr>
    LimitationStrategy::Process(std::vector<sonia_common::PingMsgConstPtr> pings) {

        std::vector<sonia_common::PingMsgConstPtr> filteredPings;

        for (auto ping : pings)
        {

            auto elevation = ping->elevation;

            // TODO Validation first
            if (elevation != elevation) // NAN
            {
                ROS_DEBUG("Elevation was NAN");
                continue;
            }

            if (ping->amplitude < 10000) // TODO TEMP, test
            {
                ROS_DEBUG("Amplitude was < than 10000");
                continue;
            }

            filteredPings.push_back(ping);

        }

        ROS_INFO_STREAM("Limitation strategy result Previous : " << pings.size() << " After : " << filteredPings.size());

        return filteredPings;
    }*/
}
