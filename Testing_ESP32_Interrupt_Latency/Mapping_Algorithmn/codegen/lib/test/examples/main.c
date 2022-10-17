/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: main.c
 *
 * MATLAB Coder version            : 5.4
 * C/C++ source code generated on  : 14-Oct-2022 16:21:02
 */
/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

/* Include Files */
#include "main.h"
#include "rt_nonfinite.h"
#include "test.h"
#include "test.c"
#include "test_terminate.h"
#include "test_terminate.c"
#include "test_rtwutil.c"
#include "xnrm2.c"
#include "xzlarf.c"
#include "xzlarfg.c"
#include "test_data.c"
#include "fgetl.c"
#include "filemanager.c"
#include "rt_nonfinite.c"
#include "test_emxutil.c"
#include "checkStoppingCriteria.c"
#include "computeForwardDifferences.c"
#include "linearLeastSquares.c"
#include "sys_x.c"
#include "test_initialize.c"
#include <math.h>

double * output;

/* Function Declarations */
static void main_test(void);

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_test(void)
{
  double x[3];
  /* Call the entry-point 'test'. */
  output = test(x);
}

/*
 * Arguments    : int argc
 *                char **argv
 * Return Type  : int
 */
int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  /* The initialize function is being called automatically from your entry-point
   * function. So, a call to initialize is not included here. */
  /* Invoke the entry-point functions.
You can call entry-point functions multiple times. */
  main_test();
  /* Terminate the application.
You do not need to do this more than one time. */
  double X = output[0];
  double Y = output[1];
  double t = output[2];

  test_terminate();
  
  printf("\nX: %lf",X);
  printf("\nY: %lf",Y);
  printf("\nt: %lf",t);
  
  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
