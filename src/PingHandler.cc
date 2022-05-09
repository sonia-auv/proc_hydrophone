//
// Created by coumarc9 on 7/16/17.
//

#include "PingHandler.h"

namespace proc_hydrophone
{
    PingHandler::PingHandler(std::shared_ptr<IFilterStrategy> filterStrategy, ros::Publisher &pingPosePublisher)
        : filterStrategy(filterStrategy),
          pingPosePublisher(pingPosePublisher)
    {

    }

    PingHandler::~PingHandler()
    {

    }

    void PingHandler::AddPing(const sonia_common::PingMsgConstPtr &ping)
    {
        std::vector<sonia_common::PingMsgConstPtr> newping;
        
        ROS_DEBUG_STREAM("Filtering received ping");

        newping.push_back(ping);
        std::vector<sonia_common::PingMsgConstPtr> filteredPing = filterStrategy->Process(newping);

        if(!filteredPing.empty())
        {
            pingPosePublisher.publish(ping);
        }
        else
        {
            ROS_WARN_STREAM("Ping filtered out");
        }
    }
}
