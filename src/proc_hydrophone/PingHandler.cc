//
// Created by coumarc9 on 7/16/17.
//

#include <geometry_msgs/Pose.h>
#include "proc_hydrophone/PingHandler.h"

namespace proc_hydrophone
{
    PingHandler::PingHandler(uint8_t frequency, std::shared_ptr<IFilterStrategy> filterStrategy,
                             std::shared_ptr<IPingMergeStrategy> pingMergeStrategy,
                             std::shared_ptr<Configuration> &configuration,
                             ros::Publisher &pingPosePublisher)
        : frequency(frequency),
          filterStrategy(filterStrategy),
          pingMergeStrategy(pingMergeStrategy),
          configuration(configuration),
          pingPosePublisher(pingPosePublisher)
    {

    }

    PingHandler::~PingHandler() {}

    void PingHandler::AddPing(const sonia_msgs::PingMsgConstPtr &ping) {

        auto currentStamp = ping->header.stamp;

        // If new group, process
        if ((currentStamp - lastStamp).sec >= 1)
        {

            auto pingsValidated = filterStrategy->Process(pendingPings);

            if (pingsValidated.size() > 0)
            {

                for (auto toto : pingsValidated)
                {
                    ROS_DEBUG_STREAM("Ping received : " << *toto);
                }



                auto orientation = pingMergeStrategy->Merge(pingsValidated);
                // TODO Use odom to create Pose then publish it

                auto odom = configuration->getOdometry();

                // TODO Configuration
                auto zBase = odom->pose.pose.orientation.z * M_PI / 180;

                auto newZ = fmod(zBase + offset - orientation->z, 2 * M_PI);

                while (newZ < 0) // Make sure z is positive
                    newZ += 2 * M_PI;

                orientation->z = newZ;

                geometry_msgs::PosePtr pose(new geometry_msgs::Pose);
                pose->orientation = *orientation;
                pose->position = odom->pose.pose.position;


                PingPosePtr pingPose(new PingPose);
                pingPose->pose = *pose;
                pingPose->frequency = this->frequency;
                // TODO Add amplitude and noise

                pingPosePublisher.publish(pingPose);

            }

            pendingPings.clear();

            lastStamp = currentStamp;
        }

        pendingPings.push_back(ping);

    }
}