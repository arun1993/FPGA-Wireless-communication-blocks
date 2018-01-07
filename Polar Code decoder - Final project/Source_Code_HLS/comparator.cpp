#include <math.h>
#include <stdio.h>
#include "list_decoder.h"
void comparator(UINT_PREC in0_data[LS], UINT_LOG2_LS_P1 in0_index[LS], UINT_PREC in1_data[LS], UINT_LOG2_LS_P1 in1_index[LS], UINT_PREC max_data[LS], UINT_LOG2_LS_P1 max_index[LS], UINT_PREC min_data[LS], UINT_LOG2_LS_P1 min_index[LS]){
#pragma HLS PIPELINE
	int k;
	comparator_lp: for (k=0; k<LS; k++){
		if (in0_data[k] > in1_data[k]){
			max_data[k] = in0_data[k];
			min_data[k] = in1_data[k];
			max_index[k] = in0_index[k];
			min_index[k] = in1_index[k];
		}
		else{
			max_data[k] = in1_data[k];
			min_data[k] = in0_data[k];
			max_index[k] = in1_index[k];
			min_index[k] = in0_index[k];
		}
	}
}
