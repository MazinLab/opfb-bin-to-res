// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2.1 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
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

u32 XBin_to_res_Get_resmap_V_BaseAddress(XBin_to_res *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XBIN_TO_RES_CONTROL_ADDR_RESMAP_V_BASE);
}

u32 XBin_to_res_Get_resmap_V_HighAddress(XBin_to_res *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XBIN_TO_RES_CONTROL_ADDR_RESMAP_V_HIGH);
}

u32 XBin_to_res_Get_resmap_V_TotalBytes(XBin_to_res *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XBIN_TO_RES_CONTROL_ADDR_RESMAP_V_HIGH - XBIN_TO_RES_CONTROL_ADDR_RESMAP_V_BASE + 1);
}

u32 XBin_to_res_Get_resmap_V_BitWidth(XBin_to_res *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XBIN_TO_RES_CONTROL_WIDTH_RESMAP_V;
}

u32 XBin_to_res_Get_resmap_V_Depth(XBin_to_res *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XBIN_TO_RES_CONTROL_DEPTH_RESMAP_V;
}

u32 XBin_to_res_Write_resmap_V_Words(XBin_to_res *InstancePtr, int offset, int *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XBIN_TO_RES_CONTROL_ADDR_RESMAP_V_HIGH - XBIN_TO_RES_CONTROL_ADDR_RESMAP_V_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XBIN_TO_RES_CONTROL_ADDR_RESMAP_V_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XBin_to_res_Read_resmap_V_Words(XBin_to_res *InstancePtr, int offset, int *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XBIN_TO_RES_CONTROL_ADDR_RESMAP_V_HIGH - XBIN_TO_RES_CONTROL_ADDR_RESMAP_V_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XBIN_TO_RES_CONTROL_ADDR_RESMAP_V_BASE + (offset + i)*4);
    }
    return length;
}

u32 XBin_to_res_Write_resmap_V_Bytes(XBin_to_res *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XBIN_TO_RES_CONTROL_ADDR_RESMAP_V_HIGH - XBIN_TO_RES_CONTROL_ADDR_RESMAP_V_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XBIN_TO_RES_CONTROL_ADDR_RESMAP_V_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XBin_to_res_Read_resmap_V_Bytes(XBin_to_res *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XBIN_TO_RES_CONTROL_ADDR_RESMAP_V_HIGH - XBIN_TO_RES_CONTROL_ADDR_RESMAP_V_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XBIN_TO_RES_CONTROL_ADDR_RESMAP_V_BASE + offset + i);
    }
    return length;
}

