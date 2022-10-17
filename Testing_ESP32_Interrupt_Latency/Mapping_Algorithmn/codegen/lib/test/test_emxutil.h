/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: test_emxutil.h
 *
 * MATLAB Coder version            : 5.4
 * C/C++ source code generated on  : 14-Oct-2022 16:21:02
 */

#ifndef TEST_EMXUTIL_H
#define TEST_EMXUTIL_H

/* Include Files */
#include "rtwtypes.h"
#include "test_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void emxEnsureCapacity_char_T(emxArray_char_T *emxArray, int oldNumel);

extern void emxFree_char_T(emxArray_char_T **pEmxArray);

extern void emxInit_char_T(emxArray_char_T **pEmxArray);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for test_emxutil.h
 *
 * [EOF]
 */
