#ifndef __bin_to_res_buffer_h__
#define __bin_to_res_buffer_h__

#include "ap_int.h"
#include <complex>

#define N_BIN_PCLK 16
#define N_PFB_BINS 4096
#define N_GROUPS 256
//#define N_RESONATORS 2048
#define N_RES_PCLK 8


typedef ap_uint<12> binndx_t;  //must match bit width of N_PFB_BINS
typedef ap_uint<8> cycleid_t;  //must match bit width of N_GROUPS
typedef ap_uint<16> sample_t;
typedef std::complex< sample_t > iq_t;

typedef struct resIQ_stream_t{
	iq_t data[N_RES_PCLK];
	ap_uint<1> last;
//	ap_uint<32> keep;
} resstream_t;

typedef struct opfb_stream_t{
	sample_t data[N_BIN_PCLK];
    ap_uint<1> last;
} opfb_stream_t;

void bin_to_res(opfb_stream_t i_stream[N_GROUPS], opfb_stream_t q_stream[N_GROUPS],
				resstream_t out[N_GROUPS], binndx_t rid_to_bin[N_GROUPS][N_RES_PCLK]);


#endif
