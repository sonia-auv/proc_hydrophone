//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: algoClass.h
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 12-Jul-2022 21:53:11
//
#ifndef ALGOCLASS_H
#define ALGOCLASS_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
class algoClass
{
 public:
  algoClass();
  ~algoClass();
  void computeHyperPlans(double phaseRef, double phase1, double phase2, double
    phase3, double frequency, double c, double *heading1, double *elevation1,
    double *heading2, double *elevation2);
};

#endif

//
// File trailer for algoClass.h
//
// [EOF]
//
