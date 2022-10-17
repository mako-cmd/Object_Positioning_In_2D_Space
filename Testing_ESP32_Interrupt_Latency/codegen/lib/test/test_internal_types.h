/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: test_internal_types.h
 *
 * MATLAB Coder version            : 5.4
 * C/C++ source code generated on  : 14-Oct-2022 23:07:56
 */

#ifndef TEST_INTERNAL_TYPES_H
#define TEST_INTERNAL_TYPES_H

/* Include Files */
#include "rtwtypes.h"
#include "test_types.h"

/* Type Definitions */
#ifndef typedef_struct_T
#define typedef_struct_T
typedef struct {
  double f_1;
  double cEq_1[3];
  double f_2;
  double cEq_2[3];
  int nVar;
  int mIneq;
  int mEq;
  int numEvals;
  boolean_T SpecifyObjectiveGradient;
  boolean_T SpecifyConstraintGradient;
  boolean_T isEmptyNonlcon;
  boolean_T hasLB[3];
  boolean_T hasUB[3];
  boolean_T hasBounds;
  int FiniteDifferenceType;
} struct_T;
#endif /* typedef_struct_T */

#endif
/*
 * File trailer for test_internal_types.h
 *
 * [EOF]
 */
