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
        CompositeFilter(std::shared_ptr<std::vector<std::shared_ptr<IFilterStrategy>>> filters);

        virtual ~CompositeFilter();

        std::vector<sonia_msgs::PingMsgConstPtr>
        Process(std::vector<sonia_msgs::PingMsgConstPtr> pings) override;

    private:
        std::shared_ptr<std::vector<std::shared_ptr<IFilterStrategy>>> filters;

    };
}

#endif //PROC_HYDROPHONE_COMPOSITEFILTER_H
