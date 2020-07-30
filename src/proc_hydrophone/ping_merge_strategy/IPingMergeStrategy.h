//
// Created by coumarc9 on 7/17/17.
//

#ifndef PROC_HYDROPHONE_IPINGMERGESTRATEGY_H
#define PROC_HYDROPHONE_IPINGMERGESTRATEGY_H

#include <geometry_msgs/Quaternion.h>
#include <sonia_common/PingMsg.h>

namespace proc_hydrophone
{
    class IPingMergeStrategy
    {
    public:

        virtual geometry_msgs::QuaternionPtr Merge(std::vector<sonia_common::PingMsgConstPtr> pings) = 0;

    };
}

#endif //PROC_HYDROPHONE_IPINGMERGESTRATEGY_H
