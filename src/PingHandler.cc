//
// Created by coumarc9 on 7/16/17.
//

#include "PingHandler.h"

namespace proc_hydrophone
{
    PingHandler::PingHandler(std::shared_ptr<IFilterStrategy> prefilterStrategy, ros::Publisher &pingPosePublisher)
        : prefilterStrategy(prefilterStrategy),
          pingPosePublisher(pingPosePublisher)
    {

    }

    PingHandler::~PingHandler()
    {

    }

    void PingHandler::AddPing(const sonia_common::PingMsgConstPtr &ping)
    {
        std::vector<sonia_common::PingMsgConstPtr> newping;
        
        ROS_DEBUG_STREAM("Pre-Filtering received ping");

        newping.push_back(ping);
        std::vector<sonia_common::PingMsgConstPtr> prefilteredPing = prefilterStrategy->Process(newping);

        if(!prefilteredPing.empty())
        {
            ROS_DEBUG_STREAM("Received Ping is correct");
            pingPosePublisher.publish(ping);
        }
    }
}
