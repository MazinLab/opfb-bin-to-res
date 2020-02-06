// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2.1 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// AXILiteS
// 0x1000 ~
// 0x1fff : Memory 'S_AXI_resmap_V' (256 * 96b)
//          Word 4n   : bit [31:0] - S_AXI_resmap_V[n][31: 0]
//          Word 4n+1 : bit [31:0] - S_AXI_resmap_V[n][63:32]
//          Word 4n+2 : bit [31:0] - S_AXI_resmap_V[n][95:64]
//          Word 4n+3 : bit [31:0] - reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XBIN_TO_RES_AXILITES_ADDR_S_AXI_RESMAP_V_BASE 0x1000
#define XBIN_TO_RES_AXILITES_ADDR_S_AXI_RESMAP_V_HIGH 0x1fff
#define XBIN_TO_RES_AXILITES_WIDTH_S_AXI_RESMAP_V     96
#define XBIN_TO_RES_AXILITES_DEPTH_S_AXI_RESMAP_V     256

