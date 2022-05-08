//
// Created by coumarc9 on 7/16/17.
//

#ifndef PROC_HYDROPHONE_PINGHANDLER_H
#define PROC_HYDROPHONE_PINGHANDLER_H

#include <cstdint>
#include <sonia_common/PingMsg.h>
#include <filter_strategy/IFilterStrategy.h>
#include <ros/ros.h>

namespace proc_hydrophone
{
    class PingHandler {

    public:
        PingHandler(std::shared_ptr<IFilterStrategy> filterStrategy,
                    ros::Publisher &pingPosePublisher);
        ~PingHandler();

        void AddPing(const sonia_common::PingMsgConstPtr &ping);

    private:

        std::shared_ptr<IFilterStrategy> filterStrategy;
        const ros::Publisher pingPosePublisher;
        std::vector<sonia_common::PingMsgConstPtr> newping;

    };
}

#endif //PROC_HYDROPHONE_PINGHANDLER_H
