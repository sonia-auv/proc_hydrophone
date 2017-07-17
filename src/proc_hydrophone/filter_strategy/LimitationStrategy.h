//
// Created by coumarc9 on 7/16/17.
//

#ifndef PROC_HYDROPHONE_LIMITATIONSTRATEGY_H
#define PROC_HYDROPHONE_LIMITATIONSTRATEGY_H

#include <proc_hydrophone/filter_strategy/IFilterStrategy.h>

namespace proc_hydrophone
{
    class LimitationStrategy : IFilterStrategy {

    public:

        LimitationStrategy();
        ~LimitationStrategy();

        geometry_msgs::QuaternionConstPtr Process(std::vector<provider_hydrophone::PingMsgConstPtr> pings);

    };
}


#endif //PROC_HYDROPHONE_LIMITATIONSTRATEGY_H
