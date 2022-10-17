#include "main.h"
#include "rt_nonfinite.h"
#include "test.h"
#include "test.c"
#include "test_terminate.h"
#include "xnrm2.c"
#include "xzlarf.c"
#include "xzlarfg.c"
#include "test_terminate.c"

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
  double x_data[3];
  int x_size[2];
  /* Call the entry-point 'test'. */
  output = test(x_data, x_size);
}
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  main_test();
  /* Terminate the application.
  You do not need to do this more than one time. */
  double x = output[0];
  double y = output[1];
  double t = output[2];
  test_terminate();
  return 0;
}
