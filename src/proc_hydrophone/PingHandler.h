//
// Created by coumarc9 on 7/16/17.
//

#ifndef PROC_HYDROPHONE_PINGHANDLER_H
#define PROC_HYDROPHONE_PINGHANDLER_H

#include <cstdint>
#include <sonia_common/PingMsg.h>
#include <sonia_common/PingPose.h>
#include <proc_hydrophone/filter_strategy/IFilterStrategy.h>
#include <proc_hydrophone/ping_merge_strategy/IPingMergeStrategy.h>
#include <ros/publisher.h>
#include "Configuration.h"

namespace proc_hydrophone
{
    class PingHandler {

    public:
        PingHandler(uint8_t frequency, std::shared_ptr<IFilterStrategy> filterStrategy,
                    std::shared_ptr<IPingMergeStrategy> pingMergeStrategy,
                    std::shared_ptr<Configuration> &configuration,
                    ros::Publisher &pingPosePublisher);
        ~PingHandler();

        void AddPing(const sonia_common::PingMsgConstPtr &ping);

    private:

        uint8_t frequency;
        std::shared_ptr<IFilterStrategy> filterStrategy;
        std::shared_ptr<IPingMergeStrategy> pingMergeStrategy;
        std::shared_ptr<Configuration> configuration;

        ros::Time lastStamp;

        const uint8_t refreshTime = 1;

        std::vector<sonia_common::PingMsgConstPtr> pendingPings;

        // TODO Configuration
        const double offset = 55 * M_PI / 180;

        const ros::Publisher pingPosePublisher;

    };
}

#endif //PROC_HYDROPHONE_PINGHANDLER_H
