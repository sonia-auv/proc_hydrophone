//
// Created by coumarc9 on 7/17/17.
//

#include "AverageMergeStrategy.h"

namespace proc_hydrophone
{

    AverageMergeStrategy::AverageMergeStrategy() {

    }

    AverageMergeStrategy::~AverageMergeStrategy() {}

    geometry_msgs::QuaternionConstPtr
    AverageMergeStrategy::Merge(std::vector<provider_hydrophone::PingMsgConstPtr> pings) {

        geometry_msgs::QuaternionPtr orientation;

        if (pings.size() == 1)
        {
            auto ping = pings[0];

            orientation->z = ping->heading;
            orientation->y = ping->elevation;

            return orientation;
        }

        double_t xHeading = 0;
        double_t yHeading = 0;

        double_t xElevation = 0;
        double_t yElevation = 0;
        uint16_t elevationCount = 0;

        for (auto ping : pings)
        {
            double_t heading = ping->heading;

            xHeading += cos(heading);
            yHeading += sin(heading);

            double_t elevation = ping->elevation;

            if (elevation != elevation) // NAN
            {
                xElevation += cos(elevation);
                yElevation += sin(elevation);
                elevationCount++;
            }

        }

        xHeading /= pings.size();
        yHeading /= pings.size();

        orientation->z = atan2(yHeading, xHeading);

        if (elevationCount > 0)
        {
            xElevation /= elevationCount;
            yElevation /= elevationCount;

            orientation->y = atan2(yElevation, xElevation);
        }

        return orientation;
    }
}