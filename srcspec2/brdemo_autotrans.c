/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: brdemo_autotrans.c
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

#include "brdemo_autotrans.h"
#include "brdemo_autotrans_private.h"
#include <stdio.h>
#include <string.h>

/* Named constants for Chart: '<Root>/ShiftLogic' */
#define brdemo_autotran_IN_downshifting ((uint8_T)1U)
#define brdemo_autotran_IN_steady_state ((uint8_T)2U)
#define brdemo_autotrans_CALL_EVENT    (-1)
#define brdemo_autotrans_IN_first      ((uint8_T)1U)
#define brdemo_autotrans_IN_fourth     ((uint8_T)2U)
#define brdemo_autotrans_IN_second     ((uint8_T)3U)
#define brdemo_autotrans_IN_third      ((uint8_T)4U)
#define brdemo_autotrans_IN_upshifting ((uint8_T)3U)
#define brdemo_autotrans_event_DOWN    (0)
#define brdemo_autotrans_event_UP      (1)

/* Block signals (default storage) */
B_brdemo_autotrans_T brdemo_autotrans_B;

/* Continuous states */
X_brdemo_autotrans_T brdemo_autotrans_X;

/* Block states (default storage) */
DW_brdemo_autotrans_T brdemo_autotrans_DW;

/* External inputs (root inport signals with default storage) */
ExtU_brdemo_autotrans_T brdemo_autotrans_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_brdemo_autotrans_T brdemo_autotrans_Y;

/* Real-time model */
RT_MODEL_brdemo_autotrans_T brdemo_autotrans_M_;
RT_MODEL_brdemo_autotrans_T *const brdemo_autotrans_M = &brdemo_autotrans_M_;

/* Forward declaration for local functions */
static void brdemo_autotrans_gear_state(const int32_T *sfEvent);
static void rate_scheduler(void);

/*
 *   This function updates active task flag for each subrate.
 * The function is called at model base rate, hence the
 * generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (brdemo_autotrans_M->Timing.TaskCounters.TID[2])++;
  if ((brdemo_autotrans_M->Timing.TaskCounters.TID[2]) > 3) {/* Sample time: [0.04s, 0.0s] */
    brdemo_autotrans_M->Timing.TaskCounters.TID[2] = 0;
  }
}

/*
 * This function updates continuous states using the ODE5 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE5_A[6] = {
    1.0/5.0, 3.0/10.0, 4.0/5.0, 8.0/9.0, 1.0, 1.0
  };

  static const real_T rt_ODE5_B[6][6] = {
    { 1.0/5.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

    { 3.0/40.0, 9.0/40.0, 0.0, 0.0, 0.0, 0.0 },

    { 44.0/45.0, -56.0/15.0, 32.0/9.0, 0.0, 0.0, 0.0 },

    { 19372.0/6561.0, -25360.0/2187.0, 64448.0/6561.0, -212.0/729.0, 0.0, 0.0 },

    { 9017.0/3168.0, -355.0/33.0, 46732.0/5247.0, 49.0/176.0, -5103.0/18656.0,
      0.0 },

    { 35.0/384.0, 0.0, 500.0/1113.0, 125.0/192.0, -2187.0/6784.0, 11.0/84.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE5_IntgData *id = (ODE5_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T *f3 = id->f[3];
  real_T *f4 = id->f[4];
  real_T *f5 = id->f[5];
  real_T hB[6];
  int_T i;
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  brdemo_autotrans_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE5_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[0]);
  rtsiSetdX(si, f1);
  brdemo_autotrans_step();
  brdemo_autotrans_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE5_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[1]);
  rtsiSetdX(si, f2);
  brdemo_autotrans_step();
  brdemo_autotrans_derivatives();

  /* f(:,4) = feval(odefile, t + hA(3), y + f*hB(:,3), args(:)(*)); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE5_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[2]);
  rtsiSetdX(si, f3);
  brdemo_autotrans_step();
  brdemo_autotrans_derivatives();

  /* f(:,5) = feval(odefile, t + hA(4), y + f*hB(:,4), args(:)(*)); */
  for (i = 0; i <= 3; i++) {
    hB[i] = h * rt_ODE5_B[3][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2] +
                   f3[i]*hB[3]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[3]);
  rtsiSetdX(si, f4);
  brdemo_autotrans_step();
  brdemo_autotrans_derivatives();

  /* f(:,6) = feval(odefile, t + hA(5), y + f*hB(:,5), args(:)(*)); */
  for (i = 0; i <= 4; i++) {
    hB[i] = h * rt_ODE5_B[4][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2] +
                   f3[i]*hB[3] + f4[i]*hB[4]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f5);
  brdemo_autotrans_step();
  brdemo_autotrans_derivatives();

  /* tnew = t + hA(6);
     ynew = y + f*hB(:,6); */
  for (i = 0; i <= 5; i++) {
    hB[i] = h * rt_ODE5_B[5][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2] +
                   f3[i]*hB[3] + f4[i]*hB[4] + f5[i]*hB[5]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Function for Chart: '<Root>/ShiftLogic' */
static void brdemo_autotrans_gear_state(const int32_T *sfEvent)
{
  switch (brdemo_autotrans_DW.is_gear_state) {
   case brdemo_autotrans_IN_first:
   strcat(output,"A");
    brdemo_autotrans_B.gear = 1.0;
    if (*sfEvent == brdemo_autotrans_event_UP) {
        strcat(output,"B");
      brdemo_autotrans_DW.is_gear_state = brdemo_autotrans_IN_second;
      brdemo_autotrans_B.gear = 2.0;
    }
    break;

   case brdemo_autotrans_IN_fourth:
   strcat(output,"C");
    brdemo_autotrans_B.gear = 4.0;
    if (*sfEvent == brdemo_autotrans_event_DOWN) {
        strcat(output,"D");
      brdemo_autotrans_DW.is_gear_state = brdemo_autotrans_IN_third;
      brdemo_autotrans_B.gear = 3.0;
    }
    break;

   case brdemo_autotrans_IN_second:
   strcat(output,"E");
    brdemo_autotrans_B.gear = 2.0;
    switch (*sfEvent) {
     case brdemo_autotrans_event_UP:
     strcat(output,"F");
      brdemo_autotrans_DW.is_gear_state = brdemo_autotrans_IN_third;
      brdemo_autotrans_B.gear = 3.0;
      break;

     case brdemo_autotrans_event_DOWN:
     strcat(output,"G");
      brdemo_autotrans_DW.is_gear_state = brdemo_autotrans_IN_first;
      brdemo_autotrans_B.gear = 1.0;
      break;
    }
    break;

   case brdemo_autotrans_IN_third:
   strcat(output,"H");
    brdemo_autotrans_B.gear = 3.0;
    switch (*sfEvent) {
     case brdemo_autotrans_event_UP:
     strcat(output,"I");
      brdemo_autotrans_DW.is_gear_state = brdemo_autotrans_IN_fourth;
      brdemo_autotrans_B.gear = 4.0;
      break;

     case brdemo_autotrans_event_DOWN:
     strcat(output,"J");
      brdemo_autotrans_DW.is_gear_state = brdemo_autotrans_IN_second;
      brdemo_autotrans_B.gear = 2.0;
      break;
    }
    break;
  }
}

real_T rt_powd_snf(real_T u0, real_T u1)
{
    return u0 * u0;
}

/* Model step function */
void brdemo_autotrans_step(void)
{
  int32_T sfEvent;
  real_T interp_down;
  real_T interp_up;
  double currb;
  if (rtmIsMajorTimeStep(brdemo_autotrans_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&brdemo_autotrans_M->solverInfo,
                          ((brdemo_autotrans_M->Timing.clockTick0+1)*
      brdemo_autotrans_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(brdemo_autotrans_M)) {
    brdemo_autotrans_M->Timing.t[0] = rtsiGetT(&brdemo_autotrans_M->solverInfo);
  }

  /* Gain: '<S5>/mph' incorporates:
   *  Gain: '<S5>/LinearSpeed'
   *  Integrator: '<S5>/Wheel Speed'
   */
  brdemo_autotrans_B.VehicleSpeed = 6.2831853071795862 *
    brdemo_autotrans_X.WheelSpeed_CSTATE * 0.011363636363636364;

  /* Outport: '<Root>/speed' */
  brdemo_autotrans_Y.speed = brdemo_autotrans_B.VehicleSpeed;

  /* Integrator: '<S1>/Integrator' */
  /* Limited  Integrator  */
  if (brdemo_autotrans_X.Integrator_CSTATE >= 6000.0) {
      strcat(output,"K");
    brdemo_autotrans_X.Integrator_CSTATE = 6000.0;
  } else {
    if (brdemo_autotrans_X.Integrator_CSTATE <= 600.0) {
        strcat(output,"L");
      brdemo_autotrans_X.Integrator_CSTATE = 600.0;
    }
  }

  brdemo_autotrans_B.RPM = brdemo_autotrans_X.Integrator_CSTATE;

  /* End of Integrator: '<S1>/Integrator' */

  /* Outport: '<Root>/RPM' */
  brdemo_autotrans_Y.RPM = brdemo_autotrans_B.RPM;
  if (rtmIsMajorTimeStep(brdemo_autotrans_M) &&
      brdemo_autotrans_M->Timing.TaskCounters.TID[2] == 0) {
    /* Chart: '<Root>/ShiftLogic' */
    sfEvent = brdemo_autotrans_CALL_EVENT;
    if (brdemo_autotrans_DW.temporalCounter_i1 < MAX_uint32_T) {
      brdemo_autotrans_DW.temporalCounter_i1++;
    }

    if (brdemo_autotrans_DW.is_active_c1_brdemo_autotrans == 0U) {
        strcat(output,"M");
      brdemo_autotrans_DW.is_active_c1_brdemo_autotrans = 1U;
      brdemo_autotrans_DW.is_active_gear_state = 1U;
      brdemo_autotrans_DW.is_gear_state = brdemo_autotrans_IN_first;
      brdemo_autotrans_B.gear = 1.0;
      brdemo_autotrans_DW.is_active_selection_state = 1U;
      brdemo_autotrans_DW.is_selection_state = brdemo_autotran_IN_steady_state;
    } else {
        strcat(output,"N");
      if (brdemo_autotrans_DW.is_active_gear_state != 0U) {
          strcat(output,"O");
        brdemo_autotrans_gear_state(&sfEvent);
      }

      if (brdemo_autotrans_DW.is_active_selection_state != 0U) {
        /* Outputs for Function Call SubSystem: '<Root>/ThresholdCalculation' */
        /* Lookup2D: '<S3>/interp_down' incorporates:
         *  Inport: '<Root>/throttle'
         */
         strcat(output,"P");
        interp_down = rt_Lookup2D_Normal
          (brdemo_autotrans_ConstP.interp_down_RowIdx, 6,
           brdemo_autotrans_ConstP.pooled1, 4,
           brdemo_autotrans_ConstP.interp_down_Table,
           brdemo_autotrans_U.throttle, brdemo_autotrans_B.gear);

        /* Lookup2D: '<S3>/interp_up' incorporates:
         *  Inport: '<Root>/throttle'
         */
        interp_up = rt_Lookup2D_Normal(brdemo_autotrans_ConstP.interp_up_RowIdx,
          6, brdemo_autotrans_ConstP.pooled1, 4,
          brdemo_autotrans_ConstP.interp_up_Table, brdemo_autotrans_U.throttle,
          brdemo_autotrans_B.gear);

        /* End of Outputs for SubSystem: '<Root>/ThresholdCalculation' */
        switch (brdemo_autotrans_DW.is_selection_state) {
         case brdemo_autotran_IN_downshifting:
         strcat(output,"Q");
          if ((brdemo_autotrans_DW.temporalCounter_i1 >= (uint32_T)2.0) &&
              (brdemo_autotrans_B.VehicleSpeed <= interp_down)) {
                  strcat(output,"R");
            sfEvent = brdemo_autotrans_event_DOWN;
            if (brdemo_autotrans_DW.is_active_gear_state != 0U) {
                strcat(output,"S");
              brdemo_autotrans_gear_state(&sfEvent);
            }

            brdemo_autotrans_DW.is_selection_state =
              brdemo_autotran_IN_steady_state;
          } else {
              strcat(output,"T");
            if (brdemo_autotrans_B.VehicleSpeed > interp_down) {
                strcat(output,"U");
              brdemo_autotrans_DW.is_selection_state =
                brdemo_autotran_IN_steady_state;
            }
          }
          break;

         case brdemo_autotran_IN_steady_state:
         strcat(output,"V");
          if (brdemo_autotrans_B.VehicleSpeed > interp_up) {
              strcat(output,"W");
            brdemo_autotrans_DW.is_selection_state =
              brdemo_autotrans_IN_upshifting;
            brdemo_autotrans_DW.temporalCounter_i1 = 0U;
          } else {
              strcat(output,"X");
            if (brdemo_autotrans_B.VehicleSpeed < interp_down) {
                strcat(output,"Y");
              brdemo_autotrans_DW.is_selection_state =
                brdemo_autotran_IN_downshifting;
              brdemo_autotrans_DW.temporalCounter_i1 = 0U;
            }
          }
          break;

         case brdemo_autotrans_IN_upshifting:
         strcat(output,"Z");
          if ((brdemo_autotrans_DW.temporalCounter_i1 >= (uint32_T)2.0) &&
              (brdemo_autotrans_B.VehicleSpeed >= interp_up)) {
                  strcat(output,"0");
            sfEvent = brdemo_autotrans_event_UP;
            if (brdemo_autotrans_DW.is_active_gear_state != 0U) {
                strcat(output,"1");
              brdemo_autotrans_gear_state(&sfEvent);
            }

            brdemo_autotrans_DW.is_selection_state =
              brdemo_autotran_IN_steady_state;
          } else {
              strcat(output,"2");
            if (brdemo_autotrans_B.VehicleSpeed < interp_up) {
                strcat(output,"3");
              brdemo_autotrans_DW.is_selection_state =
                brdemo_autotran_IN_steady_state;
            }
          }
          break;
        }
      }
    }

    /* End of Chart: '<Root>/ShiftLogic' */

    /* Outport: '<Root>/gear' */
    brdemo_autotrans_Y.gear = brdemo_autotrans_B.gear;
  }

  if (rtmIsMajorTimeStep(brdemo_autotrans_M) &&
      brdemo_autotrans_M->Timing.TaskCounters.TID[1] == 0) {
  }

  if (rtmIsMajorTimeStep(brdemo_autotrans_M) &&
      brdemo_autotrans_M->Timing.TaskCounters.TID[2] == 0) {
    /* Lookup: '<S7>/Look-Up Table' */
    brdemo_autotrans_B.LookUpTable = rt_Lookup(brdemo_autotrans_ConstP.pooled1,
      4, brdemo_autotrans_B.gear, brdemo_autotrans_ConstP.LookUpTable_YData);
  }

  /* Gain: '<S5>/FinalDriveRatio2' incorporates:
   *  Integrator: '<S5>/Wheel Speed'
   */
  brdemo_autotrans_B.TransmissionRPM = 3.23 *
    brdemo_autotrans_X.WheelSpeed_CSTATE;

  /* Product: '<S6>/SpeedRatio' incorporates:
   *  Product: '<S7>/Product1'
   */
  interp_up = brdemo_autotrans_B.LookUpTable *
    brdemo_autotrans_B.TransmissionRPM / brdemo_autotrans_B.RPM;

  /* Fcn: '<S6>/Impeller' incorporates:
   *  Lookup: '<S6>/FactorK'
   *  Product: '<S6>/Quotient'
   */
  interp_down = rt_powd_snf(brdemo_autotrans_B.RPM / rt_Lookup
    (brdemo_autotrans_ConstP.pooled3, 21, interp_up,
     brdemo_autotrans_ConstP.FactorK_YData), 2.0);

  /* Gain: '<S1>/engine + impeller inertia' incorporates:
   *  Fcn: '<S6>/Impeller'
   *  Inport: '<Root>/throttle'
   *  Lookup2D: '<S1>/EngineTorque'
   *  Sum: '<S1>/Sum'
   */
  brdemo_autotrans_B.engineimpellerinertia = (rt_Lookup2D_Normal
    (brdemo_autotrans_ConstP.EngineTorque_RowIdx, 10,
     brdemo_autotrans_ConstP.EngineTorque_ColIdx, 11,
     brdemo_autotrans_ConstP.EngineTorque_Table, brdemo_autotrans_U.throttle,
     brdemo_autotrans_B.RPM) - interp_down) * 45.472138452209627;

  /* Product: '<S7>/Product' incorporates:
   *  Fcn: '<S6>/Impeller'
   *  Lookup: '<S6>/TorqueRatio'
   *  Product: '<S6>/Turbine'
   */
  brdemo_autotrans_B.OutputTorque = interp_down * rt_Lookup
    (brdemo_autotrans_ConstP.pooled3, 21, interp_up,
     brdemo_autotrans_ConstP.TorqueRatio_YData) * brdemo_autotrans_B.LookUpTable;

  /* Signum: '<S5>/Sign' */
  if (brdemo_autotrans_B.VehicleSpeed < 0.0) {
      strcat(output,"4");
    interp_down = -1.0;
  } else if (brdemo_autotrans_B.VehicleSpeed > 0.0) {
      strcat(output,"5");
    interp_down = 1.0;
  } else if (brdemo_autotrans_B.VehicleSpeed == 0.0) {
      strcat(output,"6");
    interp_down = 0.0;
  } else {
      strcat(output,"7");
    interp_down = (rtNaN);
  }

  /* End of Signum: '<S5>/Sign' */

  /* Gain: '<S5>/Vehicle Inertia' incorporates:
   *  Fcn: '<S5>/RoadLoad'
   *  Gain: '<S5>/Final Drive Ratio1'
   *  Inport: '<Root>/brake'
   *  Product: '<S5>/SignedLoad'
   *  Sum: '<S5>/Sum'
   *  Sum: '<S5>/Sum1'
   */
  brdemo_autotrans_B.VehicleInertia = (3.23 * brdemo_autotrans_B.OutputTorque -
    ((0.02 * rt_powd_snf(brdemo_autotrans_B.VehicleSpeed, 2.0) + 40.0) +
     brdemo_autotrans_U.brake) * interp_down) * 0.082684618362373577;
  if (rtmIsMajorTimeStep(brdemo_autotrans_M)) {
    rt_ertODEUpdateContinuousStates(&brdemo_autotrans_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++brdemo_autotrans_M->Timing.clockTick0;
    brdemo_autotrans_M->Timing.t[0] = rtsiGetSolverStopTime
      (&brdemo_autotrans_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.01s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.01, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      //printf("Time: %d, In: Throttle=%lf Brake=%lf, out: Speed=%lf RPM=%lf Gear=%lf\n",brdemo_autotrans_M->Timing.clockTick1,brdemo_autotrans_U.throttle,brdemo_autotrans_U.brake,brdemo_autotrans_Y.speed,brdemo_autotrans_Y.RPM,brdemo_autotrans_Y.gear);
      brdemo_autotrans_M->Timing.clockTick1++;

      brdemo_autotrans_U.throttle=arr[0];
      brdemo_autotrans_U.brake=arr[1];
      if(brdemo_autotrans_M->Timing.clockTick1<2900){
	      currb=100-brdemo_autotrans_Y.speed;
	      if(currb<rb029)
		      rb029=currb;
      }
      else{
	      currb=brdemo_autotrans_Y.speed-65;
	      if(currb<rb2930)
		      rb2930=currb;
      }
      //if(brdemo_autotrans_Y.gear==3)
      //    currb=brdemo_autotrans_Y.speed-20;
      //else
      //    currb=300;
      //if(currb<rb)
      //    rb=currb;        
    }

    rate_scheduler();
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void brdemo_autotrans_derivatives(void)
{
  boolean_T lsat;
  boolean_T usat;
  XDot_brdemo_autotrans_T *_rtXdot;
  _rtXdot = ((XDot_brdemo_autotrans_T *) brdemo_autotrans_M->derivs);

  /* Derivatives for Integrator: '<S5>/Wheel Speed' */
  _rtXdot->WheelSpeed_CSTATE = brdemo_autotrans_B.VehicleInertia;

  /* Derivatives for Integrator: '<S1>/Integrator' */
  lsat = (brdemo_autotrans_X.Integrator_CSTATE <= 600.0);
  usat = (brdemo_autotrans_X.Integrator_CSTATE >= 6000.0);
  if (((!lsat) && (!usat)) || (lsat && (brdemo_autotrans_B.engineimpellerinertia
        > 0.0)) || (usat && (brdemo_autotrans_B.engineimpellerinertia < 0.0))) {
            strcat(output,"8");
    _rtXdot->Integrator_CSTATE = brdemo_autotrans_B.engineimpellerinertia;
  } else {
    /* in saturation */
    strcat(output,"9");
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S1>/Integrator' */
}

/* Model initialize function */
void brdemo_autotrans_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&brdemo_autotrans_M->solverInfo,
                          &brdemo_autotrans_M->Timing.simTimeStep);
    rtsiSetTPtr(&brdemo_autotrans_M->solverInfo, &rtmGetTPtr(brdemo_autotrans_M));
    rtsiSetStepSizePtr(&brdemo_autotrans_M->solverInfo,
                       &brdemo_autotrans_M->Timing.stepSize0);
    rtsiSetdXPtr(&brdemo_autotrans_M->solverInfo, &brdemo_autotrans_M->derivs);
    rtsiSetContStatesPtr(&brdemo_autotrans_M->solverInfo, (real_T **)
                         &brdemo_autotrans_M->contStates);
    rtsiSetNumContStatesPtr(&brdemo_autotrans_M->solverInfo,
      &brdemo_autotrans_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&brdemo_autotrans_M->solverInfo,
      &brdemo_autotrans_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&brdemo_autotrans_M->solverInfo,
      &brdemo_autotrans_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&brdemo_autotrans_M->solverInfo,
      &brdemo_autotrans_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&brdemo_autotrans_M->solverInfo, (&rtmGetErrorStatus
      (brdemo_autotrans_M)));
    rtsiSetRTModelPtr(&brdemo_autotrans_M->solverInfo, brdemo_autotrans_M);
  }

  rtsiSetSimTimeStep(&brdemo_autotrans_M->solverInfo, MAJOR_TIME_STEP);
  brdemo_autotrans_M->intgData.y = brdemo_autotrans_M->odeY;
  brdemo_autotrans_M->intgData.f[0] = brdemo_autotrans_M->odeF[0];
  brdemo_autotrans_M->intgData.f[1] = brdemo_autotrans_M->odeF[1];
  brdemo_autotrans_M->intgData.f[2] = brdemo_autotrans_M->odeF[2];
  brdemo_autotrans_M->intgData.f[3] = brdemo_autotrans_M->odeF[3];
  brdemo_autotrans_M->intgData.f[4] = brdemo_autotrans_M->odeF[4];
  brdemo_autotrans_M->intgData.f[5] = brdemo_autotrans_M->odeF[5];
  brdemo_autotrans_M->contStates = ((X_brdemo_autotrans_T *) &brdemo_autotrans_X);
  rtsiSetSolverData(&brdemo_autotrans_M->solverInfo, (void *)
                    &brdemo_autotrans_M->intgData);
  rtsiSetSolverName(&brdemo_autotrans_M->solverInfo,"ode5");
  rtmSetTPtr(brdemo_autotrans_M, &brdemo_autotrans_M->Timing.tArray[0]);
  brdemo_autotrans_M->Timing.stepSize0 = 0.01;

  /* InitializeConditions for Integrator: '<S5>/Wheel Speed' */
  brdemo_autotrans_X.WheelSpeed_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S1>/Integrator' */
  brdemo_autotrans_X.Integrator_CSTATE = 1000.0;
}

/* Model terminate function */
void brdemo_autotrans_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
