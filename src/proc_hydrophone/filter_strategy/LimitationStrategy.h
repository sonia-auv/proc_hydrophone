//
// Created by coumarc9 on 7/16/17.
//

#ifndef PROC_HYDROPHONE_LIMITATIONSTRATEGY_H
#define PROC_HYDROPHONE_LIMITATIONSTRATEGY_H

#include <proc_hydrophone/filter_strategy/IFilterStrategy.h>
#include <ros/ros.h>

namespace proc_hydrophone
{
    class LimitationStrategy : public IFilterStrategy {

    public:

        LimitationStrategy();
        ~LimitationStrategy();

        //std::vector<sonia_common::PingMsgConstPtr> Process(std::vector<sonia_common::PingMsgConstPtr> pings);

    };
}


#endif //PROC_HYDROPHONE_LIMITATIONSTRATEGY_H
