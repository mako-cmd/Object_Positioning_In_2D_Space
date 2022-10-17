/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: sys_x.c
 *
 * MATLAB Coder version            : 5.4
 * C/C++ source code generated on  : 14-Oct-2022 23:07:56
 */

/* Include Files */
#include "sys_x.h"
#include "fgetl.h"
#include "fileManager.h"
#include "rt_nonfinite.h"
#include "test_emxutil.h"
#include "test_rtwutil.h"
#include "test_types.h"

/* Function Definitions */
/*
 * x = x(1)
 *  y = x(2)
 *  t = x(3)
 *
 * Arguments    : const double x[3]
 *                double F[3]
 * Return Type  : void
 */
void sys_x(const double x[3], double F[3])
{
  emxArray_char_T *in;
  double b_out;
  double c_out;
  double out;
  int b_i;
  int i;
  signed char fileid;
  char *in_data;
  emxInit_char_T(&in);
  fileid = cfopen("mic_1.dat");
  fgetl(fileid, in);
  in_data = in->data;
  out = 0.0;
  i = in->size[1];
  for (b_i = 0; b_i < i; b_i++) {
    out += ((double)(unsigned char)in_data[b_i] - 48.0) *
           rt_powd_snf(10.0, (in->size[1] - b_i) - 1);
  }
  cfclose(fileid);
  fileid = cfopen("mic_2.dat");
  fgetl(fileid, in);
  in_data = in->data;
  b_out = 0.0;
  i = in->size[1];
  for (b_i = 0; b_i < i; b_i++) {
    b_out += ((double)(unsigned char)in_data[b_i] - 48.0) *
             rt_powd_snf(10.0, (in->size[1] - b_i) - 1);
  }
  cfclose(fileid);
  fileid = cfopen("mic_3.dat");
  fgetl(fileid, in);
  in_data = in->data;
  c_out = 0.0;
  i = in->size[1];
  for (b_i = 0; b_i < i; b_i++) {
    c_out += ((double)(unsigned char)in_data[b_i] - 48.0) *
             rt_powd_snf(10.0, (in->size[1] - b_i) - 1);
  }
  double F_tmp;
  double a;
  emxFree_char_T(&in);
  cfclose(fileid);
  a = 330.0 * (out * 1.0E-6 + x[2]);
  F_tmp = x[0] * x[0];
  F[0] = (F_tmp + (x[1] + 0.25) * (x[1] + 0.25)) - a * a;
  a = 330.0 * (b_out * 1.0E-6 + x[2]);
  out = x[1] * x[1];
  F[1] = (F_tmp + out) - a * a;
  a = 330.0 * (c_out * 1.0E-6 + x[2]);
  F[2] = ((x[0] - 0.25) * (x[0] - 0.25) + out) - a * a;
}

/*
 * File trailer for sys_x.c
 *
 * [EOF]
 */
