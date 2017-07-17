/**
 * \file	proc_hydrophone_node.h
 * \author	Marc-Antoine Couture <coumarc9@outlook.com>
 * \date	07/16/2017
 *
 * \copyright Copyright (c) 2017 S.O.N.I.A. All rights reserved.
 *
 * \section LICENSE
 *
 * This file is part of S.O.N.I.A. software.
 *
 * S.O.N.I.A. software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * S.O.N.I.A. software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with S.O.N.I.A. software. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PROC_HYDROPHONE_PROC_HYDROPHONE_NODE_H_
#define PROC_HYDROPHONE_PROC_HYDROPHONE_NODE_H_

#include <ros/node_handle.h>
#include <nav_msgs/Odometry.h>
#include <provider_hydrophone/PingMsg.h>
namespace proc_hydrophone {

class ProcHydrophoneNode {
 public:
  //==========================================================================
  // T Y P E D E F   A N D   E N U M

  //==========================================================================
  // P U B L I C   C / D T O R S

  explicit ProcHydrophoneNode(const ros::NodeHandlePtr &nh);

  ~ProcHydrophoneNode();

  /// Taking care of the spinning of the ROS thread.
  /// Each iteration of the loop, this will take the objects in the object
  /// registery, empty it and publish the objects.
  void Spin();

private:

    ros::NodeHandlePtr nh_;


    ros::Subscriber odomSubscriber;
    ros::Subscriber providerHydrophoneSubscriber;

    void OdomCallback(const nav_msgs::OdometryConstPtr &odom);
    void PingCallback(const provider_hydrophone::PingMsgConstPtr &ping);

    nav_msgs::OdometryConstPtr lastOdom;

};

}  // namespace proc_hydrophone

#endif  // PROC_HYDROPHONE_PROC_HYDROPHONE_NODE_H_
