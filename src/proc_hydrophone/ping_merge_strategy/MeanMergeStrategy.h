//
// Created by coumarc9 on 7/17/17.
//

#ifndef PROC_HYDROPHONE_AVERAGEMERGESTRATEGY_H
#define PROC_HYDROPHONE_AVERAGEMERGESTRATEGY_H

#include <proc_hydrophone/ping_merge_strategy/IPingMergeStrategy.h>

namespace proc_hydrophone {

    class MeanMergeStrategy : public IPingMergeStrategy {

    public:
        MeanMergeStrategy();
        ~MeanMergeStrategy();

        geometry_msgs::QuaternionPtr Merge(std::vector<sonia_common::PingMsgConstPtr> pings);

    };

}
#endif //PROC_HYDROPHONE_AVERAGEMERGESTRATEGY_H
