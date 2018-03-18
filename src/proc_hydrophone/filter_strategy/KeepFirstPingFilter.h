//
// Created by coumarc9 on 3/18/18.
//

#ifndef PROC_HYDROPHONE_KEEPFIRSTPINGFILTER_H
#define PROC_HYDROPHONE_KEEPFIRSTPINGFILTER_H

#include <proc_hydrophone/filter_strategy/IFilterStrategy.h>
#include <ros/ros.h>

namespace proc_hydrophone {

    class KeepFirstPingFilter : public IFilterStrategy {

    public:
        KeepFirstPingFilter();

        virtual ~KeepFirstPingFilter();

        std::vector<provider_hydrophone::PingMsgConstPtr>
        Process(std::vector<provider_hydrophone::PingMsgConstPtr> pings) override;

    };

}

#endif //PROC_HYDROPHONE_KEEPFIRSTPINGFILTER_H
