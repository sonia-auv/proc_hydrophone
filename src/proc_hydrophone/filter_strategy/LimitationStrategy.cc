//
// Created by coumarc9 on 7/16/17.
//

#include <proc_hydrophone/filter_strategy/LimitationStrategy.h>

namespace proc_hydrophone
{

    LimitationStrategy::LimitationStrategy() {

    }

    LimitationStrategy::~LimitationStrategy() {

    }

    geometry_msgs::QuaternionConstPtr
    LimitationStrategy::Process(std::vector<provider_hydrophone::PingMsgConstPtr> pings) {
        return geometry_msgs::QuaternionConstPtr();
    }


}