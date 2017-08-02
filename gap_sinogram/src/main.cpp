#include "gap_sino.h"
#include <assert.h>
#include <time.h>

int main(int argc, char* argv[])
{
	clock_t start, stop;
	double t = 0.;
	assert((start = clock()) != -1);

	/*
	* # of head 20 to 40 about 800 diameter & 60 undersampling radio
	* detector width : 4 mm, pitch on xr : 8 mm ( 8 mm/px )
	gap_sino(20, 4, 8, 19, 800, "20hn_60unders_800d_4dw_8xr_19dn_560FOV_LR(70).s");
	gap_sino(22, 4, 8, 17, 800, "22hn_60unders_800d_4dw_8xr_17dn_560FOV_LR(70).s");
	gap_sino(24, 4, 8, 16, 800, "24hn_60unders_800d_4dw_8xr_16dn_560FOV_LR(70).s");
	gap_sino(26, 4, 8, 15, 800, "26hn_60unders_800d_4dw_8xr_15dn_560FOV_LR(70).s");
	gap_sino(28, 4, 8, 13, 800, "28hn_60unders_800d_4dw_8xr_13dn_560FOV_LR(70).s");
	gap_sino(30, 4, 8, 13, 800, "30hn_60unders_800d_4dw_8xr_13dn_560FOV_LR(70).s");
	gap_sino(32, 4, 8, 12, 800, "32hn_60unders_800d_4dw_8xr_12dn_560FOV_LR(70).s");
	gap_sino(34, 4, 8, 11, 800, "34hn_60unders_800d_4dw_8xr_11dn_560FOV_LR(70).s");
	gap_sino(36, 4, 8, 10, 800, "36hn_60unders_800d_4dw_8xr_10dn_560FOV_LR(70).s");
	gap_sino(38, 4, 8, 10, 800, "38hn_60unders_800d_4dw_8xr_10dn_560FOV_LR(70).s");
	gap_sino(40, 4, 8, 9, 800, "40hn_60unders_800d_4dw_8xr_9dn_560FOV_LR(70).s");
	*/

	//gap_sino(20, 4, 2, 17, 800, "20hn_55unders_800d_4dw_2xr_9dn_564FOV_LR(282).s");
	//gap_sino(36, 4, 2, 10, 800, "20hn_55unders_800d_4dw_2xr_9dn_564FOV_LR(282).s");
	gap_sino(4, 4, 4, 2, 12, "samples.s");

	stop = clock();
	t = (double)(stop - start);

	printf("Run time : %f milli second\n", t);
	return 0;
}