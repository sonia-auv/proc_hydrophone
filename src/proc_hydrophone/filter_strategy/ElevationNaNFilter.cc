//
// Created by coumarc9 on 3/18/18.
//

#include "ElevationNaNFilter.h"

namespace proc_hydrophone
{

    ElevationNaNFilter::ElevationNaNFilter() {}

    ElevationNaNFilter::~ElevationNaNFilter() {

    }

    std::vector<provider_hydrophone::PingMsgConstPtr>
    ElevationNaNFilter::Process(std::vector<provider_hydrophone::PingMsgConstPtr> pings) {
        return pings;
    }
}