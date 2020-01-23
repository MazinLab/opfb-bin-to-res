// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2.1 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// AXILiteS
// 0x0000 : Control signals
//          bit 0  - ap_start (Read/Write/COH)
//          bit 1  - ap_done (Read/COR)
//          bit 2  - ap_idle (Read)
//          bit 3  - ap_ready (Read)
//          bit 7  - auto_restart (Read/Write)
//          others - reserved
// 0x0004 : Global Interrupt Enable Register
//          bit 0  - Global Interrupt Enable (Read/Write)
//          others - reserved
// 0x0008 : IP Interrupt Enable Register (Read/Write)
//          bit 0  - Channel 0 (ap_done)
//          bit 1  - Channel 1 (ap_ready)
//          others - reserved
// 0x000c : IP Interrupt Status Register (Read/TOW)
//          bit 0  - Channel 0 (ap_done)
//          bit 1  - Channel 1 (ap_ready)
//          others - reserved
// 0x1000 ~
// 0x1fff : Memory 'rid_to_bin_V' (256 * 96b)
//          Word 4n   : bit [31:0] - rid_to_bin_V[n][31: 0]
//          Word 4n+1 : bit [31:0] - rid_to_bin_V[n][63:32]
//          Word 4n+2 : bit [31:0] - rid_to_bin_V[n][95:64]
//          Word 4n+3 : bit [31:0] - reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_AP_CTRL           0x0000
#define XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_GIE               0x0004
#define XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_IER               0x0008
#define XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_ISR               0x000c
#define XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_RID_TO_BIN_V_BASE 0x1000
#define XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_RID_TO_BIN_V_HIGH 0x1fff
#define XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_WIDTH_RID_TO_BIN_V     96
#define XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_DEPTH_RID_TO_BIN_V     256

