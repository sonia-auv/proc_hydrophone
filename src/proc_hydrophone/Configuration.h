//
// Created by coumarc9 on 7/21/17.
//

#ifndef PROC_HYDROPHONE_CONFIGURATION_H
#define PROC_HYDROPHONE_CONFIGURATION_H

#include <nav_msgs/Odometry.h>

namespace proc_hydrophone
{
    class Configuration {

    public:
        Configuration();
        ~Configuration();

        void setOdometry(const nav_msgs::OdometryConstPtr &odom){this->odom = odom;};
        nav_msgs::OdometryConstPtr getOdometry(){return odom;};
    private:

        nav_msgs::OdometryConstPtr odom;

    };
}




#endif //PROC_HYDROPHONE_CONFIGURATION_H
