#include "fft.h"

void qpsk_decode(DTYPE R[SIZE], DTYPE I[SIZE], int D[SIZE]) {

	int dec_bit, i;
	DTYPE x2, y2;
	for(i = 0 ; i < SIZE ; i++) {
	x2 = R[i];
	y2 = I[i];
	if(x2 >= 0 && y2 >= 0) { dec_bit = 0; }
	if(x2 > 0 && y2 < 0) { dec_bit = 2; }
	if(x2 < 0 && y2 > 0) { dec_bit = 1; }
	if(x2 < 0 && y2 < 0) { dec_bit = 3; }
	D[i] = dec_bit;
	}
}

