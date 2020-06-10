/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ert_main.c
 *
 * Code generated for Simulink model 'brdemo_autotrans'.
 *
 * Model version                  : 1.277
 * Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
 * C/C++ source code generated on : Mon Mar  2 20:20:41 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>              /* This ert_main.c example uses printf/fflush */
#include "brdemo_autotrans.h"          /* Model's header file */
#include "rtwtypes.h"

double arr[2];
double rb;
int outputrb;
char output[10000];

/*
 * Associating rt_OneStep with a real-time clock or interrupt service routine
 * is what makes the generated code "real-time".  The function rt_OneStep is
 * always associated with the base rate of the model.  Subrates are managed
 * by the base rate from inside the generated code.  Enabling/disabling
 * interrupts and floating point context switches are target specific.  This
 * example code indicates where these should take place relative to executing
 * the generated code step function.  Overrun behavior should be tailored to
 * your application needs.  This example simply sets an error status in the
 * real-time model and returns from rt_OneStep.
 */
void rt_OneStep(void);
void rt_OneStep(void)
{
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(brdemo_autotrans_M, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */

  /* Step the model for base rate */
  brdemo_autotrans_step();

  /* Get model outputs here */

  /* Indicate task complete */
  OverrunFlag = false;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

/*
 * The example "main" function illustrates what is required by your
 * application code to initialize, execute, and terminate the generated code.
 * Attaching rt_OneStep to a real-time clock is target specific.  This example
 * illustrates how you do this relative to initializing the model.
 */
int_T main(int_T argc, const char *argv[])
{
  /* Unused arguments */
  //(void)(argc);
  //(void)(argv);

  outputrb=atoi(argv[1]);      
  int nIters=atoi(argv[2]);
  /* Initialize model */
  brdemo_autotrans_initialize();
  rb=10000; 

  /* Simulating the model step behavior (in non real-time) to
   *  simulate model behavior at stop time.
   */
  for(int i=3;i<argc;i+=2){
      arr[0]=atof(argv[i]);
      arr[1]=atof(argv[i+1]);
      memset(output,0,10000*sizeof(char));
      for(int j=0;j<=nIters;j++)
          rt_OneStep();
  }
  if(outputrb)
      printf("%lf",rb);
  else
      printf("%s",output);
  //while ((rtmGetErrorStatus(brdemo_autotrans_M) == (NULL)) &&
  //       !rtmGetStopRequested(brdemo_autotrans_M)) {
  //  rt_OneStep();
  //}

  /* Disable rt_OneStep() here */

  /* Terminate model */
  brdemo_autotrans_terminate();
  //printf(" %lf %lf\n",arr[0],arr[1]);
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
