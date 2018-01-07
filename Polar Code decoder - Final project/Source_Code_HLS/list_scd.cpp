#include <math.h>
#include <stdio.h>
#include "list_decoder.h"

//#define min(a,b) ((a) > (b) ? (b) : (a))



void list_scd(UINT_CHAN_PREC ll0_in[BL], UINT_CHAN_PREC ll1_in[BL], UINT_1 dec_out[INF_BITS]){
//, UINT_1 fi_bram[BL]
//#pragma HLS PIPELINE II=300
//#pragma HLS ARRAY_RESHAPE variable=ll1_in complete dim=1
//#pragma HLS ARRAY_RESHAPE variable=ll0_in complete dim=1



//	const int fi_bram[BL] = {1, 1, 1, 0, 1, 0, 0, 0};
	const int fi_bram[BL] = {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0};
	//const int fi_bram[BL] = {1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};




	int k,i,w,list;
//	int test,test1;
	UINT_1 pe_f_g_select[BW];
//#pragma HLS ARRAY_PARTITION variable=pe_f_g_select complete dim=1
	UINT_BW crc_dummy;
	UINT_1 dec_mem[LS][BL];
//#pragma HLS ARRAY_PARTITION variable=dec_mem complete dim=1
//#pragma HLS ARRAY_PARTITION variable=dec_mem complete dim=2
	UINT_1 muxed_dec_mem[LS][2*BL-1];
//#pragma HLS ARRAY_RESHAPE variable=muxed_dec_mem complete dim=1
//#pragma HLS ARRAY_RESHAPE variable=muxed_dec_mem complete dim=2
	UINT_1 pe_dec_in[LS][BL-1];
//#pragma HLS ARRAY_PARTITION variable=pe_dec_in complete dim=1
//#pragma HLS ARRAY_PARTITION variable=pe_dec_in complete dim=2
	UINT_LOG2_BW layer_init[BL];
	UINT_LOG2_BW layer_init_dummy;
	UINT_1 frozen_addr_rd_dummy;
	UINT_CHAN_PREC ll0_chan[BL];
//#pragma HLS ARRAY_PARTITION variable=ll0_chan complete dim=1
	UINT_CHAN_PREC ll1_chan[BL];
//#pragma HLS ARRAY_PARTITION variable=ll1_chan complete dim=1
	UINT_PREC ll0[LS][BL-1];
//#pragma HLS ARRAY_PARTITION variable=ll0 complete dim=1
//#pragma HLS ARRAY_PARTITION variable=ll0 complete dim=2
	UINT_PREC ll1[LS][BL-1];
//#pragma HLS ARRAY_PARTITION variable=ll1 complete dim=1
//#pragma HLS ARRAY_PARTITION variable=ll1 complete dim=2
	UINT_1 pe_enable[BW];
//#pragma HLS ARRAY_PARTITION variable=pe_enable complete dim=1
	UINT_1 systematic_encoded_dec_o[LS][BL];
//#pragma HLS ARRAY_RESHAPE variable=systematic_encoded_dec_o complete dim=1
//#pragma HLS ARRAY_RESHAPE variable=systematic_encoded_dec_o complete dim=2

	// Sorter Signals
	UINT_PREC sort_in_ll0[LS];
//#pragma HLS ARRAY_RESHAPE variable=sort_in_ll0 complete dim=1
	UINT_PREC sort_in_ll1[LS];
//#pragma HLS ARRAY_RESHAPE variable=sort_in_ll1 complete dim=1
	UINT_LOG2_LS_P1 pr_list_size = 1;
	UINT_LOG2_LS ll_pointer[LS][BW-1];
//#pragma HLS ARRAY_PARTITION variable=ll_pointer complete dim=1
//#pragma HLS ARRAY_PARTITION variable=ll_pointer complete dim=2
	// CRC Signals
	UINT_1 crc_false_flag;
	UINT_1 crc_true_flag;
	UINT_1 data_bits[INF_BITS-CRC_LENGTH];
	UINT_1 crc_bits[CRC_LENGTH];
	UINT_1 crc_o[CRC_LENGTH];
	UINT_1 binary_counter[BL][BW];
	UINT_BW dec_order[BL];
	UINT_1 sort_o_decisions[LS];
//#pragma HLS ARRAY_RESHAPE variable=sort_o_decisions complete dim=1

	UINT_BW dec_mux_addr_init[BW];
//#pragma HLS ARRAY_RESHAPE variable=dec_mux_addr_init complete dim=1
//	UINT_BW dec_mux_addr_bram[BL][BW];
//#pragma HLS ARRAY_RESHAPE variable=dec_mux_addr_bram complete dim=2
//	UINT_BW mux_addr_dummy[BW];

/////// BLOCK RAMS ////////////////////////////////////
	bin_cnt0: for(k=0; k<BL; k++){
		bin_cnt1: for(i=0; i<BW; i++){
			if (k % (1<<(i+1)) < 1<<(i))
				binary_counter[k][i] = 0;
			else
				binary_counter[k][i] = 1;
		}
	}


	dec_order_lp0: for (k=0; k<BL; k++){
		w = 0;
		dec_order_lp1:  for (i=0; i<BW; i++){
			w += (binary_counter[k][i])*(1<<(BW-i-1));
		}
		dec_order[k] = w;
	}

	layer_init[0] = BW-1;
	p2_bjmp_lp0: for (k=0; k<BL-1; k++){
		p2_bjmp_lp1: for (i=0; i<BW; i++){
			if ((k % (1<<(i+1))) == (1<<i)-1){
				break;}
		}
		layer_init[k+1] = i;
//		test = layer_init[k+1];
//		printf("%d ",test);
	}
	layer_init_dummy = layer_init[0];


//	mux_init_bram0: for(k=0; k<BL; k++){
//		mux_init_bram00: for(i=0; i<BW; i++){
//			if (k == 0){
//				dec_mux_addr_bram[k][i] = 0; // initialize mux addr
//				mux_addr_dummy[i] = 0;
//			}
//			else{
//				if((k % (1<<(i+1))) == 0){
//					dec_mux_addr_bram[k][i] = mux_addr_dummy[i] + (1<<(i+1));
//					mux_addr_dummy[i] = mux_addr_dummy[i] + (1<<(i+1));
//				}
//				else{
//					dec_mux_addr_bram[k][i] = mux_addr_dummy[i];
//				}
//			}
//		}
//	}

/////////////////////////////////////////////////////////

	read_in_0: for(k=0; k<BL; k++){
//#pragma HLS UNROLL
		//read_in_00: for(list=0; list<LS; list++){
//		ll0[0][BL-1+k] = ll0_in[k];
		ll0_chan[k] = ll0_in[k];
		ll1_chan[k] = ll1_in[k];
//		ll1[0][BL-1+k] = ll1_in[k];
		//}
	}

	initialize_dec_mem0: for(list=0; list<LS; list++){
//#pragma HLS UNROLL
		initialize_dec_mem1: for(i=0; i<BL; i++){
//#pragma HLS UNROLL
			dec_mem[list][i] = 0;
		}
	}

//	printf("\nllr0_chan: ");
//	for(k=0; k<BL; k++){
//		test= ll0_chan[k];
//		printf("%d ",test);
//	}
//	printf("\nllr1_chan: ");
//	for(k=0; k<BL; k++){
//		test= ll1_chan[k];
//		printf("%d ",test);
//	}

	initialize_f_g_select: for(i=0; i<BW; i++){
//#pragma HLS UNROLL
				pe_f_g_select[i] = 0;
		}
	initialize_enable: for(i=0; i<BW; i++){
//#pragma HLS UNROLL
		pe_enable[i] = 1;
	}

	main_loop:for (k=0; k<BL; k++){
//	printf("\n***** k = %d *****\n",k);




//	   printf("\n------ pe dec in -----------\n");
//	   for (list=0; list<LS; list++){
//		   for(i=0; i<BL-1; i++){
//			   test = pe_dec_in[list][i];
//			   printf("%d ",test);
//		   }
//		   printf("\n");
//	   }


		pelayer_loop: for(i=0; i<=layer_init_dummy; i++){
			processing_elements(ll0, ll1, ll0_chan, ll1_chan, pe_dec_in, ll_pointer,  pe_f_g_select, pe_enable);
		}

		frozen_addr_rd_dummy = fi_bram[dec_order[k]];

		read_f_g_select: for(i=0; i<BW; i++){
//#pragma HLS UNROLL
//			p2_pe_f_g_select[i] = binary_counter[k][i];
			if ((k+1) % (1<<(i+1)) < 1<<(i)){
				pe_f_g_select[i] = 0;
			}
			else{
				pe_f_g_select[i] = 1;
			}
		}

	   assign_pe_en: for(i=0; i<BW; i++){
//#pragma HLS UNROLL
			enable_update: for (w=0; w<BW; w++){
//#pragma HLS UNROLL
				if (((k) % (1<<(w+1))) == (1<<w)-1){
					break;}
			}
			if (i <= w){
				pe_enable[i] = 1;
			}
			else{
				pe_enable[i] = 0;
			}
		}

//

//		printf("\nll0: ");
//		for(list=0; list<LS; list++){
//			test = ll0[list][0];
//			printf("%d ",test);
//		}
//		printf("\nll1: ");
//		for(list=0; list<LS; list++){
//			test = ll1[list][0];
//			printf("%d ",test);
//		}
//		printf("\n--Pointer!--\n");
//		for(list=0; list<pr_list_size; list++){
//			for(i=0; i<BW; i++){
//				test = ll_pointer[list][i];
//				printf("%d ",test);
//			}
//			printf("\n");
//		}
		// Update Pointers

		ptr_upp1: for(list=0; list<LS; list++){ // processing element loopuna girebilir list<pr_list_size
//#pragma HLS UNROLL
			ptr_upp2: for(i=0; i<BW-1; i++){
//#pragma HLS UNROLL
				if (i<=layer_init_dummy){
					ll_pointer[list][i] = list;
				}
			}
		}
		layer_init_dummy = layer_init[k+1];


		// Free Decision
		if (frozen_addr_rd_dummy == 0){
//				printf("\n !! Free !!\n");
			// Survival and sorting algorithm
			if (pr_list_size == LS){ // maximum list size is achieved+
//					printf(" !! Survival !!");
				// Sorting the LL values

				sorter_initialize: for(list = 0; list<LS; list++){
//#pragma HLS UNROLL
					sort_in_ll0[list] = ll0[list][0];
					sort_in_ll1[list] = ll1[list][0];
				}
				//////////////////////// Sort and Forward Function is used ///////////////////////////
//				printf("\n--Pointer_before_copy!--\n");
//				for(list=0; list<LS; list++){
//					for(i=0; i<BW-1; i++){
//						test = ll_pointer[list][i];
//						printf("%d ",test);
//					}
//					printf("\n");
//				}
//				printf("\n--Decision_before_copy!--\n");
//				for(list=0; list<LS; list++){
//					for(i=0; i<BL; i++){
//						test = dec_mem[list][i];
//						printf("%d ",test);
//					}
//					printf("\n");
//				}
				//////////////////////////////////////////////////////////////////////
				sortAndForward(sort_in_ll0, sort_in_ll1, ll_pointer, dec_mem, sort_o_decisions);
				save_sort_out_decisions: for(list = 0; list<LS; list++){
//#pragma HLS UNROLL
					dec_mem[list][k] = sort_o_decisions[list];
				}
//				printf("\n--Decision_after_copy!--\n");
//				for(list=0; list<LS; list++){
//					for(i=0; i<BL; i++){
//						test = dec_mem[list][i];
//						printf("%d ",test);
//					}
//					printf("\n");
//				}
//				printf("\n--Pointer_after_copy!--\n");
//				for(list=0; list<LS; list++){
//					for(i=0; i<BW-1; i++){
//						test = ll_pointer[list][i];
//						printf("%d ",test);
//					}
//					printf("\n");
//				}
				///////////////////////////////////////////////////////////////////////////////////
			}

			// Branching for new lists
			else{
//					printf(" !! Create New Branch !!");
				branching_list: for(list = 0; list<LS/2; list++){
//#pragma HLS UNROLL
					if (list < pr_list_size){
						dec_mem[list][k] = 0; // make decision "0" for the first branches
						dec_mem[list+pr_list_size][k] = 1;	// make decision "1" for the second branches
						branch_copy_pointers: for(i=0; i<BW-1; i++){
//#pragma HLS UNROLL
							ll_pointer[list+pr_list_size][i] = ll_pointer[list][i]; // copy LL pointer ram
						}
						copy_decision_mem: for (i=0; i<k; i++){
//#pragma HLS UNROLL
							dec_mem[list+pr_list_size][i] = dec_mem[list][i];
						}
					}
				}
				pr_list_size = pr_list_size + pr_list_size; // duplicate the present list size
			}
//				for(list = 0; list<pr_list_size; list++){
//					for (i=0;i<n;i++){
//						printf("\nAddr%d LR_RAM= %d DEC_RAM= %d ",list*n+i,ptr_ll[list][i],ptr_dec[list][i]);
//					}
//				}
		}
		// Frozen Decision
		else{
//				printf("\n !! Frozen !!");
			frozen_list_loop:for(list = 0; list<LS; list++){//list<pr_list_size;
//#pragma HLS UNROLL
				dec_mem[list][k] = 0;
			}

		}
		// Feedback Part
		dec_mux_update: for(i=0; i<BW; i++){
//#pragma HLS UNROLL
//			dec_mux_addr_init[i] = dec_mux_addr_bram[k][i];
			if (k == 0){
				dec_mux_addr_init[i] = 0; // initialize mux addr
			}
			else{
				if((k % (1<<(i+1))) == 0){
					dec_mux_addr_init[i] = dec_mux_addr_init[i] + (1<<(i+1));
				}
			}
		}

		list_loop: for(list=0; list<LS; list++){
//#pragma HLS UNROLL
			mux0_loop: for(w=0; w<BW+1; w++){
//#pragma HLS UNROLL
				// modlu da yap�labilir !
				mux1_loop: for(i=0; i<(1<<w); i++){
//#pragma HLS UNROLL
					if (w == BW){
						muxed_dec_mem[list][(1<<w)-1 +i] = dec_mem[list][i];
					}
					else{
						muxed_dec_mem[list][(1<<w)-1 +i] = dec_mem[list][dec_mux_addr_init[w] + i];
					}
				}
			}
		}

		feedback_logic(muxed_dec_mem, pe_dec_in, systematic_encoded_dec_o);
	}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////


//	printf("\nOUTPUT DECISIONS: ");
	if(CRC_EN == 0){
		crc_dummy = 0;
		write_out_no_crc:for(k=0; k<BL; k++){
//#pragma HLS UNROLL
			if (fi_bram[k] == 0){ // free index
				dec_out[crc_dummy] = systematic_encoded_dec_o[0][k];//dec_save[0][BL-1+k];
				crc_dummy = crc_dummy + 1;
//				test = systematic_encoded_dec_o[0][k];
//				printf("%d ",test);
			}
		}
	}
	else{
		// read LL Values
		crc_true_flag = 0;
		crc_list: for(list = 0; list<LS; list++){
			crc_dummy = 0;
			crc_read: for(k=0; k<BL; k++){
				if (fi_bram[k] == 0){ // free index
					if (crc_dummy < DATA_BITS){
						data_bits[crc_dummy] = systematic_encoded_dec_o[list][k];//dec_save[list][BL-1+k];
					}
					else{
						crc_bits[crc_dummy-(DATA_BITS)] = systematic_encoded_dec_o[list][k];//dec_save[list][BL-1+k];
					}
					crc_dummy = crc_dummy + 1;
				}
			}
			// CRC
			crc(data_bits, crc_o);
			crc_false_flag = 0;
			crc_compare: for(k=0; k<CRC_LENGTH; k++){
				if(crc_bits[k] != crc_o[k]){
					crc_false_flag = 1;
					break;
				}
			}
			if (crc_false_flag == 0){
				crc_true_flag = 1;
				//printf("crc_satisfied_list: %d", list);
				break;
			}
		}
		// CRC is not satisfied for all lists
		if(crc_true_flag == 0){
			//printf("crc_is_not_satisfied: %d\n", list);
			crc_dummy = 0;
			write_out_false_crc:for(k=0; k<BL; k++){
				if (fi_bram[k] == 0){ // free index
					dec_out[crc_dummy] = systematic_encoded_dec_o[0][k];//dec_save[0][BL-1+k];
					//printf("%d ", dec_save[0][N-1+k]);
					crc_dummy = crc_dummy + 1;
				}
			}
		}
		// CRC is satisfied for at least one list
		else{
			crc_dummy = 0;
			//printf("%d\n",list);
			write_out_true_crc:for(k=0; k<BL; k++){
				if (fi_bram[k] == 0){ // free index
					dec_out[crc_dummy] = systematic_encoded_dec_o[list][k];//dec_save[list][BL-1+k];
					crc_dummy = crc_dummy + 1;
				}
			}
		}
	}

//			write_out:for(k=0; k<N; k++){
//				dec_out[k] = dec_save[0][N-1+k];
//				}

//	printf("\nOutput Decisions: ");
//	for(k=0; k<N; k++){
//		printf("%d ",dec_save[0][N-1+k]);
//	}
}



