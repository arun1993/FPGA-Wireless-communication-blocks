#include <math.h>
#include <stdio.h>
#include "list_decoder.h"
void bitonic_sorter(UINT_PREC ll0_i[LS], UINT_PREC ll1_i[LS], UINT_LOG2_LS_P1 index_o[LS]){
#pragma HLS inline region
/*#pragma HLS ARRAY_RESHAPE variable=index_o complete dim=1
#pragma HLS ARRAY_RESHAPE variable=ll_o complete dim=1
#pragma HLS ARRAY_RESHAPE variable=ll1_i complete dim=1
#pragma HLS ARRAY_RESHAPE variable=ll0_i complete dim=1*/
//#pragma HLS PIPELINE
	int i, k, layer, layer_timer;
//	const int max_layer = (LOG2_LS+1)*(LOG2_LS+2)/2;

	UINT_PREC in0_data[LS];
#pragma HLS ARRAY_PARTITION variable=in0_data block factor=2 dim=1
	UINT_PREC in1_data[LS];
#pragma HLS ARRAY_PARTITION variable=in1_data block factor=2 dim=1
	UINT_PREC max_data[LS];
#pragma HLS ARRAY_PARTITION variable=max_data block factor=2 dim=1
	UINT_LOG2_LS_P1 in0_index[LS];
#pragma HLS ARRAY_PARTITION variable=in0_index block factor=2 dim=1
	UINT_LOG2_LS_P1 in1_index[LS];
#pragma HLS ARRAY_PARTITION variable=in1_index block factor=2 dim=1
	UINT_LOG2_LS_P1 max_index[LS];
#pragma HLS ARRAY_PARTITION variable=max_index block factor=2 dim=1
	UINT_LOG2_LS_P1 min_index[LS];
#pragma HLS ARRAY_PARTITION variable=min_index block factor=2 dim=1
	UINT_PREC min_data[LS];
#pragma HLS ARRAY_PARTITION variable=min_data block factor=2 dim=1

	layer_loop: for (layer=0; layer<LOG2_LS; layer++){
		layer_timer_loop: for (layer_timer=0; layer_timer<=layer; layer_timer++){
			//printf("\nlayer = %d -- layer_timer = %d\n ",layer,layer_timer);
			operational_loop: for (k=0; k<LS; k++){
				//printf("k=%d ",k);
//#pragma HLS UNROLL
				switch_layer_timer: switch (layer_timer){
				// Brown Block
				case 0:
					if (layer == 0){
						//read_in: for (k=0; k<LS; k++){
							in0_data[k]  = ll0_i[k];
							in1_data[k]  = ll1_i[k];
							in0_index[k] = 2*k;
							in1_index[k] = 2*k+1;
						//}
					}
					else{
						//brown_block: for (k=0; k<LS; k++){
							if (k % 2 == 0){
								in0_data[k]   = max_data[k - (k % (1<<(layer)))/2];
								in0_index[k] = max_index[k - (k % (1<<(layer)))/2];
								in1_data[k]   = min_data[k + (1<<layer)-1 -(3*(k % (1<<layer))/2)];
								in1_index[k] = min_index[k + (1<<layer)-1 -(3*(k % (1<<layer))/2)];
								//printf("%d ",k + (1<<layer)-1 -(3*(k % (1<<layer))/2));
							}
							else{
								in0_data[k]   = max_data[k + (1<<layer) - 2 - (3*((k-1) % (1<<layer))/2)];
								in0_index[k] = max_index[k + (1<<layer) - 2 - (3*((k-1) % (1<<layer))/2)];
								in1_data[k]   = min_data[k - ((k-1) % (1<<layer))/2 - 1];
								in1_index[k] = min_index[k - ((k-1) % (1<<layer))/2 - 1];
								//printf("%d ",k - ((k-1) % (1<<layer))/2 - 1);
							}
						//}
					}
					break;
				// After Brown Block
				case 1:
					//after_brown_block: for (k=0; k<LS; k++){
						if ((k % (1<<(layer-layer_timer+1))) < (1<<(layer-layer_timer))){
							in0_data[k]   = max_data[k];
							in0_index[k] = max_index[k];
							in1_data[k]   = max_data[k + (1<<(layer-layer_timer))];
							in1_index[k] = max_index[k + (1<<(layer-layer_timer))];
							//printf("%d ",k + (1<<(layer-layer_timer)));
						}
						else{
							in0_data[k]   = min_data[k + (1<<(layer-layer_timer)) - 1 - 2*(k % (1<<(layer-layer_timer+1))) + (1<<(layer-layer_timer+1))];
							in0_index[k] = min_index[k + (1<<(layer-layer_timer)) - 1 - 2*(k % (1<<(layer-layer_timer+1))) + (1<<(layer-layer_timer+1))];
							in1_data[k]   = min_data[k - 1 - 2*(k % (1<<(layer-layer_timer+1))) + (1<<(layer-layer_timer+1))];
							in1_index[k] = min_index[k - 1 - 2*(k % (1<<(layer-layer_timer+1))) + (1<<(layer-layer_timer+1))];
							//printf("%d ",k + (1<<(layer-layer_timer)) - 1 - 2*(k % (1<<(layer-layer_timer+1))) + (1<<(layer-layer_timer+1)));
							//printf("%d ",k - 1 - 2*(k % (1<<(layer-layer_timer+1))) + (1<<(layer-layer_timer+1)));
						}

					//}
					break;
				// Not After Brown Block
				default:
					//not_after_brown_block: for (k=0; k<LS; k++){
						if ((k % (1<<(layer-layer_timer+1))) < (1<<(layer-layer_timer))){
							in0_data[k]   = max_data[k];
							in0_index[k] = max_index[k];
							in1_data[k]   = max_data[k + (1<<(layer-layer_timer))];
							in1_index[k] = max_index[k + (1<<(layer-layer_timer))];
							//printf("%d ",k + (1<<(layer-layer_timer)));
						}
						else{
							in0_data[k]   = min_data[k - (1<<(layer-layer_timer))];
							in0_index[k] = min_index[k - (1<<(layer-layer_timer))];
							in1_data[k]   = min_data[k];
							in1_index[k] = min_index[k];
							//printf("%d ",k - (1<<(layer-layer_timer)));
						}
					//}
					break;
				} // end of switch loop
			} // end of operational loop
			comparator(in0_data, in0_index, in1_data, in1_index, max_data, max_index, min_data, min_index);
		} // end of layer timer loop
	} // end of layer loop
	// Call only brown block for last layer
	// LAYER : LOG2_LS    LAYER_TIMER: 0
	layer = LOG2_LS;
	last_layer_operation: for (k=0; k<LS; k++){
		// brown_block
		if (k % 2 == 0){
			in0_data[k]   = max_data[k - (k % (1<<(layer)))/2];
			in0_index[k] = max_index[k - (k % (1<<(layer)))/2];
			in1_data[k]   = min_data[k + (1<<layer)-1 -(3*(k % (1<<layer))/2)];
			in1_index[k] = min_index[k + (1<<layer)-1 -(3*(k % (1<<layer))/2)];
			//printf("%d ",k + (1<<layer)-1 -(3*(k % (1<<layer))/2));
		}
		else{
			in0_data[k]   = max_data[k + (1<<layer) - 2 - (3*((k-1) % (1<<layer))/2)];
			in0_index[k] = max_index[k + (1<<layer) - 2 - (3*((k-1) % (1<<layer))/2)];
			in1_data[k]   = min_data[k - ((k-1) % (1<<layer))/2 - 1];
			in1_index[k] = min_index[k - ((k-1) % (1<<layer))/2 - 1];
			//printf("%d ",k - ((k-1) % (1<<layer))/2 - 1);
		}
	}
	comparator(in0_data, in0_index, in1_data, in1_index, max_data, max_index, min_data, min_index);

	write_out: for (k=0; k<LS; k++){
//#pragma HLS UNROLL
//		ll_o[k]    = min_data[k];
		index_o[k] = min_index[k];
	}
}
