//
// Created by coumarc9 on 3/18/18.
//

#include "KeepFirstPingFilter.h"

namespace proc_hydrophone
{
    KeepFirstPingFilter::KeepFirstPingFilter(uint32_t nb) : nb(nb) {}

    KeepFirstPingFilter::~KeepFirstPingFilter() {}

    std::vector<sonia_common::PingMsgConstPtr>
    KeepFirstPingFilter::Process(std::vector<sonia_common::PingMsgConstPtr> pings) {

        std::vector<sonia_common::PingMsgConstPtr> filteredPings;

        auto size = pings.size();

        if (size >= nb)
        {
            size = nb;
        }
        else
        {
            ROS_INFO_STREAM("Vector contain less element than asked. " << size << "elements will be copied");
        }

        for (u_int32_t i = 0; i < size; ++i) {
            filteredPings.push_back(pings[i]);
        }


        ROS_INFO_STREAM("KeepFirstPingFilter strategy result Previous : " << size << " After : " << filteredPings.size());

        return filteredPings;

    }
}
