/*
	Filename: fir.h
		Header file
		FIR lab wirtten for WES/CSE237C class at UCSD.

*/
#ifndef FIR_H_
#define FIR_H_

#include "ap_cint.h"
#include "ap_int.h"

const int9 N=128;

typedef  int5 coef_t;
typedef  int8 data_t;
typedef  int16 acc_t;

void fir (
  acc_t *y,
  data_t x
  );

#endif
