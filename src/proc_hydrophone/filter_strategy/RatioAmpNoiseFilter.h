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
        RatioAmpNoiseFilter(uint32_t maxRatio, uint32_t minRatio);

        virtual ~RatioAmpNoiseFilter();

        std::vector<sonia_msgs::PingMsgConstPtr>
        Process(std::vector<sonia_msgs::PingMsgConstPtr> pings) override;

    private:
        uint32_t maxRatio;
        uint32_t minRatio;
    };

}




#endif //PROC_HYDROPHONE_RATIOAMPNOISEFILTER_H
