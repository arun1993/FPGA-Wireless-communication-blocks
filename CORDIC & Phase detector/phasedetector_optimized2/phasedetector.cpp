/*
	Filename: phasedetector.cpp
		Phase detector

	INPUT:
		I: signal for I sample
		Q: signal for Q sample

	OUTPUT:
		R: Radius
		Theta: Angle

*/

#include "phasedetector.h"


void phasedetector (
  data_t I,
  data_t Q,

  data_t *R,
  data_t *theta
  ){
#pragma HLS pipeline II=1
	data_t X, Y;
	data_t r, theta_t;
	// Write your code here
	fir(I,Q,&X,&Y);

	cordiccart2pol(X,Y,&r,&theta_t);

	*R = r;
	*theta = theta_t;





}




