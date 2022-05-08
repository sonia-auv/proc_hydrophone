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
        
        // auto currentStamp = ping->header.stamp;

        // // If new group, process
        // if ((currentStamp - lastStamp).sec >= 1)
        // {
        //     ROS_INFO_STREAM("Filtering received pings");
        //     auto pingsValidated = filterStrategy->Process(pendingPings);

        //     if (pingsValidated.size() > 0)
        //     {

        //         for (auto toto : pingsValidated)
        //         {
        //             ROS_INFO_STREAM("Ping received : " << *toto);
        //         }

        //         ROS_INFO_STREAM("Merging received pings");
        //         auto orientation = pingMergeStrategy->Merge(pingsValidated);
        //         // TODO Use odom to create Pose then publish it

        //         auto odom = configuration->getOdometry();

        //         // TODO Configuration
        //         auto zBase = odom->pose.pose.orientation.z * M_PI / 180;

        //         auto newZ = fmod(zBase + offset - orientation->z, 2 * M_PI);

        //         while (newZ < 0) // Make sure z is positive
        //             newZ += 2 * M_PI;

        //         orientation->z = newZ;

        //         geometry_msgs::PosePtr pose(new geometry_msgs::Pose);
        //         pose->orientation = *orientation;
        //         pose->position = odom->pose.pose.position;


        //         sonia_common::PingPosePtr pingPose(new sonia_common::PingPose);
        //         pingPose->pose = *pose;
        //         pingPose->frequency = this->frequency;
        //         // TODO Add amplitude and noise

        //         pingPosePublisher.publish(pingPose);

        //     }

        //     pendingPings.clear();

        //     lastStamp = currentStamp;
        // }

        // pendingPings.push_back(ping);

    }
}
