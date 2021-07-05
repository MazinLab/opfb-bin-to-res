// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xbin_to_res.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XBin_to_res_CfgInitialize(XBin_to_res *InstancePtr, XBin_to_res_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

u32 XBin_to_res_Get_rid_to_bin_BaseAddress(XBin_to_res *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XBIN_TO_RES_CONTROL_ADDR_RID_TO_BIN_BASE);
}

u32 XBin_to_res_Get_rid_to_bin_HighAddress(XBin_to_res *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XBIN_TO_RES_CONTROL_ADDR_RID_TO_BIN_HIGH);
}

u32 XBin_to_res_Get_rid_to_bin_TotalBytes(XBin_to_res *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XBIN_TO_RES_CONTROL_ADDR_RID_TO_BIN_HIGH - XBIN_TO_RES_CONTROL_ADDR_RID_TO_BIN_BASE + 1);
}

u32 XBin_to_res_Get_rid_to_bin_BitWidth(XBin_to_res *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XBIN_TO_RES_CONTROL_WIDTH_RID_TO_BIN;
}

u32 XBin_to_res_Get_rid_to_bin_Depth(XBin_to_res *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XBIN_TO_RES_CONTROL_DEPTH_RID_TO_BIN;
}

u32 XBin_to_res_Write_rid_to_bin_Words(XBin_to_res *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XBIN_TO_RES_CONTROL_ADDR_RID_TO_BIN_HIGH - XBIN_TO_RES_CONTROL_ADDR_RID_TO_BIN_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XBIN_TO_RES_CONTROL_ADDR_RID_TO_BIN_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XBin_to_res_Read_rid_to_bin_Words(XBin_to_res *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XBIN_TO_RES_CONTROL_ADDR_RID_TO_BIN_HIGH - XBIN_TO_RES_CONTROL_ADDR_RID_TO_BIN_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XBIN_TO_RES_CONTROL_ADDR_RID_TO_BIN_BASE + (offset + i)*4);
    }
    return length;
}

u32 XBin_to_res_Write_rid_to_bin_Bytes(XBin_to_res *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XBIN_TO_RES_CONTROL_ADDR_RID_TO_BIN_HIGH - XBIN_TO_RES_CONTROL_ADDR_RID_TO_BIN_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XBIN_TO_RES_CONTROL_ADDR_RID_TO_BIN_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XBin_to_res_Read_rid_to_bin_Bytes(XBin_to_res *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XBIN_TO_RES_CONTROL_ADDR_RID_TO_BIN_HIGH - XBIN_TO_RES_CONTROL_ADDR_RID_TO_BIN_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XBIN_TO_RES_CONTROL_ADDR_RID_TO_BIN_BASE + offset + i);
    }
    return length;
}

