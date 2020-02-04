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
#include "bin_to_res.hpp"
#define N_OPFB_CYCLES 2
#define N_SAMPLES  N_OPFB_CYCLES*N_GROUPS

int main() {

	//Setup
	binndx_t rid_to_bin[N_GROUPS][N_RES_PCLK];
	opfb_stream_t istream[N_OPFB_CYCLES][N_GROUPS], qstream[N_OPFB_CYCLES][N_GROUPS];
	resstream_t out[N_OPFB_CYCLES][N_GROUPS];
	bool fail=false;

	//i counts up, q counts down, both shifted by cycle (so 0-4095 & 4095-0, 4096-8191 & 8191-4096, ...)
	for (int i=0;i<N_OPFB_CYCLES;i++) {
		for (int j=0;j<N_GROUPS;j++) {
			for (int k=0; k<N_BIN_PCLK; k++) {
				istream[i][j].data[k]=i*N_PFB_BINS + (j*N_BIN_PCLK+k);
				qstream[i][j].data[k]=(i+1)*N_PFB_BINS -(j*N_BIN_PCLK+k);
			}
			istream[i][j].last=j==N_GROUPS-1;
			qstream[i][j].last=j==N_GROUPS-1;
		}
	}

	//Load rid_to_bin
	//	//Load in bin to res duplication factors
	//	FILE *fp;
	//	unsigned int in_bin;
	//	fp=fopen("res_in_bin.dat", "r");
	//	if (fp==NULL) {
	//		cout<<"Null file"<<endl;
	//		return 1;
	//	}
	//	for (int i=0; i<N_RES_GROUPS*N_BIN_PCLK; i++){
	//		fscanf(fp, "%d", &in_bin);
	//		in_bin = in_bin > MAX_RES_PBIN ? MAX_RES_PBIN:in_bin;
	//		bin2resmap[i/N_BIN_PCLK].data[i%N_BIN_PCLK] = binmap_t(in_bin);
	//	}
	//	fclose(fp);
	int res=0;
	for (int j=0;j<N_GROUPS;j++) {
		for (int k=0; k<N_RES_PCLK; k++)
			rid_to_bin[j][k]=res++;//j/2*N_BIN_PCLK+k;
	}

	//Run core
	//NB w/o static copy arguments the cosim TB sigsegv!
	for (int i=0;i<N_OPFB_CYCLES;i++) {

		//Copy in, trying to figure out cosim fail
		static opfb_stream_t itmp[N_GROUPS], qtmp[N_GROUPS];
		static resstream_t otmp[N_GROUPS];
		for (int j=0;j<N_GROUPS;j++){
			itmp[j]=istream[i][j];
			qtmp[j]=qstream[i][j];
		}

		//Call core
		bin_to_res(itmp, qtmp, otmp, rid_to_bin);

		//Copy out, trying to figure out cosim fail
		for (int j=0;j<N_GROUPS;j++)
			out[i][j]=otmp[j];
	}

	//Compare results
	for (int i=0;i<N_OPFB_CYCLES;i++) {
		for (int j=0;j<N_GROUPS;j++) {
			for (int k=0;k<N_RES_PCLK;k++) {
				//if (i==0) continue; //takes a cycle to prime the buffer
				unsigned int bin=rid_to_bin[j][k].to_uint();
				unsigned int group=bin/N_BIN_PCLK;
				unsigned int ndx=bin%N_BIN_PCLK;
				iq_t expected=iq_t(istream[i][group].data[ndx], qstream[i][group].data[ndx]);
				std::cout<<"Out "<<i<<","<<j<<","<<k<<": "<<out[i][j].data[k];
				std::cout<<" Bin: "<<bin<<" ("<<group<<","<<ndx<<")";
				std::cout<<" Expected: "<<expected<<"\n";
				if (out[i][j].data[k] != expected ) {
					fail|=true;
				}
				if(out[i][j].last != istream[i][j].last){
					std::cout<<"last mismatch!!!!\n";
					fail|=true;
				}
			}
		}
	}

	if (fail) std::cout<<"FAIL!\n";
	else std::cout<<"PASS!\n";

	return fail;

}
