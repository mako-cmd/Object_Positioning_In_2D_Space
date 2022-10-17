/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: fileManager.h
 *
 * MATLAB Coder version            : 5.4
 * C/C++ source code generated on  : 14-Oct-2022 16:21:02
 */

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
int cfclose(double fid);

signed char cfopen(const char *cfilename);

FILE *fileManager(double varargin_1);

void filedata_init(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for fileManager.h
 *
 * [EOF]
 */
