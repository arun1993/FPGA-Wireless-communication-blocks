#include <stdio.h>
#include <math.h>
#include "list_decoder.h"
int main()
{
	int i,k,w;
	int vld = 1;
	FILE *fid, *fid2, *fid3;
	UINT_1 dec_out[INF_BITS] = {0};
	//UINT_1 dec_out[N] = {0};
	UINT_CHAN_PREC ll0_in[BL];
	UINT_CHAN_PREC ll1_in[BL];
	UINT_1 golden_data[INF_BITS];
	UINT_1 fi_bram[BL];

	// Load Frozen Index Data from a File
	fid = fopen ("fi_bram.dat","r");
	for (i=0; i<BL; i++){
		fscanf (fid, "%d", &k);
		fi_bram[i] = k;
	}
	fclose(fid);
	// Load SCD Input-0 Data from a File
	fid = fopen ("list_decoder_in_ll0.dat","r");
	// Load SCD Input-1 Data from a File
	fid2 = fopen ("list_decoder_in_ll1.dat","r");
	// Load SCD Output Data from a File
	fid3 = fopen ("list_decoder_out.dat","r");

	printf("......................List SCD TEST IS STARTING......................\n");
	printf("Test Number: %d\nBlock Length: %d\nList Size: %d\nPrecision: %d\nINF BITS: %d\n",TEST_NUM, BL, LS, PREC, INF_BITS);
	for (w=0; w<TEST_NUM; w++){

		for (i=0; i<BL; i++){
			fscanf (fid, "%d", &k);
			ll0_in[i] = k;
			fscanf (fid2, "%d", &k);
			ll1_in[i] = k;
		}
		for (i=0; i<32; i++){
			fscanf (fid3, "%d", &k);
			golden_data[i] = k;
		}
//		if (w == TEST_NUM-1){
			list_scd(ll0_in, ll1_in, dec_out);//, fi_bram
			for (i=0; i<32; i++){
				printf("%d",(int) dec_out[i]);
				if (dec_out[i] != golden_data[i]){
					vld = 0;
				    break;
				}
			}
			if (vld == 0)
				break;
//		}
	}

	fclose(fid);
	fclose(fid2);
	fclose(fid3);
	//free(fid);
	//free(fid2);
	//free(fid3);

	if (vld == 1){
		fprintf(stdout, "\n*******************************************\n");
		fprintf(stdout, "PASS: The output matches the golden output!\n");
		fprintf(stdout, "*******************************************\n\n");
		return 0;
	}
	else{
		fprintf(stdout, "\n*******************************************\n");
		fprintf(stdout, "FAIL: Output DOES NOT match the golden output\n");
		printf("FAIL NUMBER: %d\n",w+1);
		printf("FAIL BIT: %d\n",i);
		fprintf(stdout, "*******************************************\n\n");
		return 1;
	}

//	return 0;

}
