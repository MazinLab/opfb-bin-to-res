// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2.1 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// control
// 0x0000 : reserved
// 0x0004 : reserved
// 0x0008 : reserved
// 0x000c : reserved
// 0x2000 : Data signal of align_V
//          bit 8~0 - align_V[8:0] (Read)
//          others  - reserved
// 0x2004 : // 0x1000 ~
// 0x1fff : Memory 'resmap_V' (256 * 96b)
//          Word 4n   : bit [31:0] - resmap_V[n][31: 0]
//          Word 4n+1 : bit [31:0] - resmap_V[n][63:32]
//          Word 4n+2 : bit [31:0] - resmap_V[n][95:64]
//          Word 4n+3 : bit [31:0] - reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XBIN_TO_RES_CONTROL_ADDR_ALIGN_V_DATA  0x2000
#define XBIN_TO_RES_CONTROL_BITS_ALIGN_V_DATA  9
#define XBIN_TO_RES_CONTROL_ADDR_RESMAP_V_BASE 0x1000
#define XBIN_TO_RES_CONTROL_ADDR_RESMAP_V_HIGH 0x1fff
#define XBIN_TO_RES_CONTROL_WIDTH_RESMAP_V     96
#define XBIN_TO_RES_CONTROL_DEPTH_RESMAP_V     256

