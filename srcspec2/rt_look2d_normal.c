/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: rt_look2d_normal.c
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

#include "rt_look2d_normal.h"

/* 2D normal lookup routine for data type of real_T. */
real_T rt_Lookup2D_Normal(const real_T *xVals, const int_T numX,
  const real_T *yVals, const int_T numY,
  const real_T *zVals,
  const real_T x, const real_T y)
{
  int_T xIdx, yIdx;
  real_T ylo, yhi;
  real_T Zx0yhi, Zx0ylo, xlo, xhi;
  real_T corner1, corner2;
  xIdx = rt_GetLookupIndex(xVals,numX,x);
  xlo = xVals[xIdx];
  xhi = xVals[xIdx+1];
  yIdx = rt_GetLookupIndex(yVals,numY,y);
  ylo = yVals[yIdx];
  yhi = yVals[yIdx+1];
  corner1 = *(zVals + xIdx + (numX * yIdx));
  corner2 = *(zVals + (xIdx+1) + (numX * yIdx));
  Zx0ylo = INTERP(x, xlo, xhi, corner1, corner2);
  corner1 = *(zVals + xIdx + (numX * (yIdx+1)));
  corner2 = *(zVals + (xIdx+1) + (numX*(yIdx+1)));
  Zx0yhi = INTERP(x, xlo, xhi, corner1, corner2);
  return (INTERP(y,ylo,yhi,Zx0ylo,Zx0yhi));
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
