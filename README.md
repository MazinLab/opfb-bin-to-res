# opfb-bin-to-res
Converts the stream of OPFB IQ bins into a stream of raw resonator IQ values

Git:  [opfb-bin-to-res](https://github.com/MazinLab/opfb-bin-to-res)

Inputs: 
- 512b AXI4S of 16 32 IQs equipped with TLAST
- AXI-Lite control port (resonator map:256 ap_uint<12*8> array)

Outputs:
- 256b AXI4S of 8 16 bit complex IQ equipped with TLAST (1b) and TUSER (8b)

Interface:

    void bin_to_res(hls::stream<opfb_stream_t> &iq_stream, hls::stream<resstream_t> &res_stream, binndxword_t rid_to_bin[N_GROUPS]) {
    #pragma HLS PIPELINE II=1
    #pragma HLS INTERFACE axis register port=iq_stream
    #pragma HLS INTERFACE axis register port=res_stream
    #pragma HLS INTERFACE s_axilite port=rid_to_bin name=resmap bundle=control
    #pragma HLS INTERFACE ap_ctrl_none port=return


This block ingests the IQ bins output (as wide words) by the OPFB subsystem and caches them round-robin into a  partitioned buffer:

    static binword_t cache[N_RES_PCLK][N_GROUPS];
    #pragma HLS ARRAY_PARTITION variable=cache dim=1 complete
    
The binword_t  is a unsigned 512b int that is packed into a 2D array. Dimension one is fully partitioned (one buffer per output lane). NB 4096 bins, 16 per clock, 256 cycles) 

    loadcache: for (int j=0;j<N_RES_PCLK;j++)
        cache[j][cache_group]=iq_in.data;

Each cycle the core outputs 8 cache values corresponding to the bins for the next 8 resonators (8 per clock 2048 res, 256 cycles).  The bin addresses are loaded from the resonator map port.

    resword_t temp;
    binndxword_t binword=rid_to_bin[replay_group];
    readcaches: for (unsigned int i=0; i<N_RES_PCLK; i++) {
        binndx_t bin=binword.range(12*(i+1)-1, 12*i);
        unsigned char group=bin/N_BIN_PCLK;
        unsigned char lane=bin%N_BIN_PCLK;
        temp.range(32*(i+1)-1, 32*i)=select(cache[i][group], lane);
    }

Select slices out the 32 bits from the correct bin in the group of 16 in the cache. This allows any resonator to be drawn from any bin and, though it does not matter for correctness, it should be noted that depending on the values assigned to resonator map  resonators may be drawn from both before and after the current cache write address and thus be 256 cycles out of phase from other resonators. The core keeps track of the group and outputs it on TUSER. The group counter is forced to 0 in an inbound TLAST ensuring that the core can not get out of sync. 

The resonator map can be programmed directly from PYNQ using mkidgen3.blocks.BinToResIP (see [mkidgen3](https://github.com/MazinLab/MKIDGen3)). See [gen3-vivado-top](https://github.com/MazinLab/gen3-vivado-top) for usage .
