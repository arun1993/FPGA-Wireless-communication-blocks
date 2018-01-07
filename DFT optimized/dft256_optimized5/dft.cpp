#include <math.h> //Required for cos and sin functions
#include "dft.h"
#include "coefficients256.h"
//typedef double DTYPE; // Data type for the input signal
typedef double TEMP_TYPE; // Data type for the temporary variables
//#define N 256 // DFT Size
//#define SIZE 256
void dft(INTYPE input_real[SIZE] , INTYPE input_imag[SIZE] , DTYPE sample_real[SIZE], DTYPE sample_imag[SIZE]) {
int i, j;
TEMP_TYPE w;
TEMP_TYPE c, s;
// Temporary arrays to hold the intermediate frequency domain results
// Calculate each frequency domain sample iteratively
for (i = 0; i < SIZE; i += 1) {

// Calculate the jth frequency sample sequentially
for (j = 0; j < SIZE; j += 1) {
#pragma HLS array_partition variable=cos_coefficients_table block factor=128
#pragma HLS array_partition variable=sin_coefficients_table block factor=128
// Fetch precomputed sine and cosine values
#pragma HLS unroll factor=128
	c = cos_coefficients_table[(i * j)%SIZE];
	s = sin_coefficients_table[(i * j)%SIZE];
	// Multiply c and s with the appropriate input sample and keep running sum


	sample_real[i] += (DTYPE)input_real[j] * c - (DTYPE)input_imag[j] * s;
	sample_imag[i] += (DTYPE)input_real[j] * s + (DTYPE)input_imag[j] * c;
	}
}

}
