#include <stdio.h>
#include <math.h>
#include "list_decoder.h"


void sortAndForward(UINT_PREC ll0_i[LS], UINT_PREC ll1_i[LS], UINT_LOG2_LS memory_block[LS][BW-1], UINT_1 memory_block_dec[LS][BL], UINT_1 passed_LL[LS]){
#pragma HLS inline region
//#pragma HLS PIPELINE
//#pragma HLS ARRAY_RESHAPE variable=passed_LL complete dim=1
//#pragma HLS ARRAY_PARTITION variable=memory_block complete dim=1
//#pragma HLS ARRAY_PARTITION variable=memory_block complete dim=2
//#pragma HLS ARRAY_PARTITION variable=memory_block_dec complete dim=1
//#pragma HLS ARRAY_PARTITION variable=memory_block_dec complete dim=2
//#pragma HLS ARRAY_RESHAPE variable=ll1_i complete dim=1
//#pragma HLS ARRAY_RESHAPE variable=ll0_i complete dim=1
	int i,j;
	UINT_LOG2_LS_P1 index_o[LS];
//#pragma HLS ARRAY_RESHAPE variable=index_o complete dim=1
	UINT_1 inner_passed_LL[LS];
//#pragma HLS ARRAY_RESHAPE variable=inner_passed_LL complete dim=1
	UINT_LOG2_LS memo_block[LS][BW-1];
//#pragma HLS ARRAY_RESHAPE variable=memo_block complete dim=1
//#pragma HLS ARRAY_RESHAPE variable=memo_block complete dim=2
	UINT_1 memo_block_dec[LS][BL];
//#pragma HLS ARRAY_RESHAPE variable=memo_block_dec complete dim=1
//#pragma HLS ARRAY_RESHAPE variable=memo_block_dec complete dim=2
	Read_Memo_Outer_Loop:for(i=0;i<LS;i++){
//#pragma HLS UNROLL
		Read_Memo_Inner_Loop:for(j=0;j<BW-1;j++){
//#pragma HLS UNROLL
			memo_block[i][j]=memory_block[i][j];
		}
	}
	Read_Mem_Outer_Loop:for(i=0;i<LS;i++){
//#pragma HLS UNROLL
		Read_Mem_Inner_Loop:for(j=0;j<BL;j++){
//#pragma HLS UNROLL
			memo_block_dec[i][j]=memory_block_dec[i][j];
		}
	}

	bitonic_sorter(ll0_i, ll1_i, index_o);
	memory_transfer(memo_block,index_o, inner_passed_LL);
	memory_copy_decision(memo_block_dec, index_o );

	Write_Memo_Outer_Loop:for(i=0;i<LS;i++){
//#pragma HLS UNROLL
		Write_Memo_Inner_Loop:for(j=0;j<BW-1;j++){
//#pragma HLS UNROLL
				memory_block[i][j]=memo_block[i][j];
			}
		}

	Write_Mem_Outer_Loop:for(i=0;i<LS;i++){
//#pragma HLS UNROLL
		Write_Mem_Inner_Loop:for(j=0;j<BL;j++){
//#pragma HLS UNROLL
				memory_block_dec[i][j] = memo_block_dec[i][j];
			}
		}
	Write_Passed_LL_Loop:for(i=0;i<LS;i++){
//#pragma HLS UNROLL
		passed_LL[i]=inner_passed_LL[i];
	}

}
