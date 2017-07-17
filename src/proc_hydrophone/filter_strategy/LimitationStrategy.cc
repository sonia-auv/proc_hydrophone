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

    std::vector<provider_hydrophone::PingMsgConstPtr>
    LimitationStrategy::Process(std::vector<provider_hydrophone::PingMsgConstPtr> pings) {

        std::vector<provider_hydrophone::PingMsgConstPtr> filteredPings;

        for (auto ping : pings)
        {

            auto elevation = ping->elevation;

            // TODO Validation first
            if (elevation != elevation) // NAN
            {
                std::cout << "NAN" << std::endl;
                continue;
            }

            if (ping->amplitude < 100000) // TODO TEMP, test
            {
                std::cout << "Amplitude < 100000" << std::endl;
                continue;
            }

            filteredPings.push_back(ping);

        }

        std::cout << "Previous : " << pings.size() << " After : " << filteredPings.size() << std::endl;

        return filteredPings;
    }


}