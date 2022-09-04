/**
 * \file	DOAAlgorithm.h
 * \author	Francis Alonzo <francisalonzo29@gmail.com
 * \date	07/15/2022
 * 
 * \copyright Copyright (c) 2021 S.O.N.I.A. All rights reserved.
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

#ifndef DOAALGORITHM_H_
#define DOAALGORITHM_H_

#include <ros/ros.h>
#include <eigen3/Eigen/Eigen>
#include "math.h"

namespace proc_hydrophone {

    class DOAAlgorithm {
        public:

        //==========================================================================
        // T Y P E D E F   A N D   E N U M

        typedef Eigen::Matrix<double, 3, 3> Matrix3d;
        typedef Eigen::Matrix<double, 3, 1> Vector3d;
        
        //==========================================================================
        // P U B L I C   C / D T O R S
        
        DOAAlgorithm(bool absElevation);
        ~DOAAlgorithm();

        void setValues(double_t phaseRef, double_t phase1, double_t phase2, double_t phase3, uint16_t index, uint16_t snr);
        void compute();
        bool resetValues();

        double_t getHeading() {return heading_;}
        double_t getElevation() {return elevation_;}
        uint16_t getFrequency() {return frequency_;}
        uint16_t getSnr() {return snr_;}

        private:

        //==========================================================================
        // P R I V A T E   C / D T O R S

        void computeAngles();
        void computeFrequency();
        void calculateHeading(double_t x, double_t y);
        void calculateElevation(double_t x, double_t y, double_t z);

        double_t phaseRef_ = 0.0;
        double_t phase1_ = 0.0;
        double_t phase2_ = 0.0;
        double_t phase3_ = 0.0;
        uint16_t index_ = 0.0;
        uint16_t snr_ = 0.0;
        uint16_t frequency_ = 0.0; // frequency in Hz
        double_t heading_ = 0.0; // heading in radians
        double_t elevation_ = 0.0; // elevation in radians

        bool absElevation_ = false;

    //--------------------------------------------------------
    //-------------------------CONST--------------------------
    //--------------------------------------------------------

        const double_t sample_rate = 256000.0;
        const double_t fft_length = 256.0;
        Matrix3d hydrophone_position;
    };
}

#endif // DOAALGORITHM_H_