#ifndef __bin_to_res_buffer_h__
#define __bin_to_res_buffer_h__

#include "ap_int.h"
#include <complex>
#include <hls_stream.h>
#include "ap_axi_sdata.h"

#define N_BIN_PCLK 16
#define N_PFB_BINS 4096
#define N_GROUPS 256
#define N_RES_PCLK 8


typedef ap_uint<12> binndx_t;  //must match bit width of N_PFB_BINS
typedef ap_uint<12*N_RES_PCLK> binndxword_t;  //must match bit width of N_PFB_BINS*N_RES_PCLK
typedef ap_uint<8> cycleid_t;  //must match bit width of N_GROUPS
typedef unsigned int iq_t;

typedef ap_uint<512> binword_t;
typedef ap_uint<256> resword_t;


//template<int D,int U,int TI,int TD>
//  struct ap_axiu{
//    ap_uint<D>       data;
//    ap_uint<(D+7)/8> keep;
//    ap_uint<(D+7)/8> strb;
//    ap_uint<U>       user;
//    ap_uint<1>       last;
//    ap_uint<TI>      id;
//    ap_uint<TD>      dest;
//  };
//
//



typedef ap_axiu<512,0,0,0> opfb_stream_t;

typedef ap_axiu<256,8,0,0> resstream_t;
//typedef struct resstream_t{
//	resword_t data;
//	ap_uint<1> last;
//	ap_uint<8> user;
//} resstream_t;

typedef struct resstream_array_t{
	iq_t data[N_RES_PCLK];
	ap_uint<1> last;
	ap_uint<8> user;
} resstream_array_t;

typedef struct opfb_stream_array_t{
	iq_t data[N_BIN_PCLK];
    ap_uint<1> last;
} opfb_stream_array_t;

void bin_to_res(hls::stream<opfb_stream_t> &iq_stream, hls::stream<resstream_t> &out,
				binndxword_t rid_to_bin[N_GROUPS]);

//void bin_to_res(opfb_stream_t iq_stream[N_GROUPS], resstream_t out[N_GROUPS], binndxword_t rid_to_bin[N_GROUPS]);

#endif
