//
// Created by coumarc9 on 3/18/18.
//

#include "KeepFirstPingFilter.h"

namespace proc_hydrophone
{
    KeepFirstPingFilter::KeepFirstPingFilter() {}

    KeepFirstPingFilter::~KeepFirstPingFilter() {}

    std::vector<provider_hydrophone::PingMsgConstPtr>
    KeepFirstPingFilter::Process(std::vector<provider_hydrophone::PingMsgConstPtr> pings) {

        return pings;

    }
}


