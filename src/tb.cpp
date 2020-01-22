#include "bin_to_res_buffer.h"


/*
 * Test bench for IP to convert overlapped polyphase filter bank I & Q streams into
 * streams of IQ values corresponding to individual resonators. The OPFB yields 4096 IQ bins (16 consecutive per clock)
 * values from which a pre-determined (but reconfigurable) set of 512-2048 bins are output as IQ values
 * for 2048 resonators (e.g. up to 4 resonators may share a bin).
 *
 * The core receives a pair of axi streams (16x16bit @512 MHz) corresponding to an array of 16
 * ap_int<16> values. The streams each have an ap_uint<8> TUSER value corresponding to the cycle (0-255) of the
 * PFB. The core outputs 8 axi streams of 32 bit complex numbers (std::complex< ap_int<16> >) each with a
 * TUSER side-channel specifying a resonator ID (ap_uint<11>, should be automatically byte-padded per protocol).
 *
 * Configuration of the core is accomplished by programming a resonator ID to filterbank output bin LUT
 * (rid_to_bin) over axilite.
 *
 * In normal operation the core cycles through the LUT 8 values at a time. These values are used to address
 * a cache (read before write) of the IQ values from the OPFB and the retrieved IQ values output on the 8 axis
 * output streams along with their resonator ID in TUSER.
 *
 * This (highly inefficient) design eight copies (one for each output stream) of a full OPFB cycle of
 * bins is cached in BRAM. Each copy must support 16 consecutive IQ writes per cycle (512b) and 1 arbitrary IQ read (32b).
 * This implies we need 128 18K BRAMS  8 sets of (16 32bx256 S2P), and efficiency of 5% on memory
 * (4096x32bits of unique cache). Even allowing that the duplication is required for ports the approach is still wasting
 * about 55% of the BRAM space.
 *
 * Internally the addresses for the resonators in the LUT are stored as 8 bits specifying cycle and three bits specifying
 * bin in that cycle. I don't really care for this and would prefer a flat address space.
 *
 * Questions:
 * 1) Why is this using ~10% of the LUT resources on an Ultrascale+. Is there some significant inefficiency in the way
 * I've implemented the cache.
 * 2) Is there a fundamentally different approach here I'm missing? Since there are constraints on the bin-resonator map
 * and most bins will be unused it seems like there should be a way to do with with some FIFOs or other approach that does
 * not involve such an inefficient cache!
 *
 */

#define N_OPFB_CYCLES 2
#define N_SAMPLES  N_OPFB_CYCLES*N_CYCLES

int main() {

	//Step 1 generate input and output expected arrays
	int res=0;
	binndx_t rid_to_bin[N_CYCLES][N_RES_PER_CLOCK];
	opfb_stream_t istream[N_OPFB_CYCLES][N_CYCLES], qstream[N_OPFB_CYCLES][N_CYCLES];
	resIQ_stream_t out[8];

	//i counts up, q counts down, both shifted by cycle (so 0-4095 & 4095-0, 4096-8191 & 8191-4096, ...)
	for (int i=0;i<N_OPFB_CYCLES;i++) {
		for (int j=0;j<N_CYCLES;j++) {
			for (int k=0; k<N_PFB_BINS_PER_CLK; k++) istream[i][j].data.val[k]=i*N_PFB_BINS + (j*N_PFB_BINS_PER_CLK+k);
			for (int k=0; k<N_PFB_BINS_PER_CLK; k++) qstream[i][j].data.val[k]=(i+1)*N_PFB_BINS -(j*N_PFB_BINS_PER_CLK+k);
			istream[i][j].user=j;
			qstream[i][j].user=j;
		}
	}

	//Load rid_to_bin
	for (int j=0;j<N_CYCLES;j++) {
		for (int k=0; k<N_RES_PER_CLOCK; k++) rid_to_bin[j][k]=j<<4|k*2;
	}


	//Run core
	for (int i=0;i<N_OPFB_CYCLES;i++) {
		res=0;
		for (int j=0;j<N_CYCLES;j++) {
			bin_to_res_buff_multibuffer(istream[i][j], qstream[i][j],
					out[0], out[1], out[2], out[3], out[4], out[5], out[6], out[7], rid_to_bin);
			if (i==0) continue; //takes a cycle to prime the buffer
			for (int k=0;k<N_RES_PER_CLOCK;k++) {
				int cycle=rid_to_bin[j][k].to_int()>>4, bin=rid_to_bin[j][k].to_int()&0xF;
				if (out[k].data.val.real().to_int() != istream[i-1][cycle].data.val[bin].to_int() ||
					out[k].data.val.imag().to_int() != qstream[i-1][cycle].data.val[bin].to_int() ||
					out[k].user.to_int() != res) {
					return 1;
				}
				res++;
			}
		}
	}
//Compare results
	return 0;

}
