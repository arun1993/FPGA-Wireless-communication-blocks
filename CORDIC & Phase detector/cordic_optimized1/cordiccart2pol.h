#ifndef CORDICCART2POL_H
#define CORDICCART2POL_H
#include<ap_fixed.h>

#define NO_ITER 16

typedef int   coef_t;
//typedef float data_t;
typedef ap_fixed<14,3,AP_RND> data_t;
typedef float acc_t;
typedef ap_fixed<14,3,AP_RND> COS_SIN_TYPE;
//typedef float COS_SIN_TYPE;

void cordiccart2pol(data_t x, data_t y, data_t * r,  data_t * theta);

#endif
