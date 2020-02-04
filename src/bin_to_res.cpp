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
void bin_to_res(opfb_stream_t &i_stream, opfb_stream_t &q_stream, resIQ_stream_t &res_stream,
		binndx_t rid_to_bin[N_GROUPS][N_RES_PCLK]) {
#pragma HLS PIPELINE II=1
#pragma HLS INTERFACE axis port=i_stream
#pragma HLS INTERFACE axis port=q_stream
#pragma HLS INTERFACE axis port=res_stream
#pragma HLS INTERFACE s_axilite port=rid_to_bin bundle=control
#pragma HLS INTERFACE s_axilite port=return  bundle=control
#pragma HLS ARRAY_RESHAPE variable=rid_to_bin complete dim=2

	static cycleid_t group = 0;

	// Cache
	static iq_t bin_cache[N_RES_PCLK][N_PFB_BINS];
#pragma HLS DATA_PACK variable=bin_cache
//#pragma HLS DEPENDENCE variable=bin_cache false
#pragma HLS ARRAY_PARTITION variable=bin_cache cyclic factor=16 dim=2
#pragma HLS ARRAY_PARTITION variable=bin_cache complete dim=1

	opfb_stream_t i_in=i_stream;
	opfb_stream_t q_in=q_stream;

	for (int i=0; i<N_RES_PCLK; i++)
		res_stream.data[i]=bin_cache[i][rid_to_bin[group][i]];
	res_stream.last=i_in.last;

	//Cache the new values
	binndx_t offset=group*N_BIN_PCLK;
	for (int i=0; i<N_BIN_PCLK; i++){
		iq_t iq;
		iq.real(i_in.data[i]);
		iq.imag(q_in.data[i]);
		for (int j=0;j<N_RES_PCLK;j++)
			bin_cache[j][offset+i]=iq;
	}

	group = i_stream.last ? binndx_t(0): binndx_t(group+1);

}
