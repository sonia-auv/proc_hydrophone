//
// Created by coumarc9 on 3/18/18.
//

#include "CompositeFilter.h"

namespace proc_hydrophone
{

    CompositeFilter::CompositeFilter() {}

    CompositeFilter::~CompositeFilter() {

    }

    std::vector<provider_hydrophone::PingMsgConstPtr>
    CompositeFilter::Process(std::vector<provider_hydrophone::PingMsgConstPtr> pings) {
        return pings;
    }
}