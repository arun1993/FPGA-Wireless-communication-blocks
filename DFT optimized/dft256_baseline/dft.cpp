#include <math.h>
#include "dft.h"
//#include"coefficients256.h"
typedef double TEMP_TYPE; //Data Type for Temporary Variables
#define N 256 //DFt Size

void dft(DTYPE real_sample[SIZE], DTYPE imag_sample[SIZE])
{
    //Write your code here
    int i,j;
    TEMP_TYPE w;
    TEMP_TYPE c,s;

    //Temporary arrays to store the intermediate frequency domain results
    TEMP_TYPE temp_real[N];
    TEMP_TYPE temp_imag[N];
    // Calculate each frequency domain sample iteratively
    for (i = 0; i < N; i += 1) {
        temp_real[i] = 0;
        temp_imag[i] = 0;

        // (2 ∗ pi ∗ i)/N
        w = - 2.0 * 3.141592653589 * (TEMP_TYPE)i / (TEMP_TYPE)N;

        // Calculate the jth frequency sample sequentially
        for (j = 0; j < N; j += 1) {
            // Utilize HLS tool to calculate sine and cosine values
            c = cos(j * w);
            s = sin(j * w);

            // Multiply the current phasor with the appropriate input sample and keep
            // running sum

            temp_real[i] += real_sample[j] * c - imag_sample[j] * s;
            temp_imag[i] += real_sample[j] * s + imag_sample[j] * c;
            }
        }
            // Perform an inplace DFT, i.e., copy result into the input arrays
            for (i = 0; i < N; i += 1) {
            real_sample[i] = temp_real[i];
            imag_sample[i] = temp_imag[i];
        }
    }
