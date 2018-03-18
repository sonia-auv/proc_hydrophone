//
// Created by coumarc9 on 3/18/18.
//

#ifndef PROC_HYDROPHONE_COMPOSITEFILTER_H
#define PROC_HYDROPHONE_COMPOSITEFILTER_H

#include <proc_hydrophone/filter_strategy/IFilterStrategy.h>
#include <ros/ros.h>

namespace proc_hydrophone {
    class CompositeFilter : public IFilterStrategy{
    public:
        CompositeFilter();

        virtual ~CompositeFilter();

        std::vector<provider_hydrophone::PingMsgConstPtr>
        Process(std::vector<provider_hydrophone::PingMsgConstPtr> pings) override;
    };
}

#endif //PROC_HYDROPHONE_COMPOSITEFILTER_H
