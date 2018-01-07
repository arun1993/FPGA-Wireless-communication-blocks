#include <stdio.h>
#include <math.h>
#include "list_decoder.h"

void memory_transfer(UINT_LOG2_LS memory_block[LS][BW-1],UINT_LOG2_LS_P1 index_list[LS], UINT_1 passed_LL[LS]){
#pragma HLS PIPELINE
#pragma HLS ARRAY_RESHAPE variable=passed_LL complete dim=1
#pragma HLS ARRAY_RESHAPE variable=index_list complete dim=1
#pragma HLS ARRAY_RESHAPE variable=memory_block complete dim=1
#pragma HLS ARRAY_RESHAPE variable=memory_block complete dim=2
	int i,j;
	UINT_1 inner_LL[LS];
//#pragma HLS ARRAY_RESHAPE variable=inner_LL complete dim=1
	UINT_LOG2_LS temp_memory[LS][BW-1];
#pragma HLS ARRAY_RESHAPE variable=temp_memory complete dim=2
#pragma HLS ARRAY_RESHAPE variable=temp_memory complete dim=1
//#pragma HLS ARRAY_RESHAPE variable=memory_block complete dim=2
//#pragma HLS ARRAY_RESHAPE variable=memory_block complete dim=1
	Copying_Outer_Loop:for(i=0;i<LS;i++){
//#pragma HLS UNROLL
		inner_LL[i]=index_list[i]%2;
		Copying_Inner_Loop:for(j=0;j<BW-1;j++){
//#pragma HLS UNROLL
			temp_memory[i][j]=memory_block[(index_list[i]-(index_list[i]%2))/2][j];
		}
	}
	Writing_Outer_Loop:for(i=0;i<LS;i++){
//#pragma HLS UNROLL
		passed_LL[i]=inner_LL[i];
		Writing_Inner_Loop:for(j=0;j<BW-1;j++){
//#pragma HLS UNROLL
			memory_block[i][j]=temp_memory[i][j];
		}
	}
}

