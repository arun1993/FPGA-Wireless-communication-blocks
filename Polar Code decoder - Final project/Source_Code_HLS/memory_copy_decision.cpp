#include <stdio.h>
#include <math.h>
#include "list_decoder.h"

void memory_copy_decision(UINT_1 memory_block[LS][BL],UINT_LOG2_LS_P1 index_list[LS]){
#pragma HLS PIPELINE
//#pragma HLS INTERFACE port=memory_block
//#pragma HLS INTERFACE port=index_list
//#pragma HLS ARRAY_RESHAPE variable=passed_LL complete dim=1
#pragma HLS ARRAY_RESHAPE variable=index_list complete dim=1
#pragma HLS ARRAY_RESHAPE variable=memory_block complete dim=1
#pragma HLS ARRAY_RESHAPE variable=memory_block complete dim=2
	int i,j;
	UINT_1 temp_memory[LS][BL];
#pragma HLS ARRAY_RESHAPE variable=temp_memory complete dim=2
#pragma HLS ARRAY_RESHAPE variable=temp_memory complete dim=1
	Copying_Outer_Loop:for(i=0;i<LS;i++){
//#pragma HLS UNROLL
		Copying_Inner_Loop:for(j=0;j<BL;j++){
//#pragma HLS UNROLL
			temp_memory[i][j]=memory_block[(index_list[i]-(index_list[i]%2))/2][j];
		}
	}
	Writing_Outer_Loop:for(i=0;i<LS;i++){
//#pragma HLS UNROLL
		Writing_Inner_Loop:for(j=0;j<BL;j++){
//#pragma HLS UNROLL
			memory_block[i][j]=temp_memory[i][j];
		}
	}
}
