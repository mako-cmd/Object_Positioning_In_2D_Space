/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: test.c
 *
 * MATLAB Coder version            : 5.4
 * C/C++ source code generated on  : 14-Oct-2022 16:21:02
 */

/* Include Files */
#include "test.h"
#include "checkStoppingCriteria.h"
#include "computeForwardDifferences.h"
#include "linearLeastSquares.h"
#include "rt_nonfinite.h"
#include "sys_x.h"
#include "test_data.h"
#include "test_initialize.h"
#include "test_internal_types.h"
#include "test_rtwutil.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
/*
 * Generate plot for Source @ mic 2
 *
 * Arguments    : double x[3]
 * Return Type  : void
 */
double* test(double x[3])
{
  struct_T FiniteDifferences;
  struct_T obj;
  double augJacobian[18];
  double JacCeqTrans[9];
  double rhs[6];
  double dx[3];
  double fval[3];
  double gradf[3];
  double b_gamma;
  double c;
  double funDiff;
  double normGradF;
  double relFactor;
  double resnorm;
  int aIdx;
  int bIdx;
  int exitflag;
  int funcCount;
  int iter;
  boolean_T exitg1;
  boolean_T stepSuccessful;
  if (!isInitialized_test) {
    test_initialize();
  }
  funDiff = rtInf;
  iter = 0;
  dx[0] = rtInf;
  x[0] = 0.0;
  dx[1] = rtInf;
  x[1] = -2.5E-5;
  dx[2] = rtInf;
  x[2] = 0.0;
  sys_x(gradf);
  resnorm = 0.0;
  for (bIdx = 0; bIdx < 3; bIdx++) {
    c = gradf[bIdx];
    fval[bIdx] = c;
    resnorm += c * c;
  }
  obj.f_1 = 0.0;
  obj.f_2 = 0.0;
  obj.nVar = 3;
  obj.mIneq = 0;
  obj.mEq = 3;
  obj.numEvals = 0;
  obj.SpecifyObjectiveGradient = false;
  obj.SpecifyConstraintGradient = false;
  obj.isEmptyNonlcon = false;
  obj.hasBounds = false;
  obj.FiniteDifferenceType = 0;
  obj.cEq_1[0] = 0.0;
  obj.cEq_2[0] = 0.0;
  obj.hasLB[0] = false;
  obj.hasUB[0] = false;
  gradf[0] = 0.0;
  obj.cEq_1[1] = 0.0;
  obj.cEq_2[1] = 0.0;
  obj.hasLB[1] = false;
  obj.hasUB[1] = false;
  gradf[1] = -2.5E-5;
  obj.cEq_1[2] = 0.0;
  obj.cEq_2[2] = 0.0;
  obj.hasLB[2] = false;
  obj.hasUB[2] = false;
  gradf[2] = 0.0;
  computeForwardDifferences(&obj, fval, gradf, JacCeqTrans);
  funcCount = obj.numEvals + 1;
  b_gamma = 0.01;
  for (bIdx = 0; bIdx < 3; bIdx++) {
    augJacobian[6 * bIdx] = JacCeqTrans[bIdx];
    augJacobian[6 * bIdx + 1] = JacCeqTrans[bIdx + 3];
    augJacobian[6 * bIdx + 2] = JacCeqTrans[bIdx + 6];
    exitflag = 6 * (bIdx + 1);
    augJacobian[exitflag - 3] = 0.0;
    augJacobian[exitflag - 2] = 0.0;
    augJacobian[exitflag - 1] = 0.0;
    augJacobian[(bIdx + 6 * bIdx) + 3] = 0.1;
  }
  for (exitflag = 0; exitflag < 3; exitflag++) {
    aIdx = exitflag * 6;
    bIdx = exitflag * 3;
    JacCeqTrans[bIdx] = augJacobian[aIdx];
    JacCeqTrans[bIdx + 1] = augJacobian[aIdx + 1];
    JacCeqTrans[bIdx + 2] = augJacobian[aIdx + 2];
    gradf[exitflag] = 0.0;
  }
  for (aIdx = 0; aIdx <= 6; aIdx += 3) {
    c = 0.0;
    exitflag = aIdx + 3;
    for (bIdx = aIdx + 1; bIdx <= exitflag; bIdx++) {
      c += JacCeqTrans[bIdx - 1] * fval[(bIdx - aIdx) - 1];
    }
    exitflag = div_nde_s32_floor(aIdx, 3);
    gradf[exitflag] += c;
  }
  c = 0.0;
  stepSuccessful = true;
  normGradF = 0.0;
  relFactor = fabs(gradf[0]);
  if (rtIsNaN(relFactor) || (relFactor > 0.0)) {
    c = relFactor;
  }
  if (rtIsNaN(relFactor) || (relFactor > 0.0)) {
    normGradF = relFactor;
  }
  relFactor = fabs(gradf[1]);
  if (rtIsNaN(relFactor) || (relFactor > c)) {
    c = relFactor;
  }
  if (rtIsNaN(relFactor) || (relFactor > normGradF)) {
    normGradF = relFactor;
  }
  relFactor = fabs(gradf[2]);
  if (rtIsNaN(relFactor) || (relFactor > c)) {
    c = relFactor;
  }
  if (rtIsNaN(relFactor) || (relFactor > normGradF)) {
    normGradF = relFactor;
  }
  relFactor = fmax(c, 1.0);
  if (normGradF <= 1.0E-10 * relFactor) {
    exitflag = 1;
  } else if (obj.numEvals + 1 >= 3000000) {
    exitflag = 0;
  } else {
    exitflag = -5;
  }
  exitg1 = false;
  while ((!exitg1) && (exitflag == -5)) {
    double fNew[3];
    double xp[3];
    boolean_T evalOK;
    boolean_T guard1 = false;
    rhs[0] = -fval[0];
    rhs[3] = 0.0;
    rhs[1] = -fval[1];
    rhs[4] = 0.0;
    rhs[2] = -fval[2];
    rhs[5] = 0.0;
    linearLeastSquares(augJacobian, rhs, dx);
    xp[0] = x[0] + dx[0];
    xp[1] = x[1] + dx[1];
    xp[2] = x[2] + dx[2];
    b_sys_x(xp, gradf);
    fNew[0] = gradf[0];
    evalOK = ((!rtIsInf(gradf[0])) && (!rtIsNaN(gradf[0])));
    fNew[1] = gradf[1];
    if ((!evalOK) || (rtIsInf(gradf[1]) || rtIsNaN(gradf[1]))) {
      evalOK = false;
    }
    fNew[2] = gradf[2];
    c = (gradf[0] * gradf[0] + gradf[1] * gradf[1]) + gradf[2] * gradf[2];
    if ((!evalOK) || (rtIsInf(gradf[2]) || rtIsNaN(gradf[2]))) {
      evalOK = false;
    }
    funcCount++;
    guard1 = false;
    if ((c < resnorm) && evalOK) {
      iter++;
      funDiff = fabs(c - resnorm) / resnorm;
      resnorm = c;
      gradf[0] = xp[0];
      gradf[1] = xp[1];
      gradf[2] = xp[2];
      FiniteDifferences = obj;
      evalOK = computeForwardDifferences(&FiniteDifferences, fNew, gradf,
                                         JacCeqTrans);
      funcCount += FiniteDifferences.numEvals;
      for (exitflag = 0; exitflag < 3; exitflag++) {
        augJacobian[6 * exitflag] = JacCeqTrans[exitflag];
        augJacobian[6 * exitflag + 1] = JacCeqTrans[exitflag + 3];
        augJacobian[6 * exitflag + 2] = JacCeqTrans[exitflag + 6];
        fval[exitflag] = fNew[exitflag];
      }
      for (exitflag = 0; exitflag < 3; exitflag++) {
        aIdx = exitflag * 6;
        bIdx = exitflag * 3;
        JacCeqTrans[bIdx] = augJacobian[aIdx];
        JacCeqTrans[bIdx + 1] = augJacobian[aIdx + 1];
        JacCeqTrans[bIdx + 2] = augJacobian[aIdx + 2];
      }
      if (evalOK) {
        x[0] = xp[0];
        x[1] = xp[1];
        x[2] = xp[2];
        if (stepSuccessful) {
          b_gamma *= 0.1;
        }
        stepSuccessful = true;
        guard1 = true;
      } else {
        exitg1 = true;
      }
    } else {
      b_gamma *= 10.0;
      stepSuccessful = false;
      for (exitflag = 0; exitflag < 3; exitflag++) {
        aIdx = exitflag * 3;
        bIdx = exitflag * 6;
        augJacobian[bIdx] = JacCeqTrans[aIdx];
        augJacobian[bIdx + 1] = JacCeqTrans[aIdx + 1];
        augJacobian[bIdx + 2] = JacCeqTrans[aIdx + 2];
      }
      guard1 = true;
    }
    if (guard1) {
      c = sqrt(b_gamma);
      for (bIdx = 0; bIdx < 3; bIdx++) {
        exitflag = 6 * (bIdx + 1);
        augJacobian[exitflag - 3] = 0.0;
        augJacobian[exitflag - 2] = 0.0;
        augJacobian[exitflag - 1] = 0.0;
        augJacobian[(bIdx + 6 * bIdx) + 3] = c;
        gradf[bIdx] = 0.0;
      }
      for (aIdx = 0; aIdx <= 6; aIdx += 3) {
        c = 0.0;
        exitflag = aIdx + 3;
        for (bIdx = aIdx + 1; bIdx <= exitflag; bIdx++) {
          c += JacCeqTrans[bIdx - 1] * fval[(bIdx - aIdx) - 1];
        }
        exitflag = div_nde_s32_floor(aIdx, 3);
        gradf[exitflag] += c;
      }
      exitflag = checkStoppingCriteria(gradf, relFactor, funDiff, x, dx,
                                       funcCount, stepSuccessful, &iter);
      if (exitflag != -5) {
        exitg1 = true;
      }
    }
  }
  return x;
}

/*
 * File trailer for test.c
 *
 * [EOF]
 */
