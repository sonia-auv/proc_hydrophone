//
// Created by coumarc9 on 7/16/17.
//

#include "proc_hydrophone/PingHandler.h"

namespace proc_hydrophone
{
    PingHandler::PingHandler(uint8_t frequency)
        : frequency(frequency)
    {
    }

    PingHandler::~PingHandler() {}

    void PingHandler::AddPing(const provider_hydrophone::PingMsgConstPtr &ping) {

        auto currentStamp = ping->header.stamp;

        // If new group, process
        if ((currentStamp - lastStamp).sec >= 1)
        {
            std::cout << "New group" << std::endl;
            lastStamp = currentStamp;
        }

    }
}