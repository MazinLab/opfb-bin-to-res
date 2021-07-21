// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// control
// 0x1000 ~
// 0x1fff : Memory 'rid_to_bin' (256 * 128b)
//          Word 4n   : bit [31:0] - rid_to_bin[n][31: 0]
//          Word 4n+1 : bit [31:0] - rid_to_bin[n][63:32]
//          Word 4n+2 : bit [31:0] - rid_to_bin[n][95:64]
//          Word 4n+3 : bit [31:0] - rid_to_bin[n][127:96]
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XBIN_TO_RES_CONTROL_ADDR_RID_TO_BIN_BASE 0x1000
#define XBIN_TO_RES_CONTROL_ADDR_RID_TO_BIN_HIGH 0x1fff
#define XBIN_TO_RES_CONTROL_WIDTH_RID_TO_BIN     128
#define XBIN_TO_RES_CONTROL_DEPTH_RID_TO_BIN     256

