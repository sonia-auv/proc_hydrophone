//
// Created by coumarc9 on 7/16/19.
//

#ifndef PROC_HYDROPHONE_AMPLITUDEFILTER_H
#define PROC_HYDROPHONE_AMPLITUDEFILTER_H

#include <filter_strategy/IFilterStrategy.h>
#include <ros/ros.h>


namespace proc_hydrophone {

    class AmplitudeFilter : public IFilterStrategy {

    public:
        AmplitudeFilter(uint32_t maxAmplitude, uint32_t minAmplitude);

        virtual ~AmplitudeFilter();

        //std::vector<sonia_common::PingMsgConstPtr>
        //Process(std::vector<sonia_common::PingMsgConstPtr> pings) override;

    private:
        uint32_t minAmplitude;
        uint32_t maxAmplitude;

    };
}

#endif //PROC_HYDROPHONE_AMPLITUDEFILTER_H
