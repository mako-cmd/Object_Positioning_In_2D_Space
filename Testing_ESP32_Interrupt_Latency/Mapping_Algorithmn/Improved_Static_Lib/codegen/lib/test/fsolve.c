/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: fsolve.c
 *
 * MATLAB Coder version            : 5.4
 * C/C++ source code generated on  : 14-Oct-2022 23:07:56
 */

/* Include Files */
#include "fsolve.h"
#include "checkStoppingCriteria.h"
#include "computeForwardDifferences.h"
#include "fgetl.h"
#include "fileManager.h"
#include "linearLeastSquares.h"
#include "rt_nonfinite.h"
#include "sys_x.h"
#include "test_emxutil.h"
#include "test_internal_types.h"
#include "test_rtwutil.h"
#include "test_types.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : double x[3]
 * Return Type  : void
 */
void b_fsolve(double x[3])
{
  emxArray_char_T *in;
  struct_T FiniteDifferences;
  struct_T obj;
  double augJacobian[18];
  double JacCeqTrans[9];
  double rhs[6];
  double dx[3];
  double fval[3];
  double gradf[3];
  double absx;
  double b_gamma;
  double c;
  double funDiff;
  double resnorm;
  double resnormNew;
  int aIdx;
  int bIdx;
  int funcCount;
  int i;
  int iter;
  signed char fileid;
  char *in_data;
  boolean_T exitg1;
  boolean_T stepSuccessful;
  emxInit_char_T(&in);
  funDiff = rtInf;
  iter = 0;
  dx[0] = rtInf;
  x[0] = 0.0;
  dx[1] = rtInf;
  x[1] = 0.0;
  dx[2] = rtInf;
  x[2] = -100.0;
  /*  x = x(1) */
  /*  y = x(2) */
  /*  t = x(3) */
  fileid = cfopen("mic_1.dat");
  fgetl(fileid, in);
  in_data = in->data;
  c = 0.0;
  bIdx = in->size[1];
  for (i = 0; i < bIdx; i++) {
    c += ((double)(unsigned char)in_data[i] - 48.0) *
         rt_powd_snf(10.0, (in->size[1] - i) - 1);
  }
  cfclose(fileid);
  fileid = cfopen("mic_2.dat");
  fgetl(fileid, in);
  in_data = in->data;
  resnormNew = 0.0;
  bIdx = in->size[1];
  for (i = 0; i < bIdx; i++) {
    resnormNew += ((double)(unsigned char)in_data[i] - 48.0) *
                  rt_powd_snf(10.0, (in->size[1] - i) - 1);
  }
  cfclose(fileid);
  fileid = cfopen("mic_3.dat");
  fgetl(fileid, in);
  in_data = in->data;
  absx = 0.0;
  bIdx = in->size[1];
  for (i = 0; i < bIdx; i++) {
    absx += ((double)(unsigned char)in_data[i] - 48.0) *
            rt_powd_snf(10.0, (in->size[1] - i) - 1);
  }
  emxFree_char_T(&in);
  cfclose(fileid);
  c = 330.0 * (c * 1.0E-6 + -100.0);
  gradf[0] = 0.0625 - c * c;
  c = 330.0 * (resnormNew * 1.0E-6 + -100.0);
  gradf[1] = 0.0 - c * c;
  c = 330.0 * (absx * 1.0E-6 + -100.0);
  gradf[2] = 0.0625 - c * c;
  resnorm = 0.0;
  for (i = 0; i < 3; i++) {
    c = gradf[i];
    fval[i] = c;
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
  gradf[1] = 0.0;
  obj.cEq_1[2] = 0.0;
  obj.cEq_2[2] = 0.0;
  obj.hasLB[2] = false;
  obj.hasUB[2] = false;
  gradf[2] = -100.0;
  computeForwardDifferences(&obj, fval, gradf, JacCeqTrans);
  funcCount = obj.numEvals + 1;
  b_gamma = 0.01;
  for (i = 0; i < 3; i++) {
    augJacobian[6 * i] = JacCeqTrans[i];
    augJacobian[6 * i + 1] = JacCeqTrans[i + 3];
    augJacobian[6 * i + 2] = JacCeqTrans[i + 6];
    aIdx = 6 * (i + 1);
    augJacobian[aIdx - 3] = 0.0;
    augJacobian[aIdx - 2] = 0.0;
    augJacobian[aIdx - 1] = 0.0;
    augJacobian[(i + 6 * i) + 3] = 0.1;
  }
  for (i = 0; i < 3; i++) {
    aIdx = i * 6;
    bIdx = i * 3;
    JacCeqTrans[bIdx] = augJacobian[aIdx];
    JacCeqTrans[bIdx + 1] = augJacobian[aIdx + 1];
    JacCeqTrans[bIdx + 2] = augJacobian[aIdx + 2];
    gradf[i] = 0.0;
  }
  for (i = 0; i <= 6; i += 3) {
    c = 0.0;
    bIdx = i + 3;
    for (aIdx = i + 1; aIdx <= bIdx; aIdx++) {
      c += JacCeqTrans[aIdx - 1] * fval[(aIdx - i) - 1];
    }
    aIdx = div_nde_s32_floor(i, 3);
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
      for (bIdx = 0; bIdx < 3; bIdx++) {
        augJacobian[6 * bIdx] = JacCeqTrans[bIdx];
        augJacobian[6 * bIdx + 1] = JacCeqTrans[bIdx + 3];
        augJacobian[6 * bIdx + 2] = JacCeqTrans[bIdx + 6];
        fval[bIdx] = fNew[bIdx];
      }
      for (i = 0; i < 3; i++) {
        aIdx = i * 6;
        bIdx = i * 3;
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
      for (i = 0; i < 3; i++) {
        aIdx = i * 3;
        bIdx = i * 6;
        augJacobian[bIdx] = JacCeqTrans[aIdx];
        augJacobian[bIdx + 1] = JacCeqTrans[aIdx + 1];
        augJacobian[bIdx + 2] = JacCeqTrans[aIdx + 2];
      }
      guard1 = true;
    }
    if (guard1) {
      c = sqrt(b_gamma);
      for (i = 0; i < 3; i++) {
        aIdx = 6 * (i + 1);
        augJacobian[aIdx - 3] = 0.0;
        augJacobian[aIdx - 2] = 0.0;
        augJacobian[aIdx - 1] = 0.0;
        augJacobian[(i + 6 * i) + 3] = c;
        gradf[i] = 0.0;
      }
      for (i = 0; i <= 6; i += 3) {
        c = 0.0;
        bIdx = i + 3;
        for (aIdx = i + 1; aIdx <= bIdx; aIdx++) {
          c += JacCeqTrans[aIdx - 1] * fval[(aIdx - i) - 1];
        }
        aIdx = div_nde_s32_floor(i, 3);
        gradf[aIdx] += c;
      }
      aIdx = b_checkStoppingCriteria(gradf, absx, funDiff, x, dx, funcCount,
                                     stepSuccessful, &iter);
      if (aIdx != -5) {
        exitg1 = true;
      }
    }
  }
}

/*
 * Arguments    : double x[3]
 * Return Type  : void
 */
void c_fsolve(double x[3])
{
  emxArray_char_T *in;
  struct_T FiniteDifferences;
  struct_T obj;
  double augJacobian[18];
  double JacCeqTrans[9];
  double rhs[6];
  double dx[3];
  double fval[3];
  double gradf[3];
  double absx;
  double b_gamma;
  double c;
  double funDiff;
  double resnorm;
  double resnormNew;
  int aIdx;
  int bIdx;
  int funcCount;
  int i;
  int iter;
  signed char fileid;
  char *in_data;
  boolean_T exitg1;
  boolean_T stepSuccessful;
  emxInit_char_T(&in);
  funDiff = rtInf;
  iter = 0;
  dx[0] = rtInf;
  x[0] = 0.0;
  dx[1] = rtInf;
  x[1] = 100.0;
  dx[2] = rtInf;
  x[2] = 0.0;
  /*  x = x(1) */
  /*  y = x(2) */
  /*  t = x(3) */
  fileid = cfopen("mic_1.dat");
  fgetl(fileid, in);
  in_data = in->data;
  c = 0.0;
  bIdx = in->size[1];
  for (i = 0; i < bIdx; i++) {
    c += ((double)(unsigned char)in_data[i] - 48.0) *
         rt_powd_snf(10.0, (in->size[1] - i) - 1);
  }
  cfclose(fileid);
  fileid = cfopen("mic_2.dat");
  fgetl(fileid, in);
  in_data = in->data;
  resnormNew = 0.0;
  bIdx = in->size[1];
  for (i = 0; i < bIdx; i++) {
    resnormNew += ((double)(unsigned char)in_data[i] - 48.0) *
                  rt_powd_snf(10.0, (in->size[1] - i) - 1);
  }
  cfclose(fileid);
  fileid = cfopen("mic_3.dat");
  fgetl(fileid, in);
  in_data = in->data;
  absx = 0.0;
  bIdx = in->size[1];
  for (i = 0; i < bIdx; i++) {
    absx += ((double)(unsigned char)in_data[i] - 48.0) *
            rt_powd_snf(10.0, (in->size[1] - i) - 1);
  }
  emxFree_char_T(&in);
  cfclose(fileid);
  c = 330.0 * (c * 1.0E-6);
  gradf[0] = 10050.0625 - c * c;
  c = 330.0 * (resnormNew * 1.0E-6);
  gradf[1] = 10000.0 - c * c;
  c = 330.0 * (absx * 1.0E-6);
  gradf[2] = 10000.0625 - c * c;
  resnorm = 0.0;
  for (i = 0; i < 3; i++) {
    c = gradf[i];
    fval[i] = c;
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
  gradf[1] = 100.0;
  obj.cEq_1[2] = 0.0;
  obj.cEq_2[2] = 0.0;
  obj.hasLB[2] = false;
  obj.hasUB[2] = false;
  gradf[2] = 0.0;
  computeForwardDifferences(&obj, fval, gradf, JacCeqTrans);
  funcCount = obj.numEvals + 1;
  b_gamma = 0.01;
  for (i = 0; i < 3; i++) {
    augJacobian[6 * i] = JacCeqTrans[i];
    augJacobian[6 * i + 1] = JacCeqTrans[i + 3];
    augJacobian[6 * i + 2] = JacCeqTrans[i + 6];
    aIdx = 6 * (i + 1);
    augJacobian[aIdx - 3] = 0.0;
    augJacobian[aIdx - 2] = 0.0;
    augJacobian[aIdx - 1] = 0.0;
    augJacobian[(i + 6 * i) + 3] = 0.1;
  }
  for (i = 0; i < 3; i++) {
    aIdx = i * 6;
    bIdx = i * 3;
    JacCeqTrans[bIdx] = augJacobian[aIdx];
    JacCeqTrans[bIdx + 1] = augJacobian[aIdx + 1];
    JacCeqTrans[bIdx + 2] = augJacobian[aIdx + 2];
    gradf[i] = 0.0;
  }
  for (i = 0; i <= 6; i += 3) {
    c = 0.0;
    bIdx = i + 3;
    for (aIdx = i + 1; aIdx <= bIdx; aIdx++) {
      c += JacCeqTrans[aIdx - 1] * fval[(aIdx - i) - 1];
    }
    aIdx = div_nde_s32_floor(i, 3);
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
      for (bIdx = 0; bIdx < 3; bIdx++) {
        augJacobian[6 * bIdx] = JacCeqTrans[bIdx];
        augJacobian[6 * bIdx + 1] = JacCeqTrans[bIdx + 3];
        augJacobian[6 * bIdx + 2] = JacCeqTrans[bIdx + 6];
        fval[bIdx] = fNew[bIdx];
      }
      for (i = 0; i < 3; i++) {
        aIdx = i * 6;
        bIdx = i * 3;
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
      for (i = 0; i < 3; i++) {
        aIdx = i * 3;
        bIdx = i * 6;
        augJacobian[bIdx] = JacCeqTrans[aIdx];
        augJacobian[bIdx + 1] = JacCeqTrans[aIdx + 1];
        augJacobian[bIdx + 2] = JacCeqTrans[aIdx + 2];
      }
      guard1 = true;
    }
    if (guard1) {
      c = sqrt(b_gamma);
      for (i = 0; i < 3; i++) {
        aIdx = 6 * (i + 1);
        augJacobian[aIdx - 3] = 0.0;
        augJacobian[aIdx - 2] = 0.0;
        augJacobian[aIdx - 1] = 0.0;
        augJacobian[(i + 6 * i) + 3] = c;
        gradf[i] = 0.0;
      }
      for (i = 0; i <= 6; i += 3) {
        c = 0.0;
        bIdx = i + 3;
        for (aIdx = i + 1; aIdx <= bIdx; aIdx++) {
          c += JacCeqTrans[aIdx - 1] * fval[(aIdx - i) - 1];
        }
        aIdx = div_nde_s32_floor(i, 3);
        gradf[aIdx] += c;
      }
      aIdx = b_checkStoppingCriteria(gradf, absx, funDiff, x, dx, funcCount,
                                     stepSuccessful, &iter);
      if (aIdx != -5) {
        exitg1 = true;
      }
    }
  }
}

/*
 * Arguments    : double x[3]
 * Return Type  : void
 */
void d_fsolve(double x[3])
{
  emxArray_char_T *in;
  struct_T FiniteDifferences;
  struct_T obj;
  double augJacobian[18];
  double JacCeqTrans[9];
  double rhs[6];
  double dx[3];
  double fval[3];
  double gradf[3];
  double absx;
  double b_gamma;
  double c;
  double funDiff;
  double resnorm;
  double resnormNew;
  int aIdx;
  int bIdx;
  int funcCount;
  int i;
  int iter;
  signed char fileid;
  char *in_data;
  boolean_T exitg1;
  boolean_T stepSuccessful;
  emxInit_char_T(&in);
  funDiff = rtInf;
  iter = 0;
  dx[0] = rtInf;
  x[0] = 100.0;
  dx[1] = rtInf;
  x[1] = 0.0;
  dx[2] = rtInf;
  x[2] = 0.0;
  /*  x = x(1) */
  /*  y = x(2) */
  /*  t = x(3) */
  fileid = cfopen("mic_1.dat");
  fgetl(fileid, in);
  in_data = in->data;
  c = 0.0;
  bIdx = in->size[1];
  for (i = 0; i < bIdx; i++) {
    c += ((double)(unsigned char)in_data[i] - 48.0) *
         rt_powd_snf(10.0, (in->size[1] - i) - 1);
  }
  cfclose(fileid);
  fileid = cfopen("mic_2.dat");
  fgetl(fileid, in);
  in_data = in->data;
  resnormNew = 0.0;
  bIdx = in->size[1];
  for (i = 0; i < bIdx; i++) {
    resnormNew += ((double)(unsigned char)in_data[i] - 48.0) *
                  rt_powd_snf(10.0, (in->size[1] - i) - 1);
  }
  cfclose(fileid);
  fileid = cfopen("mic_3.dat");
  fgetl(fileid, in);
  in_data = in->data;
  absx = 0.0;
  bIdx = in->size[1];
  for (i = 0; i < bIdx; i++) {
    absx += ((double)(unsigned char)in_data[i] - 48.0) *
            rt_powd_snf(10.0, (in->size[1] - i) - 1);
  }
  emxFree_char_T(&in);
  cfclose(fileid);
  c = 330.0 * (c * 1.0E-6);
  gradf[0] = 10000.0625 - c * c;
  c = 330.0 * (resnormNew * 1.0E-6);
  gradf[1] = 10000.0 - c * c;
  c = 330.0 * (absx * 1.0E-6);
  gradf[2] = 9950.0625 - c * c;
  resnorm = 0.0;
  for (i = 0; i < 3; i++) {
    c = gradf[i];
    fval[i] = c;
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
  gradf[0] = 100.0;
  obj.cEq_1[1] = 0.0;
  obj.cEq_2[1] = 0.0;
  obj.hasLB[1] = false;
  obj.hasUB[1] = false;
  gradf[1] = 0.0;
  obj.cEq_1[2] = 0.0;
  obj.cEq_2[2] = 0.0;
  obj.hasLB[2] = false;
  obj.hasUB[2] = false;
  gradf[2] = 0.0;
  computeForwardDifferences(&obj, fval, gradf, JacCeqTrans);
  funcCount = obj.numEvals + 1;
  b_gamma = 0.01;
  for (i = 0; i < 3; i++) {
    augJacobian[6 * i] = JacCeqTrans[i];
    augJacobian[6 * i + 1] = JacCeqTrans[i + 3];
    augJacobian[6 * i + 2] = JacCeqTrans[i + 6];
    aIdx = 6 * (i + 1);
    augJacobian[aIdx - 3] = 0.0;
    augJacobian[aIdx - 2] = 0.0;
    augJacobian[aIdx - 1] = 0.0;
    augJacobian[(i + 6 * i) + 3] = 0.1;
  }
  for (i = 0; i < 3; i++) {
    aIdx = i * 6;
    bIdx = i * 3;
    JacCeqTrans[bIdx] = augJacobian[aIdx];
    JacCeqTrans[bIdx + 1] = augJacobian[aIdx + 1];
    JacCeqTrans[bIdx + 2] = augJacobian[aIdx + 2];
    gradf[i] = 0.0;
  }
  for (i = 0; i <= 6; i += 3) {
    c = 0.0;
    bIdx = i + 3;
    for (aIdx = i + 1; aIdx <= bIdx; aIdx++) {
      c += JacCeqTrans[aIdx - 1] * fval[(aIdx - i) - 1];
    }
    aIdx = div_nde_s32_floor(i, 3);
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
      for (bIdx = 0; bIdx < 3; bIdx++) {
        augJacobian[6 * bIdx] = JacCeqTrans[bIdx];
        augJacobian[6 * bIdx + 1] = JacCeqTrans[bIdx + 3];
        augJacobian[6 * bIdx + 2] = JacCeqTrans[bIdx + 6];
        fval[bIdx] = fNew[bIdx];
      }
      for (i = 0; i < 3; i++) {
        aIdx = i * 6;
        bIdx = i * 3;
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
      for (i = 0; i < 3; i++) {
        aIdx = i * 3;
        bIdx = i * 6;
        augJacobian[bIdx] = JacCeqTrans[aIdx];
        augJacobian[bIdx + 1] = JacCeqTrans[aIdx + 1];
        augJacobian[bIdx + 2] = JacCeqTrans[aIdx + 2];
      }
      guard1 = true;
    }
    if (guard1) {
      c = sqrt(b_gamma);
      for (i = 0; i < 3; i++) {
        aIdx = 6 * (i + 1);
        augJacobian[aIdx - 3] = 0.0;
        augJacobian[aIdx - 2] = 0.0;
        augJacobian[aIdx - 1] = 0.0;
        augJacobian[(i + 6 * i) + 3] = c;
        gradf[i] = 0.0;
      }
      for (i = 0; i <= 6; i += 3) {
        c = 0.0;
        bIdx = i + 3;
        for (aIdx = i + 1; aIdx <= bIdx; aIdx++) {
          c += JacCeqTrans[aIdx - 1] * fval[(aIdx - i) - 1];
        }
        aIdx = div_nde_s32_floor(i, 3);
        gradf[aIdx] += c;
      }
      aIdx = b_checkStoppingCriteria(gradf, absx, funDiff, x, dx, funcCount,
                                     stepSuccessful, &iter);
      if (aIdx != -5) {
        exitg1 = true;
      }
    }
  }
}

/*
 * Arguments    : double x[3]
 * Return Type  : void
 */
void e_fsolve(double x[3])
{
  emxArray_char_T *in;
  struct_T FiniteDifferences;
  struct_T obj;
  double augJacobian[18];
  double JacCeqTrans[9];
  double rhs[6];
  double dx[3];
  double fval[3];
  double gradf[3];
  double absx;
  double b_gamma;
  double c;
  double funDiff;
  double resnorm;
  double resnormNew;
  int aIdx;
  int bIdx;
  int funcCount;
  int i;
  int iter;
  signed char fileid;
  char *in_data;
  boolean_T exitg1;
  boolean_T stepSuccessful;
  emxInit_char_T(&in);
  funDiff = rtInf;
  iter = 0;
  dx[0] = rtInf;
  x[0] = 0.0;
  dx[1] = rtInf;
  x[1] = 0.0;
  dx[2] = rtInf;
  x[2] = 100.0;
  /*  x = x(1) */
  /*  y = x(2) */
  /*  t = x(3) */
  fileid = cfopen("mic_1.dat");
  fgetl(fileid, in);
  in_data = in->data;
  c = 0.0;
  bIdx = in->size[1];
  for (i = 0; i < bIdx; i++) {
    c += ((double)(unsigned char)in_data[i] - 48.0) *
         rt_powd_snf(10.0, (in->size[1] - i) - 1);
  }
  cfclose(fileid);
  fileid = cfopen("mic_2.dat");
  fgetl(fileid, in);
  in_data = in->data;
  resnormNew = 0.0;
  bIdx = in->size[1];
  for (i = 0; i < bIdx; i++) {
    resnormNew += ((double)(unsigned char)in_data[i] - 48.0) *
                  rt_powd_snf(10.0, (in->size[1] - i) - 1);
  }
  cfclose(fileid);
  fileid = cfopen("mic_3.dat");
  fgetl(fileid, in);
  in_data = in->data;
  absx = 0.0;
  bIdx = in->size[1];
  for (i = 0; i < bIdx; i++) {
    absx += ((double)(unsigned char)in_data[i] - 48.0) *
            rt_powd_snf(10.0, (in->size[1] - i) - 1);
  }
  emxFree_char_T(&in);
  cfclose(fileid);
  c = 330.0 * (c * 1.0E-6 + 100.0);
  gradf[0] = 0.0625 - c * c;
  c = 330.0 * (resnormNew * 1.0E-6 + 100.0);
  gradf[1] = 0.0 - c * c;
  c = 330.0 * (absx * 1.0E-6 + 100.0);
  gradf[2] = 0.0625 - c * c;
  resnorm = 0.0;
  for (i = 0; i < 3; i++) {
    c = gradf[i];
    fval[i] = c;
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
  gradf[1] = 0.0;
  obj.cEq_1[2] = 0.0;
  obj.cEq_2[2] = 0.0;
  obj.hasLB[2] = false;
  obj.hasUB[2] = false;
  gradf[2] = 100.0;
  computeForwardDifferences(&obj, fval, gradf, JacCeqTrans);
  funcCount = obj.numEvals + 1;
  b_gamma = 0.01;
  for (i = 0; i < 3; i++) {
    augJacobian[6 * i] = JacCeqTrans[i];
    augJacobian[6 * i + 1] = JacCeqTrans[i + 3];
    augJacobian[6 * i + 2] = JacCeqTrans[i + 6];
    aIdx = 6 * (i + 1);
    augJacobian[aIdx - 3] = 0.0;
    augJacobian[aIdx - 2] = 0.0;
    augJacobian[aIdx - 1] = 0.0;
    augJacobian[(i + 6 * i) + 3] = 0.1;
  }
  for (i = 0; i < 3; i++) {
    aIdx = i * 6;
    bIdx = i * 3;
    JacCeqTrans[bIdx] = augJacobian[aIdx];
    JacCeqTrans[bIdx + 1] = augJacobian[aIdx + 1];
    JacCeqTrans[bIdx + 2] = augJacobian[aIdx + 2];
    gradf[i] = 0.0;
  }
  for (i = 0; i <= 6; i += 3) {
    c = 0.0;
    bIdx = i + 3;
    for (aIdx = i + 1; aIdx <= bIdx; aIdx++) {
      c += JacCeqTrans[aIdx - 1] * fval[(aIdx - i) - 1];
    }
    aIdx = div_nde_s32_floor(i, 3);
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
      for (bIdx = 0; bIdx < 3; bIdx++) {
        augJacobian[6 * bIdx] = JacCeqTrans[bIdx];
        augJacobian[6 * bIdx + 1] = JacCeqTrans[bIdx + 3];
        augJacobian[6 * bIdx + 2] = JacCeqTrans[bIdx + 6];
        fval[bIdx] = fNew[bIdx];
      }
      for (i = 0; i < 3; i++) {
        aIdx = i * 6;
        bIdx = i * 3;
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
      for (i = 0; i < 3; i++) {
        aIdx = i * 3;
        bIdx = i * 6;
        augJacobian[bIdx] = JacCeqTrans[aIdx];
        augJacobian[bIdx + 1] = JacCeqTrans[aIdx + 1];
        augJacobian[bIdx + 2] = JacCeqTrans[aIdx + 2];
      }
      guard1 = true;
    }
    if (guard1) {
      c = sqrt(b_gamma);
      for (i = 0; i < 3; i++) {
        aIdx = 6 * (i + 1);
        augJacobian[aIdx - 3] = 0.0;
        augJacobian[aIdx - 2] = 0.0;
        augJacobian[aIdx - 1] = 0.0;
        augJacobian[(i + 6 * i) + 3] = c;
        gradf[i] = 0.0;
      }
      for (i = 0; i <= 6; i += 3) {
        c = 0.0;
        bIdx = i + 3;
        for (aIdx = i + 1; aIdx <= bIdx; aIdx++) {
          c += JacCeqTrans[aIdx - 1] * fval[(aIdx - i) - 1];
        }
        aIdx = div_nde_s32_floor(i, 3);
        gradf[aIdx] += c;
      }
      aIdx = b_checkStoppingCriteria(gradf, absx, funDiff, x, dx, funcCount,
                                     stepSuccessful, &iter);
      if (aIdx != -5) {
        exitg1 = true;
      }
    }
  }
}

/*
 * Arguments    : double x[3]
 * Return Type  : void
 */
void fsolve(double x[3])
{
  emxArray_char_T *in;
  struct_T FiniteDifferences;
  struct_T obj;
  double augJacobian[18];
  double JacCeqTrans[9];
  double rhs[6];
  double dx[3];
  double fval[3];
  double gradf[3];
  double absx;
  double b_gamma;
  double c;
  double funDiff;
  double resnorm;
  double resnormNew;
  int aIdx;
  int bIdx;
  int funcCount;
  int i;
  int iter;
  signed char fileid;
  char *in_data;
  boolean_T exitg1;
  boolean_T stepSuccessful;
  emxInit_char_T(&in);
  funDiff = rtInf;
  iter = 0;
  dx[0] = rtInf;
  x[0] = -100.0;
  dx[1] = rtInf;
  x[1] = 0.0;
  dx[2] = rtInf;
  x[2] = 0.0;
  /*  x = x(1) */
  /*  y = x(2) */
  /*  t = x(3) */
  fileid = cfopen("mic_1.dat");
  fgetl(fileid, in);
  in_data = in->data;
  c = 0.0;
  bIdx = in->size[1];
  for (i = 0; i < bIdx; i++) {
    c += ((double)(unsigned char)in_data[i] - 48.0) *
         rt_powd_snf(10.0, (in->size[1] - i) - 1);
  }
  cfclose(fileid);
  fileid = cfopen("mic_2.dat");
  fgetl(fileid, in);
  in_data = in->data;
  resnormNew = 0.0;
  bIdx = in->size[1];
  for (i = 0; i < bIdx; i++) {
    resnormNew += ((double)(unsigned char)in_data[i] - 48.0) *
                  rt_powd_snf(10.0, (in->size[1] - i) - 1);
  }
  cfclose(fileid);
  fileid = cfopen("mic_3.dat");
  fgetl(fileid, in);
  in_data = in->data;
  absx = 0.0;
  bIdx = in->size[1];
  for (i = 0; i < bIdx; i++) {
    absx += ((double)(unsigned char)in_data[i] - 48.0) *
            rt_powd_snf(10.0, (in->size[1] - i) - 1);
  }
  emxFree_char_T(&in);
  cfclose(fileid);
  c = 330.0 * (c * 1.0E-6);
  gradf[0] = 10000.0625 - c * c;
  c = 330.0 * (resnormNew * 1.0E-6);
  gradf[1] = 10000.0 - c * c;
  c = 330.0 * (absx * 1.0E-6);
  gradf[2] = 10050.0625 - c * c;
  resnorm = 0.0;
  for (i = 0; i < 3; i++) {
    c = gradf[i];
    fval[i] = c;
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
  gradf[0] = -100.0;
  obj.cEq_1[1] = 0.0;
  obj.cEq_2[1] = 0.0;
  obj.hasLB[1] = false;
  obj.hasUB[1] = false;
  gradf[1] = 0.0;
  obj.cEq_1[2] = 0.0;
  obj.cEq_2[2] = 0.0;
  obj.hasLB[2] = false;
  obj.hasUB[2] = false;
  gradf[2] = 0.0;
  computeForwardDifferences(&obj, fval, gradf, JacCeqTrans);
  funcCount = obj.numEvals + 1;
  b_gamma = 0.01;
  for (i = 0; i < 3; i++) {
    augJacobian[6 * i] = JacCeqTrans[i];
    augJacobian[6 * i + 1] = JacCeqTrans[i + 3];
    augJacobian[6 * i + 2] = JacCeqTrans[i + 6];
    aIdx = 6 * (i + 1);
    augJacobian[aIdx - 3] = 0.0;
    augJacobian[aIdx - 2] = 0.0;
    augJacobian[aIdx - 1] = 0.0;
    augJacobian[(i + 6 * i) + 3] = 0.1;
  }
  for (i = 0; i < 3; i++) {
    aIdx = i * 6;
    bIdx = i * 3;
    JacCeqTrans[bIdx] = augJacobian[aIdx];
    JacCeqTrans[bIdx + 1] = augJacobian[aIdx + 1];
    JacCeqTrans[bIdx + 2] = augJacobian[aIdx + 2];
    gradf[i] = 0.0;
  }
  for (i = 0; i <= 6; i += 3) {
    c = 0.0;
    bIdx = i + 3;
    for (aIdx = i + 1; aIdx <= bIdx; aIdx++) {
      c += JacCeqTrans[aIdx - 1] * fval[(aIdx - i) - 1];
    }
    aIdx = div_nde_s32_floor(i, 3);
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
      for (bIdx = 0; bIdx < 3; bIdx++) {
        augJacobian[6 * bIdx] = JacCeqTrans[bIdx];
        augJacobian[6 * bIdx + 1] = JacCeqTrans[bIdx + 3];
        augJacobian[6 * bIdx + 2] = JacCeqTrans[bIdx + 6];
        fval[bIdx] = fNew[bIdx];
      }
      for (i = 0; i < 3; i++) {
        aIdx = i * 6;
        bIdx = i * 3;
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
      for (i = 0; i < 3; i++) {
        aIdx = i * 3;
        bIdx = i * 6;
        augJacobian[bIdx] = JacCeqTrans[aIdx];
        augJacobian[bIdx + 1] = JacCeqTrans[aIdx + 1];
        augJacobian[bIdx + 2] = JacCeqTrans[aIdx + 2];
      }
      guard1 = true;
    }
    if (guard1) {
      c = sqrt(b_gamma);
      for (i = 0; i < 3; i++) {
        aIdx = 6 * (i + 1);
        augJacobian[aIdx - 3] = 0.0;
        augJacobian[aIdx - 2] = 0.0;
        augJacobian[aIdx - 1] = 0.0;
        augJacobian[(i + 6 * i) + 3] = c;
        gradf[i] = 0.0;
      }
      for (i = 0; i <= 6; i += 3) {
        c = 0.0;
        bIdx = i + 3;
        for (aIdx = i + 1; aIdx <= bIdx; aIdx++) {
          c += JacCeqTrans[aIdx - 1] * fval[(aIdx - i) - 1];
        }
        aIdx = div_nde_s32_floor(i, 3);
        gradf[aIdx] += c;
      }
      aIdx = b_checkStoppingCriteria(gradf, absx, funDiff, x, dx, funcCount,
                                     stepSuccessful, &iter);
      if (aIdx != -5) {
        exitg1 = true;
      }
    }
  }
}

/*
 * File trailer for fsolve.c
 *
 * [EOF]
 */
