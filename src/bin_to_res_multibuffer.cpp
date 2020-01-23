/*
Get 16 bins in
Get seq. number in

Have rID2bin mapping

Procedure:
Get bin addresses for RIDs via LUT (2048 addr. 12bit values (4096 bins) = 24kbits)
8 addresses, each repeated at most 2 times.

Fetch last cycles bin values via the addresses
8 read ports
Write 16 bins

Cache is 4096 * IQ ~ 131kbits

combine the 8 IQs read with their rIDs and output
 */

#include "bin_to_res_buffer.hpp"


//Assume natural order for now
void bin_to_res_buff_multibuffer(opfb_stream_t &i_stream, opfb_stream_t &q_stream,
		resIQ_stream_t &out0, resIQ_stream_t &out1, resIQ_stream_t &out2, resIQ_stream_t &out3,
		resIQ_stream_t &out4, resIQ_stream_t &out5, resIQ_stream_t &out6, resIQ_stream_t &out7,
		binndx_t rid_to_bin[N_CYCLES][N_RES_PER_CLOCK]) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE axis port=i_stream
#pragma HLS INTERFACE axis port=q_stream
#pragma HLS INTERFACE axis port=out0
#pragma HLS INTERFACE axis port=out1
#pragma HLS INTERFACE axis port=out2
#pragma HLS INTERFACE axis port=out3
#pragma HLS INTERFACE axis port=out4
#pragma HLS INTERFACE axis port=out5
#pragma HLS INTERFACE axis port=out6
#pragma HLS INTERFACE axis port=out7

#pragma HLS INTERFACE s_axilite port=rid_to_bin
#pragma HLS ARRAY_RESHAPE variable=rid_to_bin complete dim=2
#pragma HLS RESOURCE variable=rid_to_bin core=RAM_2P_BRAM

//#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE s_axilite port=return

	static resid_t id_ndx=0;  //This is the rID of the rIDout[0], increments by N_RES_PER_CLOCK

	// Working variables
	pfb_output_t ivals, qvals;
	cycleid_t cycle_id = 0;

	// Cache
	static iq_t bin_iq_cache0[N_CYCLES][N_PFB_BINS_PER_CLK];  //IQ values from the past cycle
	static iq_t bin_iq_cache1[N_CYCLES][N_PFB_BINS_PER_CLK];  //IQ values from the past cycle
	static iq_t bin_iq_cache2[N_CYCLES][N_PFB_BINS_PER_CLK];  //IQ values from the past cycle
	static iq_t bin_iq_cache3[N_CYCLES][N_PFB_BINS_PER_CLK];  //IQ values from the past cycle
	static iq_t bin_iq_cache4[N_CYCLES][N_PFB_BINS_PER_CLK];  //IQ values from the past cycle
	static iq_t bin_iq_cache5[N_CYCLES][N_PFB_BINS_PER_CLK];  //IQ values from the past cycle
	static iq_t bin_iq_cache6[N_CYCLES][N_PFB_BINS_PER_CLK];  //IQ values from the past cycle
	static iq_t bin_iq_cache7[N_CYCLES][N_PFB_BINS_PER_CLK];  //IQ values from the past cycle
//Must support 8 reads anywhere and one write of values
#pragma HLS DATA_PACK variable=bin_iq_cache0
#pragma HLS DATA_PACK variable=bin_iq_cache1
#pragma HLS DATA_PACK variable=bin_iq_cache2
#pragma HLS DATA_PACK variable=bin_iq_cache3
#pragma HLS DATA_PACK variable=bin_iq_cache4
#pragma HLS DATA_PACK variable=bin_iq_cache5
#pragma HLS DATA_PACK variable=bin_iq_cache6
#pragma HLS DATA_PACK variable=bin_iq_cache7
#pragma HLS DEPENDENCE variable=bin_iq_cache0 false
#pragma HLS DEPENDENCE variable=bin_iq_cache1 false
#pragma HLS DEPENDENCE variable=bin_iq_cache2 false
#pragma HLS DEPENDENCE variable=bin_iq_cache3 false
#pragma HLS DEPENDENCE variable=bin_iq_cache4 false
#pragma HLS DEPENDENCE variable=bin_iq_cache5 false
#pragma HLS DEPENDENCE variable=bin_iq_cache6 false
#pragma HLS DEPENDENCE variable=bin_iq_cache7 false
#pragma HLS ARRAY_RESHAPE variable=bin_iq_cache0 block dim=2 factor=16
#pragma HLS ARRAY_RESHAPE variable=bin_iq_cache1 block dim=2 factor=16
#pragma HLS ARRAY_RESHAPE variable=bin_iq_cache2 block dim=2 factor=16
#pragma HLS ARRAY_RESHAPE variable=bin_iq_cache3 block dim=2 factor=16
#pragma HLS ARRAY_RESHAPE variable=bin_iq_cache4 block dim=2 factor=16
#pragma HLS ARRAY_RESHAPE variable=bin_iq_cache5 block dim=2 factor=16
#pragma HLS ARRAY_RESHAPE variable=bin_iq_cache6 block dim=2 factor=16
#pragma HLS ARRAY_RESHAPE variable=bin_iq_cache7 block dim=2 factor=16


	// Fetch the out-bound rID IQs for this cycle
	// NB Using a switch in a for loop has no impact on RTL output
	cycle_id = i_stream.user;

	binndx_t cycle_bins[N_RES_PER_CLOCK];
	for (int i=0; i<N_RES_PER_CLOCK; i++) cycle_bins[i] = rid_to_bin[cycle_id][i];

	out0.data.val=bin_iq_cache0[cycle_bins[0].range(11,4)][cycle_bins[0].range(3,0)];
	out0.user=id_ndx;
	out1.data.val=bin_iq_cache1[cycle_bins[1].range(11,4)][cycle_bins[1].range(3,0)];
	out1.user=id_ndx+1;
	out2.data.val=bin_iq_cache2[cycle_bins[2].range(11,4)][cycle_bins[2].range(3,0)];
	out2.user=id_ndx+2;
	out3.data.val=bin_iq_cache3[cycle_bins[3].range(11,4)][cycle_bins[3].range(3,0)];
	out3.user=id_ndx+3;
	out4.data.val=bin_iq_cache4[cycle_bins[4].range(11,4)][cycle_bins[4].range(3,0)];
	out4.user=id_ndx+4;
	out5.data.val=bin_iq_cache5[cycle_bins[5].range(11,4)][cycle_bins[5].range(3,0)];
	out5.user=id_ndx+5;
	out6.data.val=bin_iq_cache6[cycle_bins[6].range(11,4)][cycle_bins[6].range(3,0)];
	out6.user=id_ndx+6;
	out7.data.val=bin_iq_cache7[cycle_bins[7].range(11,4)][cycle_bins[7].range(3,0)];
	out7.user=id_ndx+7;

	//Cache the new values
	iq_t temp[N_PFB_BINS_PER_CLK];
	for (int i=0; i<N_PFB_BINS_PER_CLK; i++){
		temp[i].real(i_stream.data.val[i]);
		temp[i].imag(q_stream.data.val[i]);
	}

	for (int i=0; i<N_PFB_BINS_PER_CLK; i++){
		bin_iq_cache0[cycle_id][i]=temp[i];
		bin_iq_cache1[cycle_id][i]=temp[i];
		bin_iq_cache2[cycle_id][i]=temp[i];
		bin_iq_cache3[cycle_id][i]=temp[i];
		bin_iq_cache4[cycle_id][i]=temp[i];
		bin_iq_cache5[cycle_id][i]=temp[i];
		bin_iq_cache6[cycle_id][i]=temp[i];
		bin_iq_cache7[cycle_id][i]=temp[i];
	}

	if (id_ndx == (N_RESONATORS-N_RES_PER_CLOCK)) id_ndx = 0;
	else id_ndx += N_RES_PER_CLOCK;

}
