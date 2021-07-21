#include "bin_to_res.hpp"

iq_t select(binword_t word, unsigned char lane) {
#pragma HLS INLINE

	iq_t iqtmp[16];
#pragma HLS ARRAY_PARTITION variable=iqtmp complete
	for (int j=0;j<N_BIN_PCLK;j++) iqtmp[j]=word.range((j+1)*32-1, j*32);
	return iqtmp[lane];
}

/*
16 bins arrive each clock, last set of final group
rid_to_bin[i][j] specifies the OPFB bin address (e.g. 0-4095) containing the
resonator IQ that for the resonator output on cycle i, lane j.

Flow:
Grab the addresses from the map.
Fetch the bins for each address and load the output stream.
Write the 16 new bins.
*/


void bin_to_res(hls::stream<opfb_stream_t> &iq_stream, hls::stream<resstream_t> &res_stream, binndxword_t rid_to_bin[N_GROUPS]) {
#pragma HLS PIPELINE II=1
#pragma HLS INTERFACE axis register port=iq_stream
#pragma HLS INTERFACE axis register port=res_stream
#pragma HLS INTERFACE s_axilite port=rid_to_bin name=resmap bundle=control
#pragma HLS INTERFACE ap_ctrl_none port=return

	// Cache
	static binword_t cache[N_RES_PCLK][N_GROUPS];
#pragma HLS ARRAY_PARTITION variable=cache dim=1 complete

	static cycleid_t replay_group, cache_group;
	opfb_stream_t iq_in;
	iq_stream.read(iq_in);


	//Cache the new values
	loadcache: for (int j=0;j<N_RES_PCLK;j++)
		cache[j][cache_group]=iq_in.data;

	//Load the correct values from the cache
	resword_t temp;
	binndxword_t binword=rid_to_bin[replay_group];
	readcaches: for (unsigned int i=0; i<N_RES_PCLK; i++) {
		binndx_t bin=binword.range(12*(i+1)-1, 12*i);
		unsigned char group=bin/N_BIN_PCLK;
		unsigned char lane=bin%N_BIN_PCLK;

		temp.range(32*(i+1)-1, 32*i)=select(cache[i][group], lane);
//		temp.data.range(32*(i+1), 32*i)=32*(i+1).range((lane+1)*32, 32*lane);
	}

	resstream_t output_tmp;
	output_tmp.data=temp;
	output_tmp.last=replay_group==N_GROUPS-1;
	output_tmp.user=replay_group;
	res_stream.write(output_tmp);

	replay_group++;
	cache_group = iq_in.last ? cycleid_t(0):cycleid_t(cache_group+1);

}



//void bin_to_res(opfb_stream_t iq_stream[N_GROUPS], resstream_t res_stream[N_GROUPS],
//		binndxword_t rid_to_bin[N_GROUPS]){//[N_RES_PCLK]) {
//#pragma HLS PIPELINE II=256
//#pragma HLS INTERFACE axis register port=iq_stream
//#pragma HLS INTERFACE axis register port=res_stream
//#pragma HLS INTERFACE s_axilite port=rid_to_bin clock=S_AXI_clk name=resmap bundle=control
//#pragma HLS INTERFACE ap_ctrl_none port=return
////#pragma HLS ARRAY_RESHAPE variable=rid_to_bin complete dim=2
//
//	// Cache
//	binword_t cache[N_RES_PCLK][N_GROUPS];
//#pragma HLS ARRAY_PARTITION variable=cache complete dim=1
//
//
//	for (int i=0; i<N_GROUPS;i++) {
//		binword_t store=iq_stream[i].data;
//		for (int j=0;j<N_RES_PCLK;j++){
//			cache[j][i]=store;
//		}
//	}
//
//	for (int i=0; i<N_GROUPS;i++) {
//		binndxword_t binword=rid_to_bin[i];
//		resstream_t temp;
//		for (int j=0;j<N_RES_PCLK;j++){
//			binndx_t bin=binword.range(12*(i+1)-1,12*i);
//			unsigned char group, lane;
//			group = bin/N_BIN_PCLK;
//			lane = bin%N_BIN_PCLK;
//			temp.data.range(32*(i+1)-1, 32*i)=select(cache[j][group], lane);
//		}
//		temp.last=i==N_GROUPS-1;
//		temp.user=i;
//		res_stream[i]=temp;
//	}
//
//}
