//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: algoClass.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 12-Jul-2022 21:53:11
//

// Include Files
#include "algoClass.h"
#include "rt_nonfinite.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Declarations
static double rt_atan2d_snf(double u0, double u1);

// Function Definitions
//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_atan2d_snf(double u0, double u1)
{
  double y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    int b_u0;
    int b_u1;
    if (u0 > 0.0) {
      b_u0 = 1;
    } else {
      b_u0 = -1;
    }

    if (u1 > 0.0) {
      b_u1 = 1;
    } else {
      b_u1 = -1;
    }

    y = std::atan2(static_cast<double>(b_u0), static_cast<double>(b_u1));
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = std::atan2(u0, u1);
  }

  return y;
}

//
// Arguments    : void
// Return Type  : void
//
algoClass::algoClass()
{
}

//
// Arguments    : void
// Return Type  : void
//
algoClass::~algoClass()
{
  // (no terminate code required)
}

//
// Constantes
// Arguments    : double phaseRef
//                double phase1
//                double phase2
//                double phase3
//                double frequency
//                double c
//                double *heading1
//                double *elevation1
//                double *heading2
//                double *elevation2
// Return Type  : void
//
void algoClass::computeHyperPlans(double phaseRef, double phase1, double phase2,
  double phase3, double frequency, double c, double *heading1, double
  *elevation1, double *heading2, double *elevation2)
{
  double phase[4];
  double a;
  double b;
  double c_tmp;
  double g;
  double i;
  double rij;
  double rik;
  double rkj;
  double rkl;
  double s10;
  double s14;
  int idx;
  int k;

  //  Position des hydros
  //  Preprocessing phase to time difference
  phase[0] = phaseRef;
  phase[1] = phase1;
  phase[2] = phase2;
  phase[3] = phase3;
  if (!rtIsNaN(phaseRef)) {
    idx = 1;
  } else {
    boolean_T exitg1;
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 5)) {
      if (!rtIsNaN(phase[k - 1])) {
        idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }

  if (idx == 0) {
    i = phaseRef;
  } else {
    i = phase[idx - 1];
    idx++;
    for (k = idx; k < 5; k++) {
      s10 = phase[k - 1];
      if (i > s10) {
        i = s10;
      }
    }
  }

  i = std::abs(i);
  s10 = 6.2831853071795862 * frequency;
  phase[0] = (phaseRef + i) / s10;
  phase[1] = (phase1 + i) / s10;
  phase[2] = (phase2 + i) / s10;

  //  Supposition puisqu'on a uniquement les différences de phase
  //  H1 => (h1 - href) si href = 0
  //  H2
  //  H3
  //  Différence de positions
  //  Calcul distance selon les différences d'arrivée
  rij = c * (phase[0] - phase[1]);
  rkj = c * (phase[2] - phase[1]);
  rik = c * (phase[0] - phase[2]);
  rkl = c * (phase[2] - (phase3 + i) / s10);

  //  Calcul des polynomiaux
  s10 = rij * 0.0 - rik * -0.01286;
  s14 = rkj * 0.01286 - rkl * -0.01286;
  c_tmp = rik * rik;

  //  Calcul des plans hyperboliques
  a = 1.0E+10 * (rik * -0.00677 - rij * -0.0145) / s10;
  b = 1.0E+10 * (rik * -0.004 - rij * -0.004) / s10;
  c = 1.0E+10 * (rik * (((rij * rij - 4.58329E-5) - 0.0001653796) - 1.6E-5) -
                 rij * ((c_tmp - 0.00021025000000000001) - 1.6E-5)) / 2.0 / s10;
  i = a - 1.0E+10 * (rkl * 0.0077300000000000008 - rkj * 0.0077300000000000008) /
    s14;
  g = 1.0E+10 * (1.0E+10 * (rkl * 0.0 - rkj * 0.0) / s14 - b) / i;
  rkj = 1.0E+10 * (1.0E+10 * (rkl * (((((rkj * rkj + 0.00021025000000000001) -
    4.58329E-5) - 0.0001653796) + 1.6E-5) - 1.6E-5) - rkj * (((((rkl * rkl +
    0.00021025000000000001) - 4.58329E-5) - 0.0001653796) + 1.6E-5) - 1.6E-5)) /
                   2.0 / s14 - c) / i;
  i = a * g / 1.0E+10 + b;
  rij = a * rkj / 1.0E+10 + c;
  rik = (((c_tmp - 0.00021025000000000001) - 1.6E-5) * 1.0E+10 + 2.0 * rij * 0.0)
    + 2.0 * rkj * -0.0145;
  s10 = 2.0 * ((g * -0.0145 + i * 0.0) + -4.0E+7);
  rkl = 4.0 * c_tmp;
  s14 = rkl * ((g * g + i * i) + 1.0E+20) - s10 * s10;

  //  Résolution de l'intersection des plans
  s10 = (8.0 * c_tmp * (g * (0.0 - rkj) + i * (0.0 - rij)) + 2.0 * s10 * rik) /
    (2.0 * s14);
  i = std::sqrt(std::abs(s10 * s10 - (rkl * ((0.0 - rkj) * (0.0 - rkj) + (0.0 -
    rij) * (0.0 - rij)) - rik * rik) / s14));
  rij = s10 + i;
  rik = s10 - i;
  i = (g * rij + rkj) / 1.0E+10;
  s10 = (g * rik + rkj) / 1.0E+10;
  *heading1 = rt_atan2d_snf(((a * i + b * rij) + c) / 1.0E+10, i);
  *elevation1 = rt_atan2d_snf(rij, i);
  *heading2 = rt_atan2d_snf(((a * s10 + b * rik) + c) / 1.0E+10, s10);
  *elevation2 = rt_atan2d_snf(rik, s10);
}

//
// File trailer for algoClass.cpp
//
// [EOF]
//
