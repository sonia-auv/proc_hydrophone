//
// Created by coumarc9 on 7/17/17.
//

#ifndef PROC_HYDROPHONE_AVERAGEMERGESTRATEGY_H
#define PROC_HYDROPHONE_AVERAGEMERGESTRATEGY_H

#include <proc_hydrophone/ping_merge_strategy/IPingMergeStrategy.h>

namespace proc_hydrophone {

    class AverageMergeStrategy : IPingMergeStrategy {

    public:
        AverageMergeStrategy();
        ~AverageMergeStrategy();

        geometry_msgs::QuaternionConstPtr Merge(std::vector<provider_hydrophone::PingMsgConstPtr> pings);

    };

}
#endif //PROC_HYDROPHONE_AVERAGEMERGESTRATEGY_H
