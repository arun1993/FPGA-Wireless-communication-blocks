#include <stdio.h>
#include <math.h>
#include "ap_int.h"

///////////////////////////// Change These ////////////////////////////////////////
#define BW 8 // Block Width
#define PREC 11 // Precision
#define CHAN_PREC 5 // Precision
#define LOG2_LS 1 // List Size Width
#define TEST_NUM 1 // Test Number
#define CRC_EN 0 // CRC Enable
#define INF_BITS 232 // Number of Information Bits (Data Bits + CRC Bits)
///////////////////////////////////////////////////////////////////////////////
// Fixed Values
#define CRC_LENGTH 16 // CRC Length
#define DATA_BITS INF_BITS-CRC_LENGTH // Number of Data Bits (Information Bits - CRC Bits)
#define BL (1<<BW) // Block Length 2^(Block Width)
#define LS (1<<LOG2_LS) // List Size
#define MAX_LL_VAL (1<<PREC)-1 // Maximum LL Value, 2^(PRECISION)-1
// Signal Precisions
typedef ap_uint<4> UINT_LOG2_BW;
typedef ap_uint<1> UINT_1;
typedef ap_uint<2> UINT_2;
typedef ap_uint<PREC+1> UINT_PREC_P1;
typedef ap_uint<PREC> UINT_PREC;
typedef ap_uint<PREC-1> UINT_PREC_M1;
typedef ap_uint<CHAN_PREC> UINT_CHAN_PREC;

typedef ap_uint<BW+1> UINT_BW_P1;
typedef ap_uint<BW> UINT_BW;
typedef ap_uint<BW-1> UINT_BW_M1;
typedef ap_uint<LOG2_LS+1> UINT_LOG2_LS_P1;
typedef ap_uint<LOG2_LS> UINT_LOG2_LS;
// Top Module
void list_scd(UINT_CHAN_PREC ll0_in[BL], UINT_CHAN_PREC ll1_in[BL], UINT_1 dec_out[INF_BITS]);//, UINT_1 fi_bram[BL]
// Sub Modules
void crc(UINT_1 data_in[DATA_BITS], UINT_1 crc_o[CRC_LENGTH]);
void bitonic_sorter(UINT_PREC ll0_i[LS], UINT_PREC ll1_i[LS], UINT_LOG2_LS_P1 index_o[LS]);
void comparator(UINT_PREC in0_data[LS], UINT_LOG2_LS_P1 in0_index[LS], UINT_PREC in1_data[LS], UINT_LOG2_LS_P1 in1_index[LS], UINT_PREC max_data[LS], UINT_LOG2_LS_P1 max_index[LS], UINT_PREC min_data[LS], UINT_LOG2_LS_P1 min_index[LS]);
void sortAndForward(UINT_PREC ll0_i[LS], UINT_PREC ll1_i[LS], UINT_LOG2_LS memory_block[LS][BW-1], UINT_1 memory_block_dec[LS][BL], UINT_1 passed_LL[LS]);
void memory_transfer(UINT_LOG2_LS memory_block[LS][BW-1],UINT_LOG2_LS_P1 index_list[LS], UINT_1 passed_LL[LS]);
void memory_copy_decision(UINT_1 memory_block[LS][BL],UINT_LOG2_LS_P1 index_list[LS]);
void feedback_logic(UINT_1 enc_in[LS][2*BL-1], UINT_1 ll_dec_o[LS][BL-1], UINT_1 encoded_dec_o[LS][BL]);
void processing_elements(UINT_PREC ll0[LS][BL-1], UINT_PREC ll1[LS][BL-1], UINT_CHAN_PREC ll0_chan[BL], UINT_CHAN_PREC ll1_chan[BL], UINT_1 dec_in[LS][BL-1], UINT_LOG2_LS ptr_in[LS][BW-1], UINT_1 f_g_select[BW], UINT_1 enable[BW]);
