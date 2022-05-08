//
// Created by coumarc9 on 3/18/18.
//

#ifndef PROC_HYDROPHONE_KEEPFIRSTPINGFILTER_H
#define PROC_HYDROPHONE_KEEPFIRSTPINGFILTER_H

#include <filter_strategy/IFilterStrategy.h>

namespace proc_hydrophone {

    class KeepFirstPingFilter : public IFilterStrategy {

    public:
        KeepFirstPingFilter(uint32_t nb = 1);

        virtual ~KeepFirstPingFilter();

        std::vector<sonia_common::PingMsgConstPtr>
        Process(std::vector<sonia_common::PingMsgConstPtr> pings) override;

    private:

        uint32_t nb;

    };

}

#endif //PROC_HYDROPHONE_KEEPFIRSTPINGFILTER_H
