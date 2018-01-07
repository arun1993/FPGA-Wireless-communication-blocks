/*
This is traditional 2-radix DIT FFT algorithm implementation.
INPUT:
	In_R, In_I[]: Real and Imag parts of Complex signal

OUTPUT:
	Out_R, Out_I[]: Real and Imag parts of Complex signal
*/

#include "fft.h"

void bit_reverse(DTYPE X_R[SIZE], DTYPE X_I[SIZE],DTYPE X_Copy_R[SIZE],DTYPE X_Copy_I[SIZE]);
void fft_stage_first(DTYPE X_R[SIZE], DTYPE X_I[SIZE], DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]);
void fft_stages(DTYPE X_R[SIZE], DTYPE X_I[SIZE], int STAGES, DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]);
void fft_stage_last(DTYPE X_R[SIZE], DTYPE X_I[SIZE], DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]);


void fft(DTYPE X_R[SIZE], DTYPE X_I[SIZE], DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE])
{
	DTYPE X_Copy_R[SIZE], X_Copy_I[SIZE];
	#pragma HLS dataflow
	//#pragma HLS array_partition variable=X_Copy_R block factor=10
	//#pragma HLS array_partition variable=X_Copy_I block factor=10


	bit_reverse(X_R, X_I,X_Copy_R, X_Copy_I);

	//Call fft
	DTYPE Stage1_R[SIZE], Stage1_I[SIZE];
	DTYPE Stage2_R[SIZE], Stage2_I[SIZE];
	DTYPE Stage3_R[SIZE], Stage3_I[SIZE];
	DTYPE Stage4_R[SIZE], Stage4_I[SIZE];
	DTYPE Stage5_R[SIZE], Stage5_I[SIZE];
	DTYPE Stage6_R[SIZE], Stage6_I[SIZE];
	DTYPE Stage7_R[SIZE], Stage7_I[SIZE];
	DTYPE Stage8_R[SIZE], Stage8_I[SIZE];
	DTYPE Stage9_R[SIZE], Stage9_I[SIZE];

	fft_stage_first(X_Copy_R, X_Copy_I, Stage1_R, Stage1_I);
	fft_stages(Stage1_R, Stage1_I, 2, Stage2_R, Stage2_I);
	fft_stages(Stage2_R, Stage2_I, 3, Stage3_R, Stage3_I);
	fft_stages(Stage3_R, Stage3_I, 4, Stage4_R, Stage4_I);
	fft_stages(Stage4_R, Stage4_I, 5, Stage5_R, Stage5_I);
	fft_stages(Stage5_R, Stage5_I, 6, Stage6_R, Stage6_I);
	fft_stages(Stage6_R, Stage6_I, 7, Stage7_R, Stage7_I);
	fft_stages(Stage7_R, Stage7_I, 8, Stage8_R, Stage8_I);
	fft_stages(Stage8_R, Stage8_I, 9, Stage9_R, Stage9_I);
	fft_stage_last(Stage9_R, Stage9_I, OUT_R, OUT_I);

}

unsigned int reverse_bits(unsigned int input) {
int i, rev = 0;
for (i = 0; i < FFT_BITS; i++) {
rev = (rev << 1) | (input & 1);
input = input >> 1;
	}
return rev;
}

void bit_reverse(DTYPE X_R[SIZE], DTYPE X_I[SIZE], DTYPE X_Copy_R[SIZE], DTYPE X_Copy_I[SIZE]){
	//Insert your code here
	unsigned int reversed;
	unsigned int i;
	DTYPE temp;
	for (i = 0; i < SIZE; i++) {
	reversed = reverse_bits(i); // Find the bit reversed index
	X_Copy_R[i] = X_R[i];
	X_Copy_I[i] = X_I[i];
	if (i < reversed) {
	// Swap the real values
	temp = X_R[i];
	X_R[i] = X_R[reversed];
	X_Copy_R[i] = X_R[i];
	X_R[reversed] = temp;
	X_Copy_R[reversed] = X_R[reversed];
	// Swap the imaginary values
	temp = X_I[i];
	X_I[i] = X_I[reversed];
	X_Copy_I[i] = X_I[i];
	X_I[reversed] = temp;
	X_Copy_I[reversed] = X_I[reversed];
			}
		}


}
/*=======================BEGIN: FFT=========================*/
//stage 1
void fft_stage_first(DTYPE X_R[SIZE], DTYPE X_I[SIZE], DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]) {

//Insert your code here
	//Insert your code here
	DTYPE temp_R; // temporary storage complex variable
	DTYPE temp_I; // temporary storage complex variable
	DTYPE Y_R[SIZE];
	DTYPE Y_I[SIZE];
	int i, j, k; // loop indexes
	int i_lower; // Index of lower point in butterfly
	int step, stage, DFTpts;
	int numBF; // Butterfly Width
	int N2 = SIZE2; // N2=N>>1
	//bit_reverse(X_R, X_I);
	//step = N2;
	DTYPE a, e, c, s;
	DFTpts = 2;
	//numBF = DFTpts / 2; // Butterfly WIDTHS in sub−DFT
	numBF = 1;
	c = W_real[0];
	s = W_imag[0];
	// Compute butterflies that use same W∗∗k
	for (i = 0; i < SIZE; i = i + DFTpts) {
//#pragma HLS unroll factor = 1024
//#pragma HLS array_partition variable=X_R complete
//#pragma HLS array_partition variable=X_I complete
//#pragma HLS array_partition variable=OUT_R complete
//#pragma HLS array_partition variable=OUT_I complete
//#pragma HLS array_partition variable=Y_R complete
//#pragma HLS array_partition variable=Y_I complete
	i_lower = i + numBF; // index of lower point in butterfly
	Y_R[i] = X_R[i];
	Y_I[i] = X_I[i];
	Y_R[i_lower] = X_R[i_lower];
	Y_I[i_lower] = X_I[i_lower];
	temp_R = Y_R[i_lower] * c - Y_I[i_lower] * s;
	temp_I = Y_I[i_lower] * c + Y_R[i_lower] * s;
	Y_R[i_lower] = Y_R[i] - temp_R;
	Y_I[i_lower] = Y_I[i] - temp_I;
	OUT_R[i_lower] = Y_R[i_lower];
	OUT_I[i_lower] = Y_I[i_lower];
	Y_R[i] = Y_R[i] + temp_R;
	Y_I[i] = Y_I[i] + temp_I;
	OUT_R[i] = Y_R[i];
	OUT_I[i] = Y_I[i];
	}
	//k += step;
	//}
	//step = step / 2;

}

//stages
void fft_stages(DTYPE X_R[SIZE], DTYPE X_I[SIZE], int stage, DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]) {

//Insert your code here
	//Write a code that computes any arbitary stages of the FFT
	DTYPE temp_R; // temporary storage complex variable
	DTYPE temp_I; // temporary storage complex variable
	DTYPE Y_R[SIZE];
	DTYPE Y_I[SIZE];
	int i, j, k; // loop indexes
	int i_lower; // Index of lower point in butterfly
	int step, DFTpts;
	int numBF; // Butterfly Width
	int N2 = SIZE2; // N2=N>>1
	//bit_reverse(X_R, X_I);
	//step = N2;
	DTYPE a, e, c, s;
	//stages:
	//for (stage = 1; stage <= M; stage++) { // Do M stages of butterflies
	DFTpts = 1 << stage; // DFT = 2^stage = points in sub DFT
	//DFTpts = 1024;
	//numBF = 512;
	numBF = DFTpts / 2; // Butterfly WIDTHS in sub−DFT
	//k = 0;
	//e = -6.283185307178 / DFTpts;
	//a = 0.0;
	// Perform butterflies for j−th stage
	butterfly:
	for (j = 0; j < numBF; j++) {
#pragma HLS loop_tripcount min=1 max=512 avg=256
	//c = cos(a);
	//s = sin(a);
	//a = a + e;
	c = W_real[j << (10 - stage)];
	s = W_imag[j << (10 - stage)];
	// Compute butterflies that use same W∗∗k
	for (i = j; i < SIZE; i = i + DFTpts) {
#pragma HLS loop_tripcount min=1 max=512 avg=256
	i_lower = i + numBF; // index of lower point in butterfly
	Y_R[i] = X_R[i];
	Y_I[i] = X_I[i];
	Y_R[i_lower] = X_R[i_lower];
	Y_I[i_lower] = X_I[i_lower];
	temp_R = Y_R[i_lower] * c - Y_I[i_lower] * s;
	temp_I = Y_I[i_lower] * c + Y_R[i_lower] * s;
	Y_R[i_lower] = Y_R[i] - temp_R;
	Y_I[i_lower] = Y_I[i] - temp_I;
	OUT_R[i_lower] = Y_R[i_lower];
	OUT_I[i_lower] = Y_I[i_lower];
	Y_R[i] = Y_R[i] + temp_R;
	Y_I[i] = Y_I[i] + temp_I;
	OUT_R[i] = Y_R[i];
	OUT_I[i] = Y_I[i];
			}
	//k += step;
		}
	//step = step / 2;

}


//last stage
void fft_stage_last(DTYPE X_R[SIZE], DTYPE X_I[SIZE], DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]) {

//Insert your code here
	//Write code that computes last stage of FFT
	DTYPE temp_R; // temporary storage complex variable
	DTYPE temp_I; // temporary storage complex variable
	DTYPE Y_R[SIZE];
	DTYPE Y_I[SIZE];
	int i, j, k; // loop indexes
	int i_lower; // Index of lower point in butterfly
	int step, stage, DFTpts;
	int numBF; // Butterfly Width
	int N2 = SIZE2; // N2=N>>1
	//bit_reverse(X_R, X_I);
	//step = N2;
	DTYPE a, e, c, s;
	//stages:
	//for (stage = 1; stage <= M; stage++) { // Do M stages of butterflies
	//DFTpts = 1 << stage; // DFT = 2^stage = points in sub DFT
	DFTpts = 1024;
	//numBF = DFTpts / 2; // Butterfly WIDTHS in sub−DFT
	numBF = 512;
	//k = 0;
	//e = -6.283185307178 / DFTpts;
	//a = 0.0;
	// Perform butterflies for j−th stage
	butterfly:
	for (j = 0; j < numBF; j++) {
#pragma HLS loop_tripcount min=1 max=512 avg=256
	//c = cos(a);
	//s = sin(a);
	//a = a + e;
	c = W_real[j];
	s = W_imag[j];
	// Compute butterflies that use same W∗∗k
	for (i = j; i < SIZE; i = i + DFTpts) {
#pragma HLS loop_tripcount min=1 max=512 avg=256
	i_lower = i + numBF; // index of lower point in butterfly
	Y_R[i] = X_R[i];
	Y_I[i] = X_I[i];
	Y_R[i_lower] = X_R[i_lower];
	Y_I[i_lower] = X_I[i_lower];
	temp_R = Y_R[i_lower] * c - Y_I[i_lower] * s;
	temp_I = Y_I[i_lower] * c + Y_R[i_lower] * s;
	Y_R[i_lower] = Y_R[i] - temp_R;
	Y_I[i_lower] = Y_I[i] - temp_I;
	OUT_R[i_lower] = Y_R[i_lower];
	OUT_I[i_lower] = Y_I[i_lower];
	Y_R[i] = Y_R[i] + temp_R;
	Y_I[i] = Y_I[i] + temp_I;
	OUT_R[i] = Y_R[i];
	OUT_I[i] = Y_I[i];
			}
	//k += step;
		}
	//step = step / 2;
}
/*=======================END: FFT=========================*/




