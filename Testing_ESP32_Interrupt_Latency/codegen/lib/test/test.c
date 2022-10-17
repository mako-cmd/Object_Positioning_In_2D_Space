/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: test.c
 *
 * MATLAB Coder version            : 5.4
 * C/C++ source code generated on  : 14-Oct-2022 23:07:56
 */

/* Include Files */
#include "test.h"
#include "checkStoppingCriteria.h"
#include "computeForwardDifferences.h"
#include "fgetl.h"
#include "fileManager.h"
#include "fsolve.h"
#include "linearLeastSquares.h"
#include "rt_nonfinite.h"
#include "sys_x.h"
#include "test_data.h"
#include "test_emxutil.h"
#include "test_initialize.h"
#include "test_internal_types.h"
#include "test_rtwutil.h"
#include "test_types.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <stdio.h>

/* Function Definitions */
/*
 * Generate plot for Source @ mic 2
 *
 * Arguments    : double x_data[]
 *                int x_size[2]
 * Return Type  : void
 */
void test(double x_data[], int x_size[2])
{
  emxArray_char_T *in;
  struct_T FiniteDifferences;
  struct_T obj;
  double augJacobian[18];
  double JacCeqTrans[9];
  double rhs[6];
  double dx[3];
  double fNew[3];
  double gradf[3];
  double x1[3];
  double x6[3];
  double xp[3];
  double absx;
  double b_gamma;
  double c;
  double funDiff;
  double resnorm;
  double resnormNew;
  int aIdx;
  int bIdx;
  int b_i;
  int funcCount;
  int i;
  int iter;
  signed char fileid;
  char *in_data;
  boolean_T b_x_data[3];
  boolean_T exitg1;
  boolean_T stepSuccessful;
  if (!isInitialized_test) {
    test_initialize();
  }
  emxInit_char_T(&in);
  /*  Get solutions, get variety by varying starting point in different
   * quadrants of xyz plane  */
  funDiff = rtInf;
  iter = 0;
  dx[0] = rtInf;
  x1[0] = 0.0;
  dx[1] = rtInf;
  x1[1] = -100.0;
  dx[2] = rtInf;
  x1[2] = 0.0;
  /*  x = x(1) */
  /*  y = x(2) */
  /*  t = x(3) */
  fileid = cfopen("mic_1.dat");
  fgetl(fileid, in);
  in_data = in->data;
  c = 0.0;
  i = in->size[1];
  for (b_i = 0; b_i < i; b_i++) {
    c += ((double)(unsigned char)in_data[b_i] - 48.0) *
         rt_powd_snf(10.0, (in->size[1] - b_i) - 1);
  }
  cfclose(fileid);
  fileid = cfopen("mic_2.dat");
  fgetl(fileid, in);
  in_data = in->data;
  resnormNew = 0.0;
  i = in->size[1];
  for (b_i = 0; b_i < i; b_i++) {
    resnormNew += ((double)(unsigned char)in_data[b_i] - 48.0) *
                  rt_powd_snf(10.0, (in->size[1] - b_i) - 1);
  }
  cfclose(fileid);
  fileid = cfopen("mic_3.dat");
  fgetl(fileid, in);
  in_data = in->data;
  absx = 0.0;
  i = in->size[1];
  for (b_i = 0; b_i < i; b_i++) {
    absx += ((double)(unsigned char)in_data[b_i] - 48.0) *
            rt_powd_snf(10.0, (in->size[1] - b_i) - 1);
  }
  emxFree_char_T(&in);
  cfclose(fileid);
  c = 330.0 * (c * 1.0E-6);
  gradf[0] = 9950.0625 - c * c;
  c = 330.0 * (resnormNew * 1.0E-6);
  gradf[1] = 10000.0 - c * c;
  c = 330.0 * (absx * 1.0E-6);
  gradf[2] = 10000.0625 - c * c;
  resnorm = 0.0;
  for (b_i = 0; b_i < 3; b_i++) {
    c = gradf[b_i];
    x6[b_i] = c;
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
  gradf[1] = -100.0;
  obj.cEq_1[2] = 0.0;
  obj.cEq_2[2] = 0.0;
  obj.hasLB[2] = false;
  obj.hasUB[2] = false;
  gradf[2] = 0.0;
  computeForwardDifferences(&obj, x6, gradf, JacCeqTrans);
  funcCount = obj.numEvals + 1;
  b_gamma = 0.01;
  for (b_i = 0; b_i < 3; b_i++) {
    augJacobian[6 * b_i] = JacCeqTrans[b_i];
    augJacobian[6 * b_i + 1] = JacCeqTrans[b_i + 3];
    augJacobian[6 * b_i + 2] = JacCeqTrans[b_i + 6];
    aIdx = 6 * (b_i + 1);
    augJacobian[aIdx - 3] = 0.0;
    augJacobian[aIdx - 2] = 0.0;
    augJacobian[aIdx - 1] = 0.0;
    augJacobian[(b_i + 6 * b_i) + 3] = 0.1;
  }
  for (b_i = 0; b_i < 3; b_i++) {
    aIdx = b_i * 6;
    bIdx = b_i * 3;
    JacCeqTrans[bIdx] = augJacobian[aIdx];
    JacCeqTrans[bIdx + 1] = augJacobian[aIdx + 1];
    JacCeqTrans[bIdx + 2] = augJacobian[aIdx + 2];
    gradf[b_i] = 0.0;
  }
  for (bIdx = 0; bIdx <= 6; bIdx += 3) {
    c = 0.0;
    i = bIdx + 3;
    for (aIdx = bIdx + 1; aIdx <= i; aIdx++) {
      c += JacCeqTrans[aIdx - 1] * x6[(aIdx - bIdx) - 1];
    }
    aIdx = div_nde_s32_floor(bIdx, 3);
    gradf[aIdx] += c;
  }
  resnormNew = 0.0;
  absx = fabs(gradf[0]);
  if (rtIsNaN(absx) || (absx > 0.0)) {
    resnormNew = absx;
  }
  absx = fabs(gradf[1]);
  if (rtIsNaN(absx) || (absx > resnormNew)) {
    resnormNew = absx;
  }
  absx = fabs(gradf[2]);
  if (rtIsNaN(absx) || (absx > resnormNew)) {
    resnormNew = absx;
  }
  absx = fmax(resnormNew, 1.0);
  stepSuccessful = true;
  aIdx = checkStoppingCriteria(gradf, absx, obj.numEvals + 1);
  exitg1 = false;
  while ((!exitg1) && (aIdx == -5)) {
    boolean_T evalOK;
    boolean_T guard1 = false;
    rhs[0] = -x6[0];
    rhs[3] = 0.0;
    rhs[1] = -x6[1];
    rhs[4] = 0.0;
    rhs[2] = -x6[2];
    rhs[5] = 0.0;
    linearLeastSquares(augJacobian, rhs, dx);
    xp[0] = x1[0] + dx[0];
    xp[1] = x1[1] + dx[1];
    xp[2] = x1[2] + dx[2];
    sys_x(xp, gradf);
    fNew[0] = gradf[0];
    evalOK = ((!rtIsInf(gradf[0])) && (!rtIsNaN(gradf[0])));
    fNew[1] = gradf[1];
    if ((!evalOK) || (rtIsInf(gradf[1]) || rtIsNaN(gradf[1]))) {
      evalOK = false;
    }
    fNew[2] = gradf[2];
    resnormNew =
        (gradf[0] * gradf[0] + gradf[1] * gradf[1]) + gradf[2] * gradf[2];
    if ((!evalOK) || (rtIsInf(gradf[2]) || rtIsNaN(gradf[2]))) {
      evalOK = false;
    }
    funcCount++;
    guard1 = false;
    if ((resnormNew < resnorm) && evalOK) {
      iter++;
      funDiff = fabs(resnormNew - resnorm) / resnorm;
      resnorm = resnormNew;
      gradf[0] = xp[0];
      gradf[1] = xp[1];
      gradf[2] = xp[2];
      FiniteDifferences = obj;
      evalOK = computeForwardDifferences(&FiniteDifferences, fNew, gradf,
                                         JacCeqTrans);
      funcCount += FiniteDifferences.numEvals;
      for (i = 0; i < 3; i++) {
        augJacobian[6 * i] = JacCeqTrans[i];
        augJacobian[6 * i + 1] = JacCeqTrans[i + 3];
        augJacobian[6 * i + 2] = JacCeqTrans[i + 6];
        x6[i] = fNew[i];
      }
      for (b_i = 0; b_i < 3; b_i++) {
        aIdx = b_i * 6;
        bIdx = b_i * 3;
        JacCeqTrans[bIdx] = augJacobian[aIdx];
        JacCeqTrans[bIdx + 1] = augJacobian[aIdx + 1];
        JacCeqTrans[bIdx + 2] = augJacobian[aIdx + 2];
      }
      if (evalOK) {
        x1[0] = xp[0];
        x1[1] = xp[1];
        x1[2] = xp[2];
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
      for (b_i = 0; b_i < 3; b_i++) {
        aIdx = b_i * 3;
        bIdx = b_i * 6;
        augJacobian[bIdx] = JacCeqTrans[aIdx];
        augJacobian[bIdx + 1] = JacCeqTrans[aIdx + 1];
        augJacobian[bIdx + 2] = JacCeqTrans[aIdx + 2];
      }
      guard1 = true;
    }
    if (guard1) {
      c = sqrt(b_gamma);
      for (b_i = 0; b_i < 3; b_i++) {
        aIdx = 6 * (b_i + 1);
        augJacobian[aIdx - 3] = 0.0;
        augJacobian[aIdx - 2] = 0.0;
        augJacobian[aIdx - 1] = 0.0;
        augJacobian[(b_i + 6 * b_i) + 3] = c;
        gradf[b_i] = 0.0;
      }
      for (bIdx = 0; bIdx <= 6; bIdx += 3) {
        c = 0.0;
        i = bIdx + 3;
        for (aIdx = bIdx + 1; aIdx <= i; aIdx++) {
          c += JacCeqTrans[aIdx - 1] * x6[(aIdx - bIdx) - 1];
        }
        aIdx = div_nde_s32_floor(bIdx, 3);
        gradf[aIdx] += c;
      }
      aIdx = b_checkStoppingCriteria(gradf, absx, funDiff, x1, dx, funcCount,
                                     stepSuccessful, &iter);
      if (aIdx != -5) {
        exitg1 = true;
      }
    }
  }
  fsolve(gradf);
  b_fsolve(fNew);
  c_fsolve(xp);
  d_fsolve(dx);
  e_fsolve(x6);
  /*  figure(1); */
  /*  plot(x1(1),x1(2),'o',LineWidth=5,Color='r'); */
  /*  hold on; */
  /*  plot(x2(1),x2(2),'o',LineWidth=5,Color='g'); */
  /*  hold on; */
  /*  plot(x3(1),x3(2),'o',LineWidth=5,Color='b'); */
  /*  hold on; */
  /*  plot(x4(1),x4(2),'o',LineWidth=5,Color='c'); */
  /*  hold on; */
  /*  plot(x5(1),x5(2),'o',LineWidth=5,Color='m'); */
  /*  hold on; */
  /*  plot(x6(1),x6(2),'o',LineWidth=5,Color='y'); */
  /*  axis([0 0.3 -0.3 0]); */
  /*  Init output var */
  x_size[0] = 1;
  x_size[1] = 1;
  x_data[0] = 0.0;
  /*  Select valid solution:  A valid solution will have x as positive, y as */
  /*  negativ and t as positive (duh) */
  /*  ***Remember x(1) = x, x(2) = y, x(3) = t */
  if ((x1[0] > 0.0) && (x1[1] < 0.0) && (x1[2] > 0.0)) {
    x_size[0] = 1;
    x_size[1] = 3;
    x_data[0] = x1[0];
    x_data[1] = x1[1];
    x_data[2] = x1[2];
  } else if ((gradf[0] > 0.0) && (gradf[1] < 0.0) && (gradf[2] > 0.0)) {
    x_size[0] = 1;
    x_size[1] = 3;
    x_data[0] = gradf[0];
    x_data[1] = gradf[1];
    x_data[2] = gradf[2];
  } else if ((fNew[0] > 0.0) && (fNew[1] < 0.0) && (fNew[2] > 0.0)) {
    x_size[0] = 1;
    x_size[1] = 3;
    x_data[0] = fNew[0];
    x_data[1] = fNew[1];
    x_data[2] = fNew[2];
  } else if ((xp[0] > 0.0) && (xp[1] < 0.0) && (xp[2] > 0.0)) {
    x_size[0] = 1;
    x_size[1] = 3;
    x_data[0] = xp[0];
    x_data[1] = xp[1];
    x_data[2] = xp[2];
  } else if ((dx[0] > 0.0) && (dx[1] < 0.0) && (dx[2] > 0.0)) {
    x_size[0] = 1;
    x_size[1] = 3;
    x_data[0] = dx[0];
    x_data[1] = dx[1];
    x_data[2] = dx[2];
  } else if ((x6[0] > 0.0) && (x6[1] < 0.0) && (x6[2] > 0.0)) {
    x_size[0] = 1;
    x_size[1] = 3;
    x_data[0] = x6[0];
    x_data[1] = x6[1];
    x_data[2] = x6[2];
  }
  bIdx = x_size[1];
  aIdx = x_size[1];
  for (i = 0; i < aIdx; i++) {
    b_x_data[i] = (x_data[i] == 0.0);
  }
  stepSuccessful = true;
  aIdx = 0;
  exitg1 = false;
  while ((!exitg1) && (aIdx <= bIdx - 1)) {
    if (!b_x_data[aIdx]) {
      stepSuccessful = false;
      exitg1 = true;
    } else {
      aIdx++;
    }
  }
  if (stepSuccessful) {
    printf("%s\n", "ERROR: Invalid data!");
    fflush(stdout);
  }
}

/*
 * File trailer for test.c
 *
 * [EOF]
 */
