#include "bin_to_res.hpp"
/*
16 bins arrive each clock, last set of final group
rid_to_bin[i][j] specifies the OPFB bin address (e.g. 0-4095) containing the
resonator IQ that for the resonator output on cycle i, lane j.

Flow:
Grab the addresses from the map.
Fetch the bins for each address and load the output stream.
Write the 16 new bins.
*/
void bin_to_res(opfb_stream_t &iq_stream, resstream_t &res_stream,
				binndx_t rid_to_bin[N_GROUPS][N_RES_PCLK],
				ap_int<9> &group_align											   	   ) {
#pragma HLS PIPELINE II=1
#pragma HLS INTERFACE axis register reverse port=iq_stream
#pragma HLS INTERFACE axis register forward port=res_stream
#pragma HLS INTERFACE s_axilite port=rid_to_bin clock=S_AXI_clk name=resmap bundle=control
#pragma HLS INTERFACE s_axilite port=group_align clock=S_AXI_clk name=align bundle=control
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS ARRAY_RESHAPE variable=rid_to_bin complete dim=2

	// Cache
	static iq_t cache[N_RES_PCLK][N_PFB_BINS];
#pragma HLS DATA_PACK variable=cache
#pragma HLS ARRAY_PARTITION variable=cache cyclic factor=16 dim=2
#pragma HLS ARRAY_PARTITION variable=cache complete dim=1

	static cycleid_t replay_group, cache_group;
	opfb_stream_t iq_in=iq_stream;

	//Cache the new values
	newbins: for (unsigned int i=0; i<N_BIN_PCLK; i++){
		iq_t iq=iq_in.data[i];
		loadcache: for (int j=0;j<N_RES_PCLK;j++)
			cache[j][cache_group*N_BIN_PCLK+i]=iq;
	}

	//Load the correct values from the cache
	resstream_t temp;
	temp.last=replay_group==N_GROUPS-1;
	readcaches: for (unsigned int i=0; i<N_RES_PCLK; i++)
		temp.data[i]=cache[i][rid_to_bin[replay_group][i]];
	res_stream=temp;

	group_align = cache_group - replay_group;
	replay_group++;
	cache_group = iq_in.last ? cycleid_t(0):cycleid_t(cache_group+1);
}
