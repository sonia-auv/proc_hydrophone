//
// Created by coumarc9 on 3/18/18.
//

#include "CompositeFilter.h"

namespace proc_hydrophone
{

    CompositeFilter::CompositeFilter(std::shared_ptr<std::vector<std::shared_ptr<IFilterStrategy>>> filters) : filters(filters) {}

    CompositeFilter::~CompositeFilter() {

    }

    std::vector<provider_hydrophone::PingMsgConstPtr>
    CompositeFilter::Process(std::vector<provider_hydrophone::PingMsgConstPtr> pings) {

        std::vector<provider_hydrophone::PingMsgConstPtr> filteredPings = pings;

        for (auto filter : *filters) {
            filteredPings = filter->Process(filteredPings);
        }

        return filteredPings;
    }
}