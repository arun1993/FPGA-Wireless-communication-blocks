#include <math.h>
#include "list_decoder.h"

void feedback_logic(UINT_1 enc_in[LS][2*BL-1], UINT_1 ll_dec_o[LS][BL-1], UINT_1 encoded_dec_o[LS][BL]) {
#pragma HLS PIPELINE
//#pragma HLS ARRAY_RESHAPE variable=encoded_dec_o complete dim=1
//#pragma HLS ARRAY_RESHAPE variable=encoded_dec_o complete dim=2
//#pragma HLS ARRAY_RESHAPE variable=ll_dec_o complete dim=1
//#pragma HLS ARRAY_RESHAPE variable=ll_dec_o complete dim=2
//#pragma HLS ARRAY_RESHAPE variable=enc_in complete dim=1
//#pragma HLS ARRAY_RESHAPE variable=enc_in complete dim=2
	int i,l,k,w,list;
	UINT_BW_M1 inc_when;
	UINT_BW point, loc;
	UINT_1 save[LS][2*BL-1];
#pragma HLS ARRAY_RESHAPE variable=save complete dim=1
	UINT_1 save_p[LS][2*BL-1];
#pragma HLS ARRAY_RESHAPE variable=save_p complete dim=1 // save_permutated
	UINT_BW_P1 perm_index_ram[2*BL-1];
#pragma HLS ARRAY_RESHAPE variable=perm_index_ram complete dim=1
	UINT_1 binary_counter[2*BL][BW+1];
#pragma HLS ARRAY_RESHAPE variable=binary_counter complete dim=2

	// ---------------------- Binary Counter -----------------
	bin_cnt0: for(k=0; k<2*BL; k++){
		bin_cnt1: for(i=0; i<BW+1; i++){
			if (k % (1<<(i+1)) < 1<<(i))
				binary_counter[k][i] = 0;
			else
				binary_counter[k][i] = 1;
		}
	}

	// ---------------------- Decision Order = Permutation_order (bit_reversed) ------------------
	//  perm_index_ram[0] = 0;
	//	perm_index_ram[1] = 1;
	//	perm_index_ram[2] = 2;
	//	perm_index_ram[3] = 3;
	//	perm_index_ram[4] = 5; // gibi
	//	perm_index_ram[5] = 4;
	//	perm_index_ram[6] = 6;
	//printf("\nPermutation Index Loop Starting\n");
	perm_index_ram[0] = 0;
	dec_order_lp0:for(l=1; l<BW+1; l++){
		dec_order_lp1: for(k=0; k<(1<<l); k++){
			w = 0;
			dec_order_lp2: for(i=0; i<l; i++){
				w += (binary_counter[k][i])*(1<<(l-i-1));
			}
			perm_index_ram[(1<<l)-1+k] = (1<<l)-1+w;
		}
	}
		// give encoder inputs
	list_loop: for(list=0; list<LS; list++){
		mux0_loop: for(k=0; k<2*BL-1; k++){
			save[list][k] = enc_in[list][k];
		}
		encoder_loop: for(k=1; k<BW+1; k++){ // Number of Encoders
			layer_loop: for(l=0; l<k; l++) {
				point = 0;
				loc = (1 << l);
				inc_when = (1 << l) -1;
				xor_loop: for(i=0; i<((1<<k)/2); i++) {
					save[list][(1<<k)-1+point] = (save[list][(1<<k)-1+point] + save[list][(1<<k)-1+point+loc]) % 2;
					if (inc_when == 0) {
						point = point + loc + 1;
						inc_when = (1 << l) -1;
					}
					else{
						point = point + 1;
						inc_when = inc_when - 1;
					}
				}
			}
		}

		permutation_loop: for(i=0; i<2*BL-1; i++){
			save_p[list][i] = save[list][perm_index_ram[i]];
		}
		save_ll_dec: for(i=0; i<BL-1; i++){
			ll_dec_o[list][i] = save_p[list][i];
		}
		save_encoded_dec: for(i=0; i<BL; i++){
			encoded_dec_o[list][i] = save_p[list][BL-1 + i];
		}
	}
}
