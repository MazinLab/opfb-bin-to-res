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
void bin_to_res(opfb_stream_t i_stream[N_GROUPS], opfb_stream_t q_stream[N_GROUPS],
				resstream_t res_stream[N_GROUPS], binndx_t rid_to_bin[N_GROUPS][N_RES_PCLK]) {

#pragma HLS INTERFACE axis port=i_stream //depth=256
#pragma HLS INTERFACE axis port=q_stream //depth=256
#pragma HLS INTERFACE axis port=res_stream //depth=256
#pragma HLS INTERFACE s_axilite port=rid_to_bin bundle=control //depth=2048
#pragma HLS INTERFACE s_axilite port=return  //depth=256//bundle=control depth=256
#pragma HLS ARRAY_RESHAPE variable=rid_to_bin complete dim=2

	// Cache
	static iq_t cache[N_RES_PCLK][N_PFB_BINS];
	static bool primed=false;
#pragma HLS DATA_PACK variable=cache
#pragma HLS ARRAY_PARTITION variable=cache cyclic factor=16 dim=2
#pragma HLS ARRAY_PARTITION variable=cache complete dim=1

	eachgroup: for (unsigned int group=0;group<N_GROUPS; group++) {
#pragma HLS pipeline rewind
		opfb_stream_t i_in=i_stream[group];
		opfb_stream_t q_in=q_stream[group];
		binndx_t offset=group*N_BIN_PCLK;

		//Cache the new values
		newbins: for (unsigned int i=0; i<N_BIN_PCLK; i++){
			iq_t iq;
			iq.real(i_in.data[i]);
			iq.imag(q_in.data[i]);
			loadcache: for (int j=0;j<N_RES_PCLK;j++)
				cache[j][offset+i]=iq;
		}

		//Load the correct values from the cache
		resstream_t temp;
		temp.last=group==N_GROUPS-1;
		//if (primed) {
			readcaches: for (unsigned int i=0; i<N_RES_PCLK; i++) temp.data[i]=cache[i][rid_to_bin[group][i]];
		//} else for (unsigned int i=0; i<N_RES_PCLK; i++) temp.data[i]=iq_t(0,0);

		res_stream[group]=temp;

		//primed|=group==N_GROUPS-1;
	}
}
