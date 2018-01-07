/*
	Filename: fir.cpp
		FIR lab written for WES/CSE237C class at UCSD.

	INPUT:
		x: signal (chirp)

	OUTPUT:
		y: filtered output

*/

#include "fir.h"

void fir (data_t *y, data_t x) { 
  coef_t c[N] = {53, 0, -91, 0, 313, 500, 313, 0, -91, 0,53};
  static data_t delay_line[N];

  acc_t acc = 0;
  //acc_t mult;
  
  for (int i=N-1;i>=0;i--)
  {
     if (i==0)
     {
       //acc+=x*c[0];
       delay_line[0]=x;
     }
     else
     {
			delay_line[i]=delay_line[i-1];
			//acc+=delay_line[i]*c[i];
     }
     //mult = delay_line[i]*c[i];
     acc  = acc + delay_line[i]*c[i];

  }

  *y = (data_t) acc;
  
}

