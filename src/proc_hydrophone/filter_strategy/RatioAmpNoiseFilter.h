//
// Created by supertoto on 7/17/19.
//

#ifndef PROC_HYDROPHONE_RATIOAMPNOISEFILTER_H
#define PROC_HYDROPHONE_RATIOAMPNOISEFILTER_H

#include <proc_hydrophone/filter_strategy/IFilterStrategy.h>
#include <ros/ros.h>

namespace proc_hydrophone {

    class RatioAmpNoiseFilter : public IFilterStrategy {

    public:
        RatioAmpNoiseFilter(uint32_t maxRatio);

        virtual ~RatioAmpNoiseFilter();

        std::vector<provider_hydrophone::PingMsgConstPtr>
        Process(std::vector<provider_hydrophone::PingMsgConstPtr> pings) override;

    private:
        uint32_t maxRatio;
    };

}




#endif //PROC_HYDROPHONE_RATIOAMPNOISEFILTER_H
