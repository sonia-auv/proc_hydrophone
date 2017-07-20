//
// Created by coumarc9 on 7/16/17.
//

#ifndef PROC_HYDROPHONE_IFILTERSTRATEGY_H
#define PROC_HYDROPHONE_IFILTERSTRATEGY_H

#include <geometry_msgs/Quaternion.h>
#include <provider_hydrophone/PingMsg.h>

namespace proc_hydrophone
{
    class IFilterStrategy
    {
    public:
        virtual std::vector<provider_hydrophone::PingMsgConstPtr> Process(std::vector<provider_hydrophone::PingMsgConstPtr> pings) = 0;
    };
}

#endif //PROC_HYDROPHONE_IFILTERSTRATEGY_H