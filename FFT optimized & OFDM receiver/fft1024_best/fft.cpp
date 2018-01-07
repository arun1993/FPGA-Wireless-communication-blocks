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

/*#pragma HLS array_partition variable=X_R block factor = 12
#pragma HLS array_partition variable=X_I block factor = 12
#pragma HLS array_partition variable=OUT_R block factor = 12
#pragma HLS array_partition variable=OUT_I block factor = 12
#pragma HLS array_partition variable=X_Copy_R block factor = 12
#pragma HLS array_partition variable=X_Copy_I block factor = 12*/

/*#pragma HLS array_partition variable=Stage1_R block factor = 12
#pragma HLS array_partition variable=Stage2_R block factor = 12
#pragma HLS array_partition variable=Stage3_R block factor = 12
#pragma HLS array_partition variable=Stage4_R block factor = 12
#pragma HLS array_partition variable=Stage5_R block factor = 12
#pragma HLS array_partition variable=Stage6_R block factor = 12
#pragma HLS array_partition variable=Stage7_R block factor = 12
#pragma HLS array_partition variable=Stage8_R block factor = 12
#pragma HLS array_partition variable=Stage9_R block factor = 12

#pragma HLS array_partition variable=Stage1_I block factor = 12
#pragma HLS array_partition variable=Stage2_I block factor = 12
#pragma HLS array_partition variable=Stage3_I block factor = 12
#pragma HLS array_partition variable=Stage4_I block factor = 12
#pragma HLS array_partition variable=Stage5_I block factor = 12
#pragma HLS array_partition variable=Stage6_I block factor = 12
#pragma HLS array_partition variable=Stage7_I block factor = 12
#pragma HLS array_partition variable=Stage8_I block factor = 12
#pragma HLS array_partition variable=Stage9_I block factor = 12*/


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
#pragma HLS pipeline
#pragma HLS inline region
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

	DTYPE temp_R; // temporary storage complex variable
	DTYPE temp_I; // temporary storage complex variable
	DTYPE Y_R[SIZE];
	DTYPE Y_I[SIZE];

//#pragma HLS array_partition variable=Y_R cyclic factor = 12
//#pragma HLS array_partition variable=Y_I cyclic factor = 12
	int i, j, k; // loop indexes
	int i_lower; // Index of lower point in butterfly
	int step, stage, DFTpts;
	int numBF; // Butterfly Width
	int N2 = SIZE2; // N2=N>>1

	DTYPE a, e, c, s;
	DFTpts = 2;
	numBF = 1;
	c = W_real[0];
	s = W_imag[0];
	// Compute butterflies that use same W∗∗k
	for (i = 0; i < SIZE; i = i + DFTpts) {
#pragma HLS pipeline
	i_lower = i + numBF; // index of lower point in butterfly
	Y_R[i] = X_R[i];
	Y_I[i] = X_I[i];
	Y_R[i_lower] = X_R[i_lower];
	Y_I[i_lower] = X_I[i_lower];
	temp_R = Y_R[i_lower] * c - Y_I[i_lower] * s;
	temp_I = Y_I[i_lower] * c + Y_R[i_lower] * s;
	OUT_R[i_lower] = Y_R[i] - temp_R;
	OUT_I[i_lower] = Y_I[i] - temp_I;

	OUT_R[i] = Y_R[i] + temp_R;
	OUT_I[i] = Y_I[i] + temp_I;

	}

}

//stages
void fft_stages(DTYPE X_R[SIZE], DTYPE X_I[SIZE], int stage, DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]) {

	DTYPE Y_R[SIZE];
	DTYPE Y_I[SIZE];
	//Write a code that computes any arbitary stages of the FFT

//#pragma HLS array_partition variable=Y_R block factor=12
//#pragma HLS array_partition variable=Y_I block factor=12


	DTYPE temp_R; // temporary storage complex variable
	DTYPE temp_I; // temporary storage complex variable

	int i, j, k,j1,i1,j2; // loop indexes
	int i_lower; // Index of lower point in butterfly
	int step, DFTpts;
	int numBF; // Butterfly Width
	int N2 = SIZE2; // N2=N>>1
	DTYPE a, e, c, s;
	DFTpts = 1 << stage; // DFT = 2^stage = points in sub DFT
	numBF = DFTpts >> 1; // Butterfly WIDTHS in sub−DFT
	// Perform butterflies for j−th stage
	butterfly:
	for (j = 0; j < 512; j++) {
	#pragma HLS pipeline
	j1 = j >> (10-stage);
	j2 = j%(1<<(10-stage));
	c = W_real[j1 << (10 - stage)];
	s = W_imag[j1 << (10 - stage)];
	// Compute butterflies that use same W∗∗k
	i1 = (DFTpts * j2) + j1;
	i_lower = i1 + numBF; // index of lower point in butterfly
	Y_R[i1] = X_R[i1];
	Y_I[i1] = X_I[i1];
	Y_R[i_lower] = X_R[i_lower];
	Y_I[i_lower] = X_I[i_lower];
	temp_R = Y_R[i_lower] * c - Y_I[i_lower] * s;
	temp_I = Y_I[i_lower] * c + Y_R[i_lower] * s;
	OUT_R[i_lower] = Y_R[i1] - temp_R;
	OUT_I[i_lower] = Y_I[i1] - temp_I;

	OUT_R[i1] = Y_R[i1] + temp_R;
	OUT_I[i1] = Y_I[i1] + temp_I;

	}

}


//last stage
void fft_stage_last(DTYPE X_R[SIZE], DTYPE X_I[SIZE], DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]) {

	DTYPE Y_R[SIZE];
	DTYPE Y_I[SIZE];
	//Write a code that computes any arbitary stages of the FFT

//#pragma HLS array_partition variable=Y_R block factor=12
//#pragma HLS array_partition variable=Y_I block factor=12


	DTYPE temp_R; // temporary storage complex variable
	DTYPE temp_I; // temporary storage complex variable

	int i, j, k,j1,i1,j2; // loop indexes
	int i_lower; // Index of lower point in butterfly
	int step, DFTpts;
	int numBF; // Butterfly Width
	int N2 = SIZE2; // N2=N>>1
	DTYPE a, e, c, s;
	DFTpts = 1024; // DFT = 2^stage = points in sub DFT
	numBF = 512; // Butterfly WIDTHS in sub−DFT
	// Perform butterflies for j−th stage
	butterfly:
	for (j = 0; j < 512; j++) {
	#pragma HLS pipeline
	j1 = j;
	j2 = 0;
	c = W_real[j1];
	s = W_imag[j1];
	// Compute butterflies that use same W∗∗k
	i1 = (DFTpts * j2) + j1;
	i_lower = i1 + numBF; // index of lower point in butterfly
	Y_R[i1] = X_R[i1];
	Y_I[i1] = X_I[i1];
	Y_R[i_lower] = X_R[i_lower];
	Y_I[i_lower] = X_I[i_lower];
	temp_R = Y_R[i_lower] * c - Y_I[i_lower] * s;
	temp_I = Y_I[i_lower] * c + Y_R[i_lower] * s;
	OUT_R[i_lower] = Y_R[i1] - temp_R;
	OUT_I[i_lower] = Y_I[i1] - temp_I;

	OUT_R[i1] = Y_R[i1] + temp_R;
	OUT_I[i1] = Y_I[i1] + temp_I;

	}

}
/*=======================END: FFT=========================*/




