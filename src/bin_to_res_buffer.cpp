/*
Get 16 bins in
Get seq. number in
Get 8 Rids in


Get bin addresses for RIDs via LUT (2048 addr. 12bit values (4096 bins) = 24kbits)
8 addresses, each repeated at most 2 times.

Fetch last cycles bin values via the addresses
8 read ports
Write 16 bins

Cache is 4096 * IQ ~ 131kbits

combine the 8 IQs read with their rIDs and output
 */

#include "ap_int.h"
#include "hls_stream.h"
#include "bin_to_res_buffer.hpp"


//Assume natural order for now
void bin_to_res_buff(hls::stream<opfb_stream_t> &i_stream, hls::stream<opfb_stream_t> &q_stream,
		hls::stream<resIQ_stream_t> &out0, hls::stream<resIQ_stream_t> &out1,
		hls::stream<resIQ_stream_t> &out2, hls::stream<resIQ_stream_t> &out3,
		hls::stream<resIQ_stream_t> &out4, hls::stream<resIQ_stream_t> &out5,
		hls::stream<resIQ_stream_t> &out6, hls::stream<resIQ_stream_t> &out7,
		binndx_t rid_to_bin[N_RESONATORS]) {

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
#pragma HLS INTERFACE ap_ctrl_none port=return
//#pragma HLS INTERFACE axilite port=return
//#pragma HLS DATA_PACK variable=out_val.data
//#pragma HLS DATA_PACK variable=in_ivals.data
//#pragma HLS DATA_PACK variable=in_qvals.data
#pragma HLS DATA_PACK variable=i_stream
#pragma HLS DATA_PACK variable=q_stream


	// Working variables
	opfb_stream_t in_ivals, in_qvals;
	resIQ_stream_t out_val;
	iq_t val;


	// Cache
	static iq_t bin_iq_cache[N_PFB_BINS];  //IQ values from the past cycle
	static resid_t id_ndx=0;  //This is the rID of the rIDout[0], increments by N_RES_PER_CLOCK,

	// Fetch the outbound rID IQs for this cycle
	for (int i=0; i<N_RES_PER_CLOCK; i++){
		out_val.data.val=bin_iq_cache[rid_to_bin[id_ndx+i]];
		out_val.user=id_ndx+i;
	    switch(i) {
	        case 0: out0<<out_val; break;
	        case 1: out1<<out_val; break;
	        case 2: out2<<out_val; break;
	        case 3: out3<<out_val; break;
	        case 4: out4<<out_val; break;
	        case 5: out5<<out_val; break;
	        case 6: out6<<out_val; break;
	        case 7: out7<<out_val; break;
	    }
	}
	if (id_ndx == (N_RESONATORS-N_RES_PER_CLOCK)) id_ndx = 0;
	else id_ndx += N_RES_PER_CLOCK;

//	//Cache the new vals
	i_stream>>in_ivals;
	q_stream>>in_qvals;
////	for (int i=0; i<N_PFB_BINS_PER_CLK; i++){
////		val.real(in_ivals.data.iorq[i]);
////		val.imag(in_qvals.data.iorq[i]);
////		bin_iq_cache[in_ivals.user*N_PFB_BINS_PER_CLK+i] = val;
////	}

}

//https://forums.xilinx.com/t5/High-Level-Synthesis-HLS/DATA-PACK-on-HLS-Stream-gives-error-when-accessing-member-of-a/td-p/737854  no luck
