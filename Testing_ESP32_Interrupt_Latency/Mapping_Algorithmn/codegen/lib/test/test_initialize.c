/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: test_initialize.c
 *
 * MATLAB Coder version            : 5.4
 * C/C++ source code generated on  : 14-Oct-2022 16:21:02
 */

/* Include Files */
#include "test_initialize.h"
#include "fileManager.h"
#include "rt_nonfinite.h"
#include "test_data.h"

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void test_initialize(void)
{
  filedata_init();
  isInitialized_test = true;
}

/*
 * File trailer for test_initialize.c
 *
 * [EOF]
 */
