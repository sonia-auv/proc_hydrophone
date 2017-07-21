//
// Created by coumarc9 on 7/16/17.
//

#include <geometry_msgs/Pose.h>
#include "proc_hydrophone/PingHandler.h"

namespace proc_hydrophone
{
    PingHandler::PingHandler(uint8_t frequency, std::shared_ptr<IFilterStrategy> filterStrategy,
                             std::shared_ptr<IPingMergeStrategy> pingMergeStrategy,
                             std::shared_ptr<Configuration> &configuration)
        : frequency(frequency),
          filterStrategy(filterStrategy),
          pingMergeStrategy(pingMergeStrategy),
          configuration(configuration)
    {

    }

    PingHandler::~PingHandler() {}

    void PingHandler::AddPing(const provider_hydrophone::PingMsgConstPtr &ping) {

        auto currentStamp = ping->header.stamp;

        // If new group, process
        if ((currentStamp - lastStamp).sec >= 1)
        {

            auto pingsValidated = filterStrategy->Process(pendingPings);

            if (pingsValidated.size() > 0)
            {
                auto orientation = pingMergeStrategy->Merge(pingsValidated);
                // TODO Use odom to create Pose then publish it

                std::cout << configuration->getOdometry()->header << std::endl;

                //orientation->z += M_PI + 45 / M_PI * 180; // 45 ° offset
                //orientation->z = std::fmod(orientation->z ,2 * M_PI);

                //geometry_msgs::PosePtr pose(new geometry_msgs::Pose);



            }

            pendingPings.clear();

            lastStamp = currentStamp;
        }

        pendingPings.push_back(ping);

    }
}