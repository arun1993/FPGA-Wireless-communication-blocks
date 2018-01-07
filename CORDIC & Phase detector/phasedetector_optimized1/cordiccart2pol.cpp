#include "cordiccart2pol.h"

data_t Kvalues[NO_ITER] = {1,	0.500000000000000,	0.250000000000000,	0.125000000000000,	0.0625000000000000,	0.0312500000000000,	0.0156250000000000,	0.00781250000000000,	0.00390625000000000,	0.00195312500000000,	0.000976562500000000,	0.000488281250000000,	0.000244140625000000,	0.000122070312500000,	6.10351562500000e-05,	3.05175781250000e-05};

data_t angles[NO_ITER] = {0.785398163397448,	0.463647609000806,	0.244978663126864,	0.124354994546761,	0.0624188099959574,	0.0312398334302683,	0.0156237286204768,	0.00781234106010111,	0.00390623013196697,	0.00195312251647882,	0.000976562189559320,	0.000488281211194898,	0.000244140620149362,	0.000122070311893670,	6.10351561742088e-05,	3.05175781155261e-05};


void cordiccart2pol(data_t x, data_t y, data_t * r,  data_t * theta)
{
	// Write your code here
#pragma HLS pipeline II=1


    float theta_temp = 0;
	//ap_fixed<14,3,AP_RND> theta_temp = 0;

	// Set the initial vector that we will rotate
	// current cos = I; current sin = Q
	COS_SIN_TYPE current_cos,current_sin;

	//x and y are copied to the current cos and current_sin
	current_cos = x;
	current_sin = y;
	float pi_2 = 1.571428571428571;
	//ap_ufixed<14,3,AP_RND> pi_2 = 1.571428571428571;

    //Fit the complex number into the 1st/4th the quadrants
	if (y < 0) {
		current_cos = -y;
		current_sin = x;
		theta_temp =  -pi_2;
	} else {
		current_cos = y;
		current_sin = -x;
		theta_temp = pi_2;
	}
	//current_cos = y<0 ? -y : y;
	//current_sin = y<0 ? x : -x;
	//theta_temp = y<0 ? -pi_2 : pi_2;

	// Only takes values -1/1
	int sigma = 0;
	//ap_fixed<14,3,AP_RND> sigma = 0;
	// Factor is the 2^(-L) value
	//float factor;
	// This loop iteratively rotates the initial vector to nd the
	// sine and cosine values corresponding to the input theta angle
	for (int j=0; j < NO_ITER; j++)
	{
	    // Determine if we are rotating by a positive or negative angle
	    /*if (current_sin < 0)
	    {
	    sigma = 1;
	    }
	    else
	    {
	    sigma = -1;
	    }*/
		sigma = current_sin < 0 ? 1 : -1;

	    // Save the current cos, so that it can be used in the sine calculation
	    COS_SIN_TYPE temp_cos = current_cos;
	    // Perform the rotation
	    current_cos = current_cos - current_sin * sigma * Kvalues[j];
	    current_sin = temp_cos * sigma * Kvalues[j] + current_sin;

	    // Determine the new theta
	    theta_temp = theta_temp - sigma * angles[j];
	    // Calculate next 2^(􀀀L) value
	    //factor = factor >> 1;
	}
	*theta = theta_temp;
    //*r = current_cos/(ap_ufixed<14,3,AP_RND>)1.6467760;
	*r = current_cos/1.6467760;
	
}
