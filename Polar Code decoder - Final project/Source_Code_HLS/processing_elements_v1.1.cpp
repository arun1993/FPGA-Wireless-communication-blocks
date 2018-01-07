#include <stdio.h>
#include <math.h>
#include "list_decoder.h"
void processing_elements(UINT_PREC ll0[LS][BL-1], UINT_PREC ll1[LS][BL-1], UINT_CHAN_PREC ll0_chan[BL], UINT_CHAN_PREC ll1_chan[BL], UINT_1 dec_in[LS][BL-1], UINT_LOG2_LS ptr_in[LS][BW-1], UINT_1 f_g_select[BW], UINT_1 enable[BW]){
#pragma HLS PIPELINE II = 143
/*#pragma HLS ARRAY_RESHAPE variable=enable complete dim=1
#pragma HLS ARRAY_RESHAPE variable=f_g_select complete dim=1
#pragma HLS ARRAY_RESHAPE variable=ptr_in complete	dim=1
#pragma HLS ARRAY_RESHAPE variable=ptr_in complete dim=2
#pragma HLS ARRAY_RESHAPE variable=dec_in complete dim=1
#pragma HLS ARRAY_RESHAPE variable=dec_in complete dim=2
#pragma HLS ARRAY_RESHAPE variable=ll1_chan complete dim=1
#pragma HLS ARRAY_RESHAPE variable=ll0_chan complete dim=1
#pragma HLS ARRAY_RESHAPE variable=ll1 complete dim=1
#pragma HLS ARRAY_RESHAPE variable=ll1 complete dim=2
#pragma HLS ARRAY_RESHAPE variable=ll0 complete dim=1
#pragma HLS ARRAY_RESHAPE variable=ll0 complete dim=2
*/

	int i,w, list;
//	int test,test1,test2,test3,test4;
	UINT_LOG2_LS pointer_select[LS][BL/2-1];
	UINT_1 pe_f_g_select[BL/2-1];
	UINT_1 pe_enable[BL/2-1];
	ptr_list: for(list=0; list<LS; list++){
		ptr_select: for(i=0; i<BW-1; i++){
			load_pointer_select: for(w=0; w<(1<<i); w++){
				pointer_select[list][(1<<i) -1 +w] = ptr_in[list][i];
			}
		}
	}
	fg_select1: for(i=0; i<BW-1; i++){
		fg_select2: for(w=0; w<(1<<i); w++){
			pe_f_g_select[(1<<i) -1 +w] = f_g_select[i];
		}
	}
	assign_enable1: for(i=0; i<BW-1; i++){
		assign_enable2: for(w=0; w<(1<<i); w++){
			pe_enable[(1<<i) -1 +w] = enable[i];
		}
	}
	pe_loop1: for(i=0; i<(BL/2)-1; i++){
		if (pe_enable[i] == 1){
			list_loop1: for(list=0; list<LS; list++){
				if (pe_f_g_select[i] == 0){
					if ((ll0[list][2*i+1]+ll0[list][2*i+2]) > (ll1[list][2*i+1]+ll1[list][2*i+2])){
						ll0[list][i] = (ll1[list][2*i+1]+ll1[list][2*i+2]);
					}
					else{
						ll0[list][i] = (ll0[list][2*i+1]+ll0[list][2*i+2]);
					}

					if ((ll0[list][2*i+1]+ll1[list][2*i+2]) > (ll1[list][2*i+1]+ll0[list][2*i+2])){
						ll1[list][i] = (ll1[list][2*i+1]+ll0[list][2*i+2]);
					}
					else{
						ll1[list][i] = (ll0[list][2*i+1]+ll1[list][2*i+2]);
					}
				}
				else{
					if (dec_in[list][i] == 0){
						ll0[list][i] = ll0[pointer_select[list][i]][2*i+1] + ll0[pointer_select[list][i]][2*i+2];
						ll1[list][i] = ll1[pointer_select[list][i]][2*i+1] + ll1[pointer_select[list][i]][2*i+2];
					}
					else{
						ll0[list][i] = ll1[pointer_select[list][i]][2*i+1] + ll0[pointer_select[list][i]][2*i+2];
						ll1[list][i] = ll0[pointer_select[list][i]][2*i+1] + ll1[pointer_select[list][i]][2*i+2];
					}
				}
//				test = ll0[list][i];
//				test1 = ll1[list][i];
//				test2 = dec_in[list][i];
//				test3 = pe_f_g_select[i];
//				test4 = pointer_select[list][i];
//				printf("list:%d=> %d %d dec:%d f_g:%d ptr:%d --",list,test,test1,test2,test3,test4);
			}
		}
	}

	pe_loop_chan: for(i=0; i<BL/2; i++){
		if (enable[BW-1] == 1){
			list_loop_chan: for(list=0; list<LS; list++){
				if (f_g_select[BW-1] == 0){
					if ((ll0_chan[2*i]+ll0_chan[2*i+1]) > (ll1_chan[2*i]+ll1_chan[2*i+1])){
						ll0[list][(BL/2)-1+i] = (ll1_chan[2*i]+ll1_chan[2*i+1]);
					}
					else{
						ll0[list][(BL/2)-1+i] = (ll0_chan[2*i]+ll0_chan[2*i+1]);
					}

					if ((ll0_chan[2*i]+ll1_chan[2*i+1]) > (ll1_chan[2*i]+ll0_chan[2*i+1])){
						ll1[list][(BL/2)-1+i] = (ll1_chan[2*i]+ll0_chan[2*i+1]);
					}
					else{
						ll1[list][(BL/2)-1+i] = (ll0_chan[2*i]+ll1_chan[2*i+1]);
					}
				}
				else{
					if (dec_in[list][(BL/2)-1+i] == 0){
						ll0[list][(BL/2)-1+i] = ll0_chan[2*i] + ll0_chan[2*i+1];
						ll1[list][(BL/2)-1+i] = ll1_chan[2*i] + ll1_chan[2*i+1];
					}
					else{
						ll0[list][(BL/2)-1+i] = ll1_chan[2*i] + ll0_chan[2*i+1];
						ll1[list][(BL/2)-1+i] = ll0_chan[2*i] + ll1_chan[2*i+1];
					}
				}
//				test = ll0[list][(BL/2)-1+i];
//				test1 = ll1[list][(BL/2)-1+i];
//				test2= dec_in[list][(BL/2)-1+i];
//				printf("list:%d=> %d %d dec:%d -- ",list,test,test1,test2);
			}
		}
	}
//	printf("\n\n");
}
