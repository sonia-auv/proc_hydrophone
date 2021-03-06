//
// Created by coumarc9 on 3/18/18.
//

#ifndef PROC_HYDROPHONE_ELEVATIONNANFILTER_H
#define PROC_HYDROPHONE_ELEVATIONNANFILTER_H

#include <proc_hydrophone/filter_strategy/IFilterStrategy.h>
#include <ros/ros.h>
namespace proc_hydrophone
{

    class ElevationNaNFilter : public IFilterStrategy {

    public:
        ElevationNaNFilter();
        virtual ~ElevationNaNFilter();

        std::vector<sonia_common::PingMsgConstPtr>
        Process(std::vector<sonia_common::PingMsgConstPtr> pings) override;

    };

}
#endif //PROC_HYDROPHONE_ELEVATIONNANFILTER_H
