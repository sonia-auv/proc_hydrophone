//
// Created by coumarc9 on 7/16/17.
//

#ifndef PROC_HYDROPHONE_PINGHANDLER_H
#define PROC_HYDROPHONE_PINGHANDLER_H

#include <sonia_common/PingMsg.h>
#include <filter_strategy/IFilterStrategy.h>
#include <ros/ros.h>
#include "algorithm/DOAAlgorithm.h"

namespace proc_hydrophone // To continue with more filters
{
    class PingHandler {

    public:
        PingHandler(std::shared_ptr<IFilterStrategy> prefilterStrategy,
                    ros::Publisher &pingPosePublisher);
        ~PingHandler();

        void AddPing(const sonia_common::PingMsgConstPtr &ping);

    private:

        std::shared_ptr<IFilterStrategy> prefilterStrategy;
        const ros::Publisher pingPosePublisher;

    };
}

#endif //PROC_HYDROPHONE_PINGHANDLER_H
