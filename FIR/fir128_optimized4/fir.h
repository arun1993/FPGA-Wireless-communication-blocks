#ifndef FIR_H_
#define FIR_H_

#include "ap_cint.h"
#include "ap_int.h"

const int N=128;

typedef  int coef_t;
typedef  int data_t;
typedef  int acc_t;

void fir (
  acc_t *y,
  data_t x
  );

#endif
