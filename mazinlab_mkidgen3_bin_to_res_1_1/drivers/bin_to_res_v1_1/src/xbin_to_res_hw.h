// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// control
// 0x1000 ~
// 0x1fff : Memory 'resmap' (256 * 128b)
//          Word 4n   : bit [31:0] - resmap[n][31: 0]
//          Word 4n+1 : bit [31:0] - resmap[n][63:32]
//          Word 4n+2 : bit [31:0] - resmap[n][95:64]
//          Word 4n+3 : bit [31:0] - resmap[n][127:96]
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XBIN_TO_RES_CONTROL_ADDR_RESMAP_BASE 0x1000
#define XBIN_TO_RES_CONTROL_ADDR_RESMAP_HIGH 0x1fff
#define XBIN_TO_RES_CONTROL_WIDTH_RESMAP     128
#define XBIN_TO_RES_CONTROL_DEPTH_RESMAP     256

