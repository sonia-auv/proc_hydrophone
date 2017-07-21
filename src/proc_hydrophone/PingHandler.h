//
// Created by coumarc9 on 7/16/17.
//

#ifndef PROC_HYDROPHONE_PINGHANDLER_H
#define PROC_HYDROPHONE_PINGHANDLER_H

#include <cstdint>
#include <provider_hydrophone/PingMsg.h>
#include <proc_hydrophone/PingPose.h>
#include <proc_hydrophone/filter_strategy/IFilterStrategy.h>
#include <proc_hydrophone/ping_merge_strategy/IPingMergeStrategy.h>
#include "Configuration.h"

namespace proc_hydrophone
{
    class PingHandler {

    public:
        PingHandler(uint8_t frequency, std::shared_ptr<IFilterStrategy> filterStrategy,
                    std::shared_ptr<IPingMergeStrategy> pingMergeStrategy,
                    std::shared_ptr<Configuration> &configuration);
        ~PingHandler();

        void AddPing(const provider_hydrophone::PingMsgConstPtr &ping);

    private:

        uint8_t frequency;
        std::shared_ptr<IFilterStrategy> filterStrategy;
        std::shared_ptr<IPingMergeStrategy> pingMergeStrategy;
        std::shared_ptr<Configuration> configuration;

        ros::Time lastStamp;

        const uint8_t refreshTime = 1;

        std::vector<provider_hydrophone::PingMsgConstPtr> pendingPings;

        // TODO Configuration
        const double offset = M_PI + 45 * M_PI / 180;

    };
}

#endif //PROC_HYDROPHONE_PINGHANDLER_H
