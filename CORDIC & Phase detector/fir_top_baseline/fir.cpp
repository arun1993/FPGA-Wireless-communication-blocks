/*
	Filename: fir.cpp
		Complex FIR or Match filter
		firI1 and firI2 share coef_t c[N]
		firQ1 and firQ2 share coef_t c[N]
		
	INPUT:
		I: signal for I sample
		I: signal for Q sample

	OUTPUT:
		X: filtered output
		Y: filtered output

*/

#include "fir.h"

void firI1 (
  data_t *y,
  data_t x
  ) {

	coef_t c[N] = {1,    -1,    1,    -1,    -1,    -1,    1,    1,    -1,    -1,    -1,    1,    1,    -1,    1,    -1,    -1,    -1,    -1,    1,    1,    1,    1,    1,    -1,    -1,    1,    1,    1,    -1,    -1,    -1};

	// Write your code here
	#pragma HLS pipeline II=1
	 static data_t delay_line[N];
	    #pragma HLS array_partition variable=delay_line complete dim=1
		//#pragma HLS array_partition variable=delay_line cyclic factor=2 dim=1
		//#pragma HLS array_partition variable=delay_line block factor=2 dim=1
		  acc_t acc = 0;

		  for (int i=N-1;i>=1;i--)
		  {

		  				delay_line[i]=delay_line[i-1];

		  	     acc  = acc + delay_line[i]*c[i];


		  }

		  acc = acc + x*c[0];
		  delay_line[0] = x;

		  *y =  acc;

	
}


void firI2 (
  data_t *y,
  data_t x
  ) {

	coef_t c[N] = {1,    -1,    1,    -1,    -1,    -1,    1,    1,    -1,    -1,    -1,    1,    1,    -1,    1,    -1,    -1,    -1,    -1,    1,    1,    1,    1,    1,    -1,    -1,    1,    1,    1,    -1,    -1,    -1};

	// Write your code here
#pragma HLS pipeline II=1
 static data_t delay_line[N];
    #pragma HLS array_partition variable=delay_line complete dim=1
	//#pragma HLS array_partition variable=delay_line cyclic factor=2 dim=1
	//#pragma HLS array_partition variable=delay_line block factor=2 dim=1
	  acc_t acc = 0;

	  for (int i=N-1;i>=1;i--)
	  {

	  				delay_line[i]=delay_line[i-1];

	  	     acc  = acc + delay_line[i]*c[i];


	  }

	  acc = acc + x*c[0];
	  delay_line[0] = x;

	  *y =  acc;
}




void firQ1 (
  data_t *y,
  data_t x
  ) {

	coef_t c[N] = {-1,    -1,    1,    -1,    1,    -1,    1,    -1,    -1,    -1,    -1,    1,    -1,    1,    -1,    1,    1,    -1,    1,    -1,    -1,    1,    -1,    1,    1,    1,    1,    -1,    1,    -1,    1,    1};


	// Write your code here
#pragma HLS pipeline II=1
 static data_t delay_line[N];
    #pragma HLS array_partition variable=delay_line complete dim=1
	//#pragma HLS array_partition variable=delay_line cyclic factor=2 dim=1
	//#pragma HLS array_partition variable=delay_line block factor=2 dim=1
	  acc_t acc = 0;

	  for (int i=N-1;i>=1;i--)
	  {

	  				delay_line[i]=delay_line[i-1];

	  	     acc  = acc + delay_line[i]*c[i];


	  }

	  acc = acc + x*c[0];
	  delay_line[0] = x;

	  *y =  acc;
}

void firQ2 (
  data_t *y,
  data_t x
  ) {

	coef_t c[N] = {-1,    -1,    1,    -1,    1,    -1,    1,    -1,    -1,    -1,    -1,    1,    -1,    1,    -1,    1,    1,    -1,    1,    -1,    -1,    1,    -1,    1,    1,    1,    1,    -1,    1,    -1,    1,    1};


	// Write your code here
#pragma HLS pipeline II=1
 static data_t delay_line[N];
    #pragma HLS array_partition variable=delay_line complete dim=1
	//#pragma HLS array_partition variable=delay_line cyclic factor=2 dim=1
	//#pragma HLS array_partition variable=delay_line block factor=2 dim=1
	  acc_t acc = 0;

	  for (int i=N-1;i>=1;i--)
	  {

	  				delay_line[i]=delay_line[i-1];

	  	     acc  = acc + delay_line[i]*c[i];


	  }

	  acc = acc + x*c[0];
	  delay_line[0] = x;

	  *y =  acc;
}


void fir (
  data_t I,
  data_t Q,

  data_t *X,
  data_t *Y
  ) {

	// Write your code here
	//#pragma HLS pipeline II=1
	data_t IinIfir, QinQfir, QinIfir, IinQfir;
	
	firI1(&IinIfir,I);
	firQ1(&QinQfir,Q);
	firI2(&QinIfir,Q);
	firQ2(&IinQfir,I);
	//Calculate X
	*X = IinIfir + QinQfir;
	//Calculate Y
	*Y = QinIfir - IinQfir;

}


