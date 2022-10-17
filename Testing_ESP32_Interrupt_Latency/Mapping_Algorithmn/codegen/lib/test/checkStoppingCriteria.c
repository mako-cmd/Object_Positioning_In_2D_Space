/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: checkStoppingCriteria.c
 *
 * MATLAB Coder version            : 5.4
 * C/C++ source code generated on  : 14-Oct-2022 16:21:02
 */

/* Include Files */
#include "checkStoppingCriteria.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : const double gradf[3]
 *                double relFactor
 *                double funDiff
 *                const double x[3]
 *                const double dx[3]
 *                int funcCount
 *                boolean_T stepSuccessful
 *                int *iter
 * Return Type  : int
 */
int checkStoppingCriteria(const double gradf[3], double relFactor,
                          double funDiff, const double x[3], const double dx[3],
                          int funcCount, boolean_T stepSuccessful, int *iter)
{
  double absx;
  double normGradF;
  int exitflag;
  normGradF = 0.0;
  absx = fabs(gradf[0]);
  if (rtIsNaN(absx) || (absx > 0.0)) {
    normGradF = absx;
  }
  absx = fabs(gradf[1]);
  if (rtIsNaN(absx) || (absx > normGradF)) {
    normGradF = absx;
  }
  absx = fabs(gradf[2]);
  if (rtIsNaN(absx) || (absx > normGradF)) {
    normGradF = absx;
  }
  if (normGradF <= 1.0E-10 * relFactor) {
    exitflag = 1;
  } else if (funcCount >= 3000000) {
    exitflag = 0;
  } else if (*iter >= 4000000) {
    exitflag = 0;
  } else {
    double absxk;
    double b_y;
    double t;
    double y;
    normGradF = 3.3121686421112381E-170;
    absx = 3.3121686421112381E-170;
    absxk = fabs(dx[0]);
    if (absxk > 3.3121686421112381E-170) {
      y = 1.0;
      normGradF = absxk;
    } else {
      t = absxk / 3.3121686421112381E-170;
      y = t * t;
    }
    absxk = fabs(x[0]);
    if (absxk > 3.3121686421112381E-170) {
      b_y = 1.0;
      absx = absxk;
    } else {
      t = absxk / 3.3121686421112381E-170;
      b_y = t * t;
    }
    absxk = fabs(dx[1]);
    if (absxk > normGradF) {
      t = normGradF / absxk;
      y = y * t * t + 1.0;
      normGradF = absxk;
    } else {
      t = absxk / normGradF;
      y += t * t;
    }
    absxk = fabs(x[1]);
    if (absxk > absx) {
      t = absx / absxk;
      b_y = b_y * t * t + 1.0;
      absx = absxk;
    } else {
      t = absxk / absx;
      b_y += t * t;
    }
    absxk = fabs(dx[2]);
    if (absxk > normGradF) {
      t = normGradF / absxk;
      y = y * t * t + 1.0;
      normGradF = absxk;
    } else {
      t = absxk / normGradF;
      y += t * t;
    }
    absxk = fabs(x[2]);
    if (absxk > absx) {
      t = absx / absxk;
      b_y = b_y * t * t + 1.0;
      absx = absxk;
    } else {
      t = absxk / absx;
      b_y += t * t;
    }
    y = normGradF * sqrt(y);
    b_y = absx * sqrt(b_y);
    if (y < 1.0E-6 * (b_y + 1.4901161193847656E-8)) {
      exitflag = 4;
      if (!stepSuccessful) {
        (*iter)++;
      }
    } else if (funDiff <= 1.0E-6) {
      exitflag = 3;
    } else {
      exitflag = -5;
    }
  }
  return exitflag;
}

/*
 * File trailer for checkStoppingCriteria.c
 *
 * [EOF]
 */
