/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: computeForwardDifferences.c
 *
 * MATLAB Coder version            : 5.4
 * C/C++ source code generated on  : 14-Oct-2022 23:07:56
 */

/* Include Files */
#include "computeForwardDifferences.h"
#include "rt_nonfinite.h"
#include "sys_x.h"
#include "test_internal_types.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : struct_T *obj
 *                const double cEqCurrent[3]
 *                double xk[3]
 *                double JacCeqTrans[9]
 * Return Type  : boolean_T
 */
boolean_T computeForwardDifferences(struct_T *obj, const double cEqCurrent[3],
                                    double xk[3], double JacCeqTrans[9])
{
  int idx;
  boolean_T evalOK;
  boolean_T exitg1;
  evalOK = true;
  obj->numEvals = 0;
  idx = 0;
  exitg1 = false;
  while ((!exitg1) && (idx < 3)) {
    double deltaX;
    double temp;
    int b_idx;
    boolean_T guard1 = false;
    deltaX = 1.4901161193847656E-8 * (1.0 - 2.0 * (double)(xk[idx] < 0.0)) *
             fmax(fabs(xk[idx]), 1.0);
    evalOK = true;
    temp = xk[idx];
    xk[idx] += deltaX;
    sys_x(xk, obj->cEq_1);
    b_idx = 0;
    while (evalOK && (b_idx + 1 <= 3)) {
      evalOK = ((!rtIsInf(obj->cEq_1[b_idx])) && (!rtIsNaN(obj->cEq_1[b_idx])));
      b_idx++;
    }
    xk[idx] = temp;
    obj->f_1 = 0.0;
    obj->numEvals++;
    guard1 = false;
    if (!evalOK) {
      deltaX = -deltaX;
      evalOK = true;
      temp = xk[idx];
      xk[idx] += deltaX;
      sys_x(xk, obj->cEq_1);
      b_idx = 0;
      while (evalOK && (b_idx + 1 <= 3)) {
        evalOK =
            ((!rtIsInf(obj->cEq_1[b_idx])) && (!rtIsNaN(obj->cEq_1[b_idx])));
        b_idx++;
      }
      xk[idx] = temp;
      obj->f_1 = 0.0;
      obj->numEvals++;
      if (!evalOK) {
        exitg1 = true;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }
    if (guard1) {
      JacCeqTrans[idx] = (obj->cEq_1[0] - cEqCurrent[0]) / deltaX;
      JacCeqTrans[idx + 3] = (obj->cEq_1[1] - cEqCurrent[1]) / deltaX;
      JacCeqTrans[idx + 6] = (obj->cEq_1[2] - cEqCurrent[2]) / deltaX;
      idx++;
    }
  }
  return evalOK;
}

/*
 * File trailer for computeForwardDifferences.c
 *
 * [EOF]
 */
