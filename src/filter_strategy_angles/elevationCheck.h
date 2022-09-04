/**
 * \file	elevationCheck.h
 * \author	Francis Alonzo <francisalonzo@gmail.com>
 * \date	23/072022
 *
 * \copyright Copyright (c) 2022 S.O.N.I.A. All rights reserved.
 *
 * \section LICENSE
 *
 * This file is part of S.O.N.I.A. software.
 *
 * S.O.N.I.A. software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * S.O.N.I.A. software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with S.O.N.I.A. software. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PROC_HYDROPHONE_ELEVATIONCHECK_H
#define PROC_HYDROPHONE_ELEVATIONCHECK_H

#include <sonia_common/PingAngles.h>
#include <ros/ros.h>
#include <math.h>

namespace proc_hydrophone
{
    class elevationCheck
    {
    //==========================================================================
    // P U B L I C   C / D T O R S
    public:
        elevationCheck(double angle, bool flipElevation, bool removeElevation);
        ~elevationCheck();

        void setValues(double_t heading, double_t elevation, double_t frequency, uint16_t snr);
        bool compute();
        bool resetValues();

        sonia_common::PingAngles getPing() {return ping;};

    private:

        double_t angle_;
        bool flipElevation_;
        bool removeElevation_;

        double_t heading_;
        double_t elevation_;
        double_t frequency_;
        uint16_t snr_;

        sonia_common::PingAngles ping;

        double_t unWrap(double_t angle);
    };

}
#endif //PROC_HYDROPHONE_PHASEDIFF_H
