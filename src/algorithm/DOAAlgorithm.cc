/**
 * \file	DOAAlgorithm.cc
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

 #include "DOAAlgorithm.h"

 #define POW2(x) x*x

 namespace proc_hydrophone {

    // DOAAlgorithm::DOAAlgorithm(double_t phaseRef, double_t phase1, double_t phase2, double_t phase3, uint16_t index, uint16_t snr)
    //     :   phaseRef_(phaseRef),
    //         phase1_(phase1),
    //         phase2_(phase2),
    //         phase3_(phase3),
    //         index_(index),
    //         snr_(snr)
    // {
    // }

    DOAAlgorithm::DOAAlgorithm()
    {
        hydrophone_position <<  64.6830530401035,	-129.366106080207,	64.6830530401035,
                                -38.8802488335925,	0,	                38.8802488335925,
                                -234.476067270375,	218.952134540750,	-234.476067270375;
    }

    DOAAlgorithm::~DOAAlgorithm()
    {
    }

    void DOAAlgorithm::setValues(double_t phaseRef, double_t phase1, double_t phase2, double_t phase3, uint16_t index, uint16_t snr)
    {
        phaseRef_ = phaseRef;
        phase1_ = phase1;
        phase2_ = phase2;
        phase3_ = phase3;
        index_ = index;
        snr_ = snr;        
    }

    void DOAAlgorithm::compute()
    {
        computeAngles();
        computeFrequency();
    }

    bool DOAAlgorithm::resetValues()
    {
        phaseRef_ = 0.0;
        phase1_ = 0.0;
        phase2_ = 0.0;
        phase3_ = 0.0;
        index_ = 0.0;
        snr_ = 0.0;

        return true;         
    }

    void DOAAlgorithm::computeAngles()
    {
        Vector3d dephasage, m;
        dephasage << phase1_ - phaseRef_, phase2_ - phaseRef_, phase3_ - phaseRef_;

        m = hydrophone_position * dephasage; // À confirmer cross() ou dot()

        calculateHeading(m(0), m(1));
        calculateElevation(m(0), m(1), m(2));
    }

    void DOAAlgorithm::computeFrequency()
    {
        frequency_ = index_ * (sample_rate / fft_length);
    }

    void DOAAlgorithm::calculateHeading(double_t x, double_t y)
    {
        heading_ = atan2(y,x);
    }

    void DOAAlgorithm::calculateElevation(double_t x, double_t y, double_t z)
    {
        double_t _x = POW2(x), _y = POW2(y), _z = POW2(z);
        double_t sum = 0, tmp = 0;

        sum = _x + _y + _z;
        tmp = z / sum;
        
        // Ajouter une configuration pour la valeur absolue
        elevation_ = acos(abs(tmp));
    }

    // const Matrix3d DOAAlgorithm::getHydroPosition()
    // {
    //     static Matrix3d hydrophone_position <<  64.6830530401035,	-129.366106080207,	64.6830530401035,
    //                                             -38.8802488335925,	0,	                38.8802488335925,
    //                                             -234.476067270375,	218.952134540750,	-234.476067270375;
    //     return hydrophone_position;
    // }

}