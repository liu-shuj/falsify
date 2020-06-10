/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: brdemo_autotrans.h
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

#ifndef RTW_HEADER_brdemo_autotrans_h_
#define RTW_HEADER_brdemo_autotrans_h_
#include <math.h>
#include <string.h>
#ifndef brdemo_autotrans_COMMON_INCLUDES_
# define brdemo_autotrans_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* brdemo_autotrans_COMMON_INCLUDES_ */

#include "brdemo_autotrans_types.h"
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include "rt_look.h"
#include "rt_look1d.h"
#include "rt_look2d_normal.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T VehicleSpeed;                 /* '<S5>/mph' */
  real_T RPM;                          /* '<S1>/Integrator' */
  real_T LookUpTable;                  /* '<S7>/Look-Up Table' */
  real_T TransmissionRPM;              /* '<S5>/FinalDriveRatio2' */
  real_T engineimpellerinertia;        /* '<S1>/engine + impeller inertia' */
  real_T OutputTorque;                 /* '<S7>/Product' */
  real_T VehicleInertia;               /* '<S5>/Vehicle Inertia' */
  real_T gear;                         /* '<Root>/ShiftLogic' */
} B_brdemo_autotrans_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  struct {
    void *LoggedData[3];
  } Scope_PWORK;                       /* '<Root>/Scope' */

  struct {
    void *LoggedData[2];
  } Scope2_PWORK;                      /* '<Root>/Scope2' */

  uint32_T temporalCounter_i1;         /* '<Root>/ShiftLogic' */
  uint8_T is_active_c1_brdemo_autotrans;/* '<Root>/ShiftLogic' */
  uint8_T is_gear_state;               /* '<Root>/ShiftLogic' */
  uint8_T is_active_gear_state;        /* '<Root>/ShiftLogic' */
  uint8_T is_selection_state;          /* '<Root>/ShiftLogic' */
  uint8_T is_active_selection_state;   /* '<Root>/ShiftLogic' */
} DW_brdemo_autotrans_T;

/* Continuous states (default storage) */
typedef struct {
  real_T WheelSpeed_CSTATE;            /* '<S5>/Wheel Speed' */
  real_T Integrator_CSTATE;            /* '<S1>/Integrator' */
} X_brdemo_autotrans_T;

/* State derivatives (default storage) */
typedef struct {
  real_T WheelSpeed_CSTATE;            /* '<S5>/Wheel Speed' */
  real_T Integrator_CSTATE;            /* '<S1>/Integrator' */
} XDot_brdemo_autotrans_T;

/* State disabled  */
typedef struct {
  boolean_T WheelSpeed_CSTATE;         /* '<S5>/Wheel Speed' */
  boolean_T Integrator_CSTATE;         /* '<S1>/Integrator' */
} XDis_brdemo_autotrans_T;

#ifndef ODE5_INTG
#define ODE5_INTG

/* ODE5 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[6];                        /* derivatives */
} ODE5_IntgData;

#endif

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: downth
   * Referenced by: '<S3>/interp_down'
   */
  real_T interp_down_RowIdx[6];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S3>/interp_down'
   *   '<S3>/interp_up'
   *   '<S7>/Look-Up Table'
   */
  real_T pooled1[4];

  /* Expression: downtab
   * Referenced by: '<S3>/interp_down'
   */
  real_T interp_down_Table[24];

  /* Expression: upth
   * Referenced by: '<S3>/interp_up'
   */
  real_T interp_up_RowIdx[6];

  /* Expression: uptab
   * Referenced by: '<S3>/interp_up'
   */
  real_T interp_up_Table[24];

  /* Expression: thvec
   * Referenced by: '<S1>/EngineTorque'
   */
  real_T EngineTorque_RowIdx[10];

  /* Expression: nevec
   * Referenced by: '<S1>/EngineTorque'
   */
  real_T EngineTorque_ColIdx[11];

  /* Expression: emap
   * Referenced by: '<S1>/EngineTorque'
   */
  real_T EngineTorque_Table[110];

  /* Expression: [2.393 1.450 1.000 0.677]
   * Referenced by: '<S7>/Look-Up Table'
   */
  real_T LookUpTable_YData[4];

  /* Pooled Parameter (Expression: speedratio)
   * Referenced by:
   *   '<S6>/FactorK'
   *   '<S6>/TorqueRatio'
   */
  real_T pooled3[21];

  /* Expression: Kfactor
   * Referenced by: '<S6>/FactorK'
   */
  real_T FactorK_YData[21];

  /* Expression: Torkratio
   * Referenced by: '<S6>/TorqueRatio'
   */
  real_T TorqueRatio_YData[21];
} ConstP_brdemo_autotrans_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T throttle;                     /* '<Root>/throttle' */
  real_T brake;                        /* '<Root>/brake' */
} ExtU_brdemo_autotrans_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T speed;                        /* '<Root>/speed' */
  real_T RPM;                          /* '<Root>/RPM' */
  real_T gear;                         /* '<Root>/gear' */
} ExtY_brdemo_autotrans_T;

/* Real-time Model Data Structure */
struct tag_RTM_brdemo_autotrans_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_brdemo_autotrans_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[2];
  real_T odeF[6][2];
  ODE5_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    struct {
      uint8_T TID[3];
    } TaskCounters;

    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[3];
  } Timing;
};

extern double arr[2];
extern double rb;
extern int outputrb;
extern char output[10000];

/* Block signals (default storage) */
extern B_brdemo_autotrans_T brdemo_autotrans_B;

/* Continuous states (default storage) */
extern X_brdemo_autotrans_T brdemo_autotrans_X;

/* Block states (default storage) */
extern DW_brdemo_autotrans_T brdemo_autotrans_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_brdemo_autotrans_T brdemo_autotrans_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_brdemo_autotrans_T brdemo_autotrans_Y;

/* Constant parameters (default storage) */
extern const ConstP_brdemo_autotrans_T brdemo_autotrans_ConstP;

/* Model entry point functions */
extern void brdemo_autotrans_initialize(void);
extern void brdemo_autotrans_step(void);
extern void brdemo_autotrans_terminate(void);

/* Real-time Model object */
extern RT_MODEL_brdemo_autotrans_T *const brdemo_autotrans_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'brdemo_autotrans'
 * '<S1>'   : 'brdemo_autotrans/Engine'
 * '<S2>'   : 'brdemo_autotrans/ShiftLogic'
 * '<S3>'   : 'brdemo_autotrans/ThresholdCalculation'
 * '<S4>'   : 'brdemo_autotrans/Transmission'
 * '<S5>'   : 'brdemo_autotrans/Vehicle'
 * '<S6>'   : 'brdemo_autotrans/Transmission/TorqueConverter'
 * '<S7>'   : 'brdemo_autotrans/Transmission/TransmissionRatio'
 */
#endif                                 /* RTW_HEADER_brdemo_autotrans_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
