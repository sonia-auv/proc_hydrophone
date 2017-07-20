//
// Created by coumarc9 on 7/16/17.
//

#ifndef PROC_HYDROPHONE_PINGHANDLER_H
#define PROC_HYDROPHONE_PINGHANDLER_H

#include <cstdint>
#include <provider_hydrophone/PingMsg.h>
#include <proc_hydrophone/filter_strategy/IFilterStrategy.h>
#include <proc_hydrophone/ping_merge_strategy/IPingMergeStrategy.h>
namespace proc_hydrophone
{
    class PingHandler {

    public:
        PingHandler(uint8_t frequency, std::shared_ptr<IFilterStrategy> filterStrategy, std::shared_ptr<IPingMergeStrategy> pingMergeStrategy);
        ~PingHandler();

        void AddPing(const provider_hydrophone::PingMsgConstPtr &ping);

    private:

        uint8_t frequency;
        std::shared_ptr<IFilterStrategy> filterStrategy;
        std::shared_ptr<IPingMergeStrategy> pingMergeStrategy;

        ros::Time lastStamp;

        const uint8_t refreshTime = 1;

        std::vector<provider_hydrophone::PingMsgConstPtr> pendingPings;

    };
}

#endif //PROC_HYDROPHONE_PINGHANDLER_H
