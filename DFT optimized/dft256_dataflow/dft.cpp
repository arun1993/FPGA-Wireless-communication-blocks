#include <math.h> //Required for cos and sin functions
#include "dft.h"
#include "coefficients256.h"
//typedef double DTYPE; // Data type for the input signal
typedef double TEMP_TYPE; // Data type for the temporary variables
//#define N 256 // DFT Size
void input_function(INTYPE *input_real , INTYPE *input_imag , TEMP_TYPE *temp_real, TEMP_TYPE *temp_imag);
void output_function(TEMP_TYPE *temp_real, TEMP_TYPE *temp_imag, DTYPE *sample_real, DTYPE *sample_imag);

void input_function(INTYPE *input_real , INTYPE *input_imag , TEMP_TYPE *temp_real, TEMP_TYPE *temp_imag) {
    int i;
    for(i = 0; i < SIZE ; i += 1) {
        *(temp_real+i) = (TEMP_TYPE)*(input_real+i);
        *(temp_imag+i) = (TEMP_TYPE)*(input_imag+i);
    }
}

void output_function(TEMP_TYPE *temp_real, TEMP_TYPE *temp_imag, DTYPE *sample_real, DTYPE *sample_imag) {
    int i,j;
    TEMP_TYPE c, s;
    for (i = 0; i < SIZE; i += 1) {
    // Calculate the jth frequency sample sequentially
    for (j = 0; j < SIZE; j += 1) {

    c = cos_coefficients_table[(i * j)%SIZE];
    s = sin_coefficients_table[(i * j)%SIZE];

    *(sample_real+i) += (DTYPE)*(temp_real+j) * c - (DTYPE)*(temp_imag+j) * s;
    *(sample_imag+i) += (DTYPE)*(temp_real+j) * s + (DTYPE)*(temp_imag+j) * c;
        }
    }
}

//#define SIZE 256
void dft(INTYPE input_real[SIZE] , INTYPE input_imag[SIZE] , DTYPE sample_real[SIZE], DTYPE sample_imag[SIZE]) {
#pragma HLS DATAFLOW
int i, j;
TEMP_TYPE w;
TEMP_TYPE c, s;
TEMP_TYPE temp_real[SIZE], temp_imag[SIZE];

input_function(input_real,input_imag, temp_real, temp_imag);
output_function(temp_real,temp_imag,sample_real,sample_imag);

}
