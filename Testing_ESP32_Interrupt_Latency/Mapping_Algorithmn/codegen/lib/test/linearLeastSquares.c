/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: linearLeastSquares.c
 *
 * MATLAB Coder version            : 5.4
 * C/C++ source code generated on  : 14-Oct-2022 16:21:02
 */

/* Include Files */
#include "linearLeastSquares.h"
#include "rt_nonfinite.h"
#include "xnrm2.h"
#include "xzlarf.h"
#include "xzlarfg.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : double lhs[18]
 *                double rhs[6]
 *                double dx[3]
 * Return Type  : void
 */
void linearLeastSquares(double lhs[18], double rhs[6], double dx[3])
{
  double jpvt[3];
  double work[3];
  double temp;
  int b_i;
  int i;
  int ii;
  int ix;
  int iy;
  int j;
  int k;
  int nfxd;
  int temp_tmp;
  jpvt[0] = 0.0;
  jpvt[1] = 0.0;
  jpvt[2] = 0.0;
  nfxd = -1;
  for (j = 0; j < 3; j++) {
    if (jpvt[j] != 0.0) {
      nfxd++;
      if (j + 1 != nfxd + 1) {
        ix = j * 6;
        iy = nfxd * 6;
        for (k = 0; k < 6; k++) {
          temp_tmp = ix + k;
          temp = lhs[temp_tmp];
          b_i = iy + k;
          lhs[temp_tmp] = lhs[b_i];
          lhs[b_i] = temp;
        }
        jpvt[j] = jpvt[nfxd];
        jpvt[nfxd] = (double)j + 1.0;
      } else {
        jpvt[j] = (double)j + 1.0;
      }
    } else {
      jpvt[j] = (double)j + 1.0;
    }
    dx[j] = 0.0;
    work[j] = 0.0;
  }
  for (i = 0; i <= nfxd; i++) {
    ii = i * 6 + i;
    temp = lhs[ii];
    dx[i] = xzlarfg(6 - i, &temp, lhs, ii + 2);
    lhs[ii] = temp;
    if (i + 1 < 3) {
      temp = lhs[ii];
      lhs[ii] = 1.0;
      xzlarf(6 - i, 2 - i, ii + 1, dx[i], lhs, ii + 7, work);
      lhs[ii] = temp;
    }
  }
  if (nfxd + 1 < 3) {
    double vn1[3];
    double vn2[3];
    work[0] = 0.0;
    vn1[0] = 0.0;
    vn2[0] = 0.0;
    work[1] = 0.0;
    vn1[1] = 0.0;
    vn2[1] = 0.0;
    work[2] = 0.0;
    vn1[2] = 0.0;
    vn2[2] = 0.0;
    b_i = nfxd + 2;
    for (j = b_i; j < 4; j++) {
      temp = xnrm2(5 - nfxd, lhs, (nfxd + (j - 1) * 6) + 2);
      vn1[j - 1] = temp;
      vn2[j - 1] = temp;
    }
    for (i = b_i; i < 4; i++) {
      double s;
      int ip1;
      ip1 = i + 1;
      j = (i - 1) * 6;
      ii = (j + i) - 1;
      iy = 4 - i;
      nfxd = -1;
      if (4 - i > 1) {
        temp = fabs(vn1[i - 1]);
        for (k = 2; k <= iy; k++) {
          s = fabs(vn1[(i + k) - 2]);
          if (s > temp) {
            nfxd = k - 2;
            temp = s;
          }
        }
      }
      iy = i + nfxd;
      if (iy + 1 != i) {
        ix = iy * 6;
        for (k = 0; k < 6; k++) {
          temp_tmp = ix + k;
          temp = lhs[temp_tmp];
          nfxd = j + k;
          lhs[temp_tmp] = lhs[nfxd];
          lhs[nfxd] = temp;
        }
        temp = jpvt[iy];
        jpvt[iy] = jpvt[i - 1];
        jpvt[i - 1] = temp;
        vn1[iy] = vn1[i - 1];
        vn2[iy] = vn2[i - 1];
      }
      temp = lhs[ii];
      dx[i - 1] = xzlarfg(7 - i, &temp, lhs, ii + 2);
      lhs[ii] = temp;
      if (i < 3) {
        temp = lhs[ii];
        lhs[ii] = 1.0;
        xzlarf(7 - i, 3 - i, ii + 1, dx[i - 1], lhs, ii + 7, work);
        lhs[ii] = temp;
      }
      for (j = ip1; j < 4; j++) {
        iy = i + (j - 1) * 6;
        temp = vn1[j - 1];
        if (temp != 0.0) {
          double temp2;
          s = fabs(lhs[iy - 1]) / temp;
          s = 1.0 - s * s;
          if (s < 0.0) {
            s = 0.0;
          }
          temp2 = temp / vn2[j - 1];
          temp2 = s * (temp2 * temp2);
          if (temp2 <= 1.4901161193847656E-8) {
            temp = xnrm2(6 - i, lhs, iy + 1);
            vn1[j - 1] = temp;
            vn2[j - 1] = temp;
          } else {
            vn1[j - 1] = temp * sqrt(s);
          }
        }
      }
    }
  }
  for (j = 0; j < 3; j++) {
    if (dx[j] != 0.0) {
      temp = rhs[j];
      b_i = j + 2;
      for (i = b_i; i < 7; i++) {
        temp += lhs[(i + 6 * j) - 1] * rhs[i - 1];
      }
      temp *= dx[j];
      if (temp != 0.0) {
        rhs[j] -= temp;
        for (i = b_i; i < 7; i++) {
          rhs[i - 1] -= lhs[(i + 6 * j) - 1] * temp;
        }
      }
    }
  }
  dx[0] = rhs[0];
  dx[1] = rhs[1];
  dx[2] = rhs[2];
  for (j = 2; j >= 0; j--) {
    iy = j + j * 6;
    dx[j] /= lhs[iy];
    for (i = 0; i < j; i++) {
      ix = (j - i) - 1;
      dx[ix] -= dx[j] * lhs[(iy - i) - 1];
    }
  }
  work[1] = dx[1];
  work[2] = dx[2];
  dx[(int)jpvt[0] - 1] = dx[0];
  dx[(int)jpvt[1] - 1] = work[1];
  dx[(int)jpvt[2] - 1] = work[2];
}

/*
 * File trailer for linearLeastSquares.c
 *
 * [EOF]
 */
