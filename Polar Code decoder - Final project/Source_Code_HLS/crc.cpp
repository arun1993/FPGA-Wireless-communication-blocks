//#include <math.h>
//#include <stdio.h>
//#include "list_decoder.h"
//void crc(UINT_1 data_in[DATA_BITS], UINT_1 crc_o[CRC_LENGTH]){
////#pragma HLS ARRAY_RESHAPE variable=crc_o complete dim=1
////#pragma HLS ARRAY_RESHAPE variable=data_in complete dim=1
//
//	int j,a;
//	UINT_1 crc_reg[CRC_LENGTH];
////#pragma HLS ARRAY_PARTITION variable=crc_reg complete dim=1
//	UINT_1 crc_reg2[CRC_LENGTH];
////#pragma HLS ARRAY_PARTITION variable=crc_reg2 complete dim=1
//	// Initialize CRC Registers
//    read_in: for (j=0; j<CRC_LENGTH; j++){
//        crc_reg[j] = data_in[DATA_BITS-CRC_LENGTH+j];
//    }
//    CRC_loop0: for (a=0; a<DATA_BITS; a++){
////#pragma HLS PIPELINE
//    	CRC_loop00: for (j=0; j<CRC_LENGTH; j++){
//            if (j == 0 ){// d16 + d15 + d2 +1
//                if (a > (DATA_BITS-CRC_LENGTH-1))
//                    crc_reg2[0] = crc_reg[15];
//                else
//                    crc_reg2[0] = ((crc_reg[15]+data_in[DATA_BITS-CRC_LENGTH-1-a]) % 2);
//
//            }
//            else if (j == 2){
//                crc_reg2[2] = ((crc_reg[15]+crc_reg[1]) % 2);
//            }
//            else if (j == 15){
//            	crc_reg2[15] = ((crc_reg[15]+ crc_reg[14]) % 2);
//            }
//            else{
//              crc_reg2[j] = crc_reg[j-1];
//            }
//        }
//        for (j=0; j<CRC_LENGTH; j++)
//            crc_reg[j] = crc_reg2[j];
//    }
//	write_out: for (j=0; j<CRC_LENGTH; j++){
//		crc_o[j] = crc_reg[j];
//	}
//}


#include <math.h>
#include <stdio.h>
#include "list_decoder.h"

void crc(UINT_1 input_codeword[DATA_BITS],UINT_1 CRC_result[CRC_LENGTH])
{
#pragma HLS PIPELINE
#pragma HLS ARRAY_RESHAPE variable=CRC_result complete dim=1
#pragma HLS ARRAY_RESHAPE variable=input_codeword complete dim=1
    int i,j,k;
    UINT_1 input_reader[INF_BITS];
#pragma HLS ARRAY_RESHAPE variable=input_reader complete dim=1
    UINT_1 register_array[CRC_LENGTH];
#pragma HLS ARRAY_RESHAPE variable=register_array complete dim=1
    Initialize_Register:for(i=0;i<CRC_LENGTH;i++){
//#pragma HLS UNROLL
        register_array[i]=0;
    }
    UINT_1 divisor_array[CRC_LENGTH+1];
//#pragma HLS ARRAY_RESHAPE variable=divisor_array complete dim=1
    divisor_array[0]=1;
    divisor_array[1]=0;
    divisor_array[2]=0;
    divisor_array[3]=0;
    divisor_array[4]=0;
    divisor_array[5]=1;
    divisor_array[6]=0;
    divisor_array[7]=0;
    divisor_array[8]=0;
    divisor_array[9]=0;
    divisor_array[10]=0;
    divisor_array[11]=0;
    divisor_array[12]=1;
    divisor_array[13]=0;
    divisor_array[14]=0;
    divisor_array[15]=0;
    divisor_array[16]=1;

    int pop_value=0;
    //printf("Input:\n");
    Read_Codeword:for(i=0;i<DATA_BITS;i++){
//#pragma HLS UNROLL
        input_reader[i]=input_codeword[i];
        //printf("%d ",int(input_codeword[i]));
    }

    Append_zero:for(i=DATA_BITS;i<INF_BITS;i++){
//#pragma HLS UNROLL
    	input_reader[i]=0;
    }

    Push_Input:for(i=0;i<INF_BITS;i++){
//#pragma HLS UNROLL
        pop_value=register_array[CRC_LENGTH-1];
        Slide_Register:for(j=CRC_LENGTH-1;j>0;j--){
//#pragma HLS UNROLL
            register_array[j]=register_array[j-1];
        }
        register_array[0]=input_reader[i];
        if(pop_value==1){
            XOR_Operation:for(k=0;k<CRC_LENGTH;k++){
//#pragma HLS UNROLL
                register_array[k]=(register_array[k]+divisor_array[k])%2;
            }
        }
    }
    //printf("\n");
    Output_Check:for(i=0;i<CRC_LENGTH;i++){
//#pragma HLS UNROLL
    	CRC_result[i]=register_array[CRC_LENGTH-1-i];
    	//printf("%d ",int(register_array[CRC_LENGTH-1-i]));
    }
    //printf("\n");
}

