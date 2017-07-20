//
// Created by coumarc9 on 7/16/17.
//

#include "proc_hydrophone/PingHandler.h"

namespace proc_hydrophone
{
    PingHandler::PingHandler(uint8_t frequency, std::shared_ptr<IFilterStrategy> filterStrategy, std::shared_ptr<IPingMergeStrategy> pingMergeStrategy)
        : frequency(frequency),
          filterStrategy(filterStrategy),
          pingMergeStrategy(pingMergeStrategy)
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
            }

            pendingPings.clear();

            lastStamp = currentStamp;
        }

        pendingPings.push_back(ping);

    }
}