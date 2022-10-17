/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: checkStoppingCriteria.h
 *
 * MATLAB Coder version            : 5.4
 * C/C++ source code generated on  : 14-Oct-2022 23:07:56
 */

#ifndef CHECKSTOPPINGCRITERIA_H
#define CHECKSTOPPINGCRITERIA_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
int b_checkStoppingCriteria(const double gradf[3], double relFactor,
                            double funDiff, const double x[3],
                            const double dx[3], int funcCount,
                            boolean_T stepSuccessful, int *iter);

int checkStoppingCriteria(const double gradf[3], double relFactor,
                          int funcCount);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for checkStoppingCriteria.h
 *
 * [EOF]
 */
