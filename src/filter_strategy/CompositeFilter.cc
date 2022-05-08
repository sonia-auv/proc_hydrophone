//
// Created by coumarc9 on 3/18/18.
//

#include "CompositeFilter.h"

namespace proc_hydrophone
{

    CompositeFilter::CompositeFilter(std::shared_ptr<std::vector<std::shared_ptr<IFilterStrategy>>> filters) 
        : filters(filters) 
    {

    }

    CompositeFilter::~CompositeFilter()
    {

    }

    std::vector<sonia_common::PingMsgConstPtr> CompositeFilter::Process(std::vector<sonia_common::PingMsgConstPtr> ping) {

        std::vector<sonia_common::PingMsgConstPtr> filteredPing = ping;

        for (auto filter : *filters) {
            filteredPings = filter->Process(filteredPing);
        }

        return filteredPing;
    }
}
