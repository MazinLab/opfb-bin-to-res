#ifndef __bin_to_res_buffer_h__
#define __bin_to_res_buffer_h__

#include "ap_int.h"
#include "hls_stream.h"
#include <complex>

#define N_PFB_BINS_PER_CLK 16
#define N_PFB_BINS 4096
#define N_PFB_CYCLES (N_PFB_BINS/N_PFB_BINS_PER_CLK)
#define N_CYCLES 256
#define N_RESONATORS 2048

#define MAX_RES_IN_BIN 2  //because bins are overlapped by 50% effective wid. is 1MHz
#define N_RES_PER_CLOCK 8

#define channfo_t ap_uint<2>
#define binchndx_t ap_uint<4>
#define binndx_t ap_uint<12> //ap_uint<11>  //must match bit width of N_PFB_BINS
#define resid_t ap_uint<11>  //must match bit width of N_RESONATORS
#define cycleid_t ap_uint<8>  //must match bit width of N_CYCLES

//struct ap_axiu{
// ap_uint<D>   data;
// ap_uint<D/8> keep;
// ap_uint<D/8> strb;
// ap_uint<U>   user;
// ap_uint<1>   last;
// ap_uint<TI>  id;
// ap_uint<TD>  dest;
//};

typedef std::complex< ap_int<16> > iq_t;

typedef struct resiq_t{
    iq_t iq;
    resid_t resID;
} resiq_t;

//typedef struct iqvals_t {
//	iq_t iqvals[N_PFB_BINS_PER_CLK];
//} iqvals_t;

//typedef struct IorQ_t {
//	ap_uint<16> val;
//} IorQ_t;

//typedef struct iorqvals_t {
//	ap_uint<16> vals[N_PFB_BINS_PER_CLK];
//} iorqvals_t;

//typedef struct iorqvals_t {
//	IorQ_t iorq[N_PFB_BINS_PER_CLK];
//} iorqvals_t;

//typedef struct AXI_OPFB_VALUE{
//	iorqvals_t data;
//    cycleid_t  user;   //TODO I intend for this to be TUSER, don't think that works with this name
//} AXI_OPFB_VALUE;


typedef struct resIQ_stream_t{
 struct {
	 iq_t val;
 } data;
 resid_t user;
} resIQ_stream_t;

typedef struct pfb_IQ_bins_t{
	iq_t val[N_PFB_BINS_PER_CLK];
} pfb_IQ_bins_t;

typedef struct pfb_output_t{
    ap_uint<16> val[N_PFB_BINS_PER_CLK];
} pfb_output_t;

typedef struct opfb_stream_t{
	pfb_output_t data;
    cycleid_t user;
} opfb_stream_t;



//TODO should be N_RES_PER_CLOCK wide

//in old code: stream of struct.data(struct).iqvals(array of structs).val(2 apuint)
//here: stream of struct.data(struct).vals(array of apuint)
//change to : stream of struct.data(struct).iorq(array of structs).val(apuint)

void bin_to_res_buff(hls::stream<opfb_stream_t> &i_stream, hls::stream<opfb_stream_t> &q_stream,
		hls::stream<resIQ_stream_t> &out0, hls::stream<resIQ_stream_t> &out1,
		hls::stream<resIQ_stream_t> &out2, hls::stream<resIQ_stream_t> &out3,
		hls::stream<resIQ_stream_t> &out4, hls::stream<resIQ_stream_t> &out5,
		hls::stream<resIQ_stream_t> &out6, hls::stream<resIQ_stream_t> &out7,
		binndx_t rid_to_bin[N_RESONATORS]);

void bin_to_res_buff_nostream(opfb_stream_t &i_stream, opfb_stream_t &q_stream,
		resIQ_stream_t &out0, resIQ_stream_t &out1,
		resIQ_stream_t &out2, resIQ_stream_t &out3,
		resIQ_stream_t &out4, resIQ_stream_t &out5,
		resIQ_stream_t &out6, resIQ_stream_t &out7,
		binndx_t rid_to_bin[N_CYCLES][N_RES_PER_CLOCK]);

void bin_to_res_buff_multibuffer(opfb_stream_t &i_stream, opfb_stream_t &q_stream,
		resIQ_stream_t &out0, resIQ_stream_t &out1, resIQ_stream_t &out2, resIQ_stream_t &out3,
		resIQ_stream_t &out4, resIQ_stream_t &out5, resIQ_stream_t &out6, resIQ_stream_t &out7,
		binndx_t rid_to_bin[N_CYCLES][N_RES_PER_CLOCK]);

void bin_to_res_buff_multibuffer_struct(opfb_stream_t &i_stream, opfb_stream_t &q_stream,
		resIQ_stream_t &out0, resIQ_stream_t &out1, resIQ_stream_t &out2, resIQ_stream_t &out3,
		resIQ_stream_t &out4, resIQ_stream_t &out5, resIQ_stream_t &out6, resIQ_stream_t &out7,
		binndx_t rid_to_bin[N_CYCLES][N_RES_PER_CLOCK]);

void bin_to_res_buff_extcache(opfb_stream_t &i_stream, opfb_stream_t &q_stream,
		resIQ_stream_t &out0, resIQ_stream_t &out1, resIQ_stream_t &out2, resIQ_stream_t &out3,
		resIQ_stream_t &out4, resIQ_stream_t &out5, resIQ_stream_t &out6, resIQ_stream_t &out7,
		binndx_t rid_to_bin[N_CYCLES][N_RES_PER_CLOCK],
		pfb_output_t pfb_cache_out[N_RES_PER_CLOCK][N_CYCLES],
		iq_t pfb_in_cache[N_RES_PER_CLOCK][N_PFB_BINS]);

void bin_to_res_buff_extcache(opfb_stream_t &i_stream, opfb_stream_t &q_stream,
		resIQ_stream_t &out0, resIQ_stream_t &out1, resIQ_stream_t &out2, resIQ_stream_t &out3,
		resIQ_stream_t &out4, resIQ_stream_t &out5, resIQ_stream_t &out6, resIQ_stream_t &out7,
		binndx_t rid_to_bin[N_CYCLES][N_RES_PER_CLOCK],
		pfb_IQ_bins_t &pfb_cache_out,  cycleid_t &cycle_addr,
		iq_t pfb_cache_in0[N_PFB_BINS],
		iq_t pfb_cache_in1[N_PFB_BINS],
		iq_t pfb_cache_in2[N_PFB_BINS],
		iq_t pfb_cache_in3[N_PFB_BINS],
		iq_t pfb_cache_in4[N_PFB_BINS],
		iq_t pfb_cache_in5[N_PFB_BINS],
		iq_t pfb_cache_in6[N_PFB_BINS],
		iq_t pfb_cache_in7[N_PFB_BINS]);

#endif
