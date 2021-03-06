/*
	Filename: fir.cpp
		FIR lab wirtten for WES/CSE237C class at UCSD.
		Match filter
	INPUT:
		x: signal (chirp)

	OUTPUT:
		y: filtered output

*/

#include "fir.h"

void fir (
  acc_t *y,
  data_t x
  )
{
     #pragma HLS pipeline II=1


	coef_t c[N] = {10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
	
	static data_t delay_line[N];
    #pragma HLS array_partition variable=delay_line complete dim=1
	//#pragma HLS array_partition variable=delay_line cyclic factor=2 dim=1
	//#pragma HLS array_partition variable=delay_line block factor=2 dim=1
	  acc_t acc = 0;

	  for (int9 i=N-1;i>=1;i--)
	  {

	  				delay_line[i]=delay_line[i-1];

	  	     acc  = acc + delay_line[i]*c[i];


	  }

	  acc = acc + x*c[0];
	  delay_line[0] = x;

	  *y =  acc;

}


