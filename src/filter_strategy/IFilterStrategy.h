//
// Created by coumarc9 on 7/16/17.
//

#ifndef PROC_HYDROPHONE_IFILTERSTRATEGY_H
#define PROC_HYDROPHONE_IFILTERSTRATEGY_H

#include <sonia_common/PingMsg.h>
#include <ros/ros.h>
#include <math.h>

namespace proc_hydrophone
{
    class IFilterStrategy
    {
    public:
        virtual std::vector<sonia_common::PingMsgConstPtr> Process(std::vector<sonia_common::PingMsgConstPtr> pings) = 0;
    };
}

#endif //PROC_HYDROPHONE_IFILTERSTRATEGY_H
