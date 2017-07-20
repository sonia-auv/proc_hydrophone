//
// Created by coumarc9 on 7/16/17.
//

#ifndef PROC_HYDROPHONE_LIMITATIONSTRATEGY_H
#define PROC_HYDROPHONE_LIMITATIONSTRATEGY_H

#include <proc_hydrophone/filter_strategy/IFilterStrategy.h>

namespace proc_hydrophone
{
    class LimitationStrategy : public IFilterStrategy {

    public:

        LimitationStrategy();
        ~LimitationStrategy();

        std::vector<provider_hydrophone::PingMsgConstPtr> Process(std::vector<provider_hydrophone::PingMsgConstPtr> pings);

    };
}


#endif //PROC_HYDROPHONE_LIMITATIONSTRATEGY_H
