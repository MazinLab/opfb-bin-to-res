// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2.1 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xbin_to_res_buff_multibuffer.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XBin_to_res_buff_multibuffer_CfgInitialize(XBin_to_res_buff_multibuffer *InstancePtr, XBin_to_res_buff_multibuffer_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Axilites_BaseAddress = ConfigPtr->Axilites_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XBin_to_res_buff_multibuffer_Start(XBin_to_res_buff_multibuffer *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XBin_to_res_buff_multibuffer_ReadReg(InstancePtr->Axilites_BaseAddress, XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_AP_CTRL) & 0x80;
    XBin_to_res_buff_multibuffer_WriteReg(InstancePtr->Axilites_BaseAddress, XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_AP_CTRL, Data | 0x01);
}

u32 XBin_to_res_buff_multibuffer_IsDone(XBin_to_res_buff_multibuffer *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XBin_to_res_buff_multibuffer_ReadReg(InstancePtr->Axilites_BaseAddress, XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XBin_to_res_buff_multibuffer_IsIdle(XBin_to_res_buff_multibuffer *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XBin_to_res_buff_multibuffer_ReadReg(InstancePtr->Axilites_BaseAddress, XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XBin_to_res_buff_multibuffer_IsReady(XBin_to_res_buff_multibuffer *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XBin_to_res_buff_multibuffer_ReadReg(InstancePtr->Axilites_BaseAddress, XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XBin_to_res_buff_multibuffer_EnableAutoRestart(XBin_to_res_buff_multibuffer *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XBin_to_res_buff_multibuffer_WriteReg(InstancePtr->Axilites_BaseAddress, XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_AP_CTRL, 0x80);
}

void XBin_to_res_buff_multibuffer_DisableAutoRestart(XBin_to_res_buff_multibuffer *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XBin_to_res_buff_multibuffer_WriteReg(InstancePtr->Axilites_BaseAddress, XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_AP_CTRL, 0);
}

u32 XBin_to_res_buff_multibuffer_Get_rid_to_bin_V_BaseAddress(XBin_to_res_buff_multibuffer *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Axilites_BaseAddress + XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_RID_TO_BIN_V_BASE);
}

u32 XBin_to_res_buff_multibuffer_Get_rid_to_bin_V_HighAddress(XBin_to_res_buff_multibuffer *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Axilites_BaseAddress + XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_RID_TO_BIN_V_HIGH);
}

u32 XBin_to_res_buff_multibuffer_Get_rid_to_bin_V_TotalBytes(XBin_to_res_buff_multibuffer *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_RID_TO_BIN_V_HIGH - XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_RID_TO_BIN_V_BASE + 1);
}

u32 XBin_to_res_buff_multibuffer_Get_rid_to_bin_V_BitWidth(XBin_to_res_buff_multibuffer *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_WIDTH_RID_TO_BIN_V;
}

u32 XBin_to_res_buff_multibuffer_Get_rid_to_bin_V_Depth(XBin_to_res_buff_multibuffer *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_DEPTH_RID_TO_BIN_V;
}

u32 XBin_to_res_buff_multibuffer_Write_rid_to_bin_V_Words(XBin_to_res_buff_multibuffer *InstancePtr, int offset, int *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_RID_TO_BIN_V_HIGH - XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_RID_TO_BIN_V_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Axilites_BaseAddress + XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_RID_TO_BIN_V_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XBin_to_res_buff_multibuffer_Read_rid_to_bin_V_Words(XBin_to_res_buff_multibuffer *InstancePtr, int offset, int *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_RID_TO_BIN_V_HIGH - XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_RID_TO_BIN_V_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Axilites_BaseAddress + XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_RID_TO_BIN_V_BASE + (offset + i)*4);
    }
    return length;
}

u32 XBin_to_res_buff_multibuffer_Write_rid_to_bin_V_Bytes(XBin_to_res_buff_multibuffer *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_RID_TO_BIN_V_HIGH - XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_RID_TO_BIN_V_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Axilites_BaseAddress + XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_RID_TO_BIN_V_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XBin_to_res_buff_multibuffer_Read_rid_to_bin_V_Bytes(XBin_to_res_buff_multibuffer *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_RID_TO_BIN_V_HIGH - XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_RID_TO_BIN_V_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Axilites_BaseAddress + XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_RID_TO_BIN_V_BASE + offset + i);
    }
    return length;
}

void XBin_to_res_buff_multibuffer_InterruptGlobalEnable(XBin_to_res_buff_multibuffer *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XBin_to_res_buff_multibuffer_WriteReg(InstancePtr->Axilites_BaseAddress, XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_GIE, 1);
}

void XBin_to_res_buff_multibuffer_InterruptGlobalDisable(XBin_to_res_buff_multibuffer *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XBin_to_res_buff_multibuffer_WriteReg(InstancePtr->Axilites_BaseAddress, XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_GIE, 0);
}

void XBin_to_res_buff_multibuffer_InterruptEnable(XBin_to_res_buff_multibuffer *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XBin_to_res_buff_multibuffer_ReadReg(InstancePtr->Axilites_BaseAddress, XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_IER);
    XBin_to_res_buff_multibuffer_WriteReg(InstancePtr->Axilites_BaseAddress, XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_IER, Register | Mask);
}

void XBin_to_res_buff_multibuffer_InterruptDisable(XBin_to_res_buff_multibuffer *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XBin_to_res_buff_multibuffer_ReadReg(InstancePtr->Axilites_BaseAddress, XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_IER);
    XBin_to_res_buff_multibuffer_WriteReg(InstancePtr->Axilites_BaseAddress, XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_IER, Register & (~Mask));
}

void XBin_to_res_buff_multibuffer_InterruptClear(XBin_to_res_buff_multibuffer *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XBin_to_res_buff_multibuffer_WriteReg(InstancePtr->Axilites_BaseAddress, XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_ISR, Mask);
}

u32 XBin_to_res_buff_multibuffer_InterruptGetEnabled(XBin_to_res_buff_multibuffer *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XBin_to_res_buff_multibuffer_ReadReg(InstancePtr->Axilites_BaseAddress, XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_IER);
}

u32 XBin_to_res_buff_multibuffer_InterruptGetStatus(XBin_to_res_buff_multibuffer *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XBin_to_res_buff_multibuffer_ReadReg(InstancePtr->Axilites_BaseAddress, XBIN_TO_RES_BUFF_MULTIBUFFER_AXILITES_ADDR_ISR);
}

