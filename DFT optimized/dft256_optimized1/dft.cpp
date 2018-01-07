#include <math.h> //Required for cos and sin functions
#include "dft.h"
#include "coefficients256.h"
//typedef double DTYPE; // Data type for the input signal
typedef double TEMP_TYPE; // Data type for the temporary variables
//#define N 256 // DFT Size
//#define SIZE 256
void dft(DTYPE sample_real[SIZE], DTYPE sample_imag[SIZE]) {
int i, j;
TEMP_TYPE w;
TEMP_TYPE c, s;
// Temporary arrays to hold the intermediate frequency domain results
TEMP_TYPE temp_real[SIZE];
TEMP_TYPE temp_imag[SIZE];
// Calculate each frequency domain sample iteratively
for (i = 0; i < SIZE; i += 1) {
temp_real[i] = 0;
temp_imag[i] = 0;
// Calculate the jth frequency sample sequentially
for (j = 0; j < SIZE; j += 1) {
// Fetch precomputed sine and cosine values
c = cos_coefficients_table[(i * j)%SIZE];
s = sin_coefficients_table[(i * j)%SIZE];
// Multiply c and s with the appropriate input sample and keep running sum
temp_real[i] += sample_real[j] * c - sample_imag[j] * s;
temp_imag[i] += sample_real[j] * s + sample_imag[j] * c;
	}
}
// Perform an inplace DFT, i.e., copy result into the input arrays
for (i = 0; i < SIZE; i += 1) {
sample_real[i] = temp_real[i];
sample_imag[i] = temp_imag[i];
	}
}
