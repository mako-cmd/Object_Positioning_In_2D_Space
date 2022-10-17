/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: computeForwardDifferences.h
 *
 * MATLAB Coder version            : 5.4
 * C/C++ source code generated on  : 14-Oct-2022 23:07:56
 */

#ifndef COMPUTEFORWARDDIFFERENCES_H
#define COMPUTEFORWARDDIFFERENCES_H

/* Include Files */
#include "rtwtypes.h"
#include "test_internal_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
boolean_T computeForwardDifferences(struct_T *obj, const double cEqCurrent[3],
                                    double xk[3], double JacCeqTrans[9]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for computeForwardDifferences.h
 *
 * [EOF]
 */
