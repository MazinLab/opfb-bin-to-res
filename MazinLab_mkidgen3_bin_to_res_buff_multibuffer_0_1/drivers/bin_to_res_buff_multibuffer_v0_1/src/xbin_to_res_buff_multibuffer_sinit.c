// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2.1 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xbin_to_res_buff_multibuffer.h"

extern XBin_to_res_buff_multibuffer_Config XBin_to_res_buff_multibuffer_ConfigTable[];

XBin_to_res_buff_multibuffer_Config *XBin_to_res_buff_multibuffer_LookupConfig(u16 DeviceId) {
	XBin_to_res_buff_multibuffer_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XBIN_TO_RES_BUFF_MULTIBUFFER_NUM_INSTANCES; Index++) {
		if (XBin_to_res_buff_multibuffer_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XBin_to_res_buff_multibuffer_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XBin_to_res_buff_multibuffer_Initialize(XBin_to_res_buff_multibuffer *InstancePtr, u16 DeviceId) {
	XBin_to_res_buff_multibuffer_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XBin_to_res_buff_multibuffer_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XBin_to_res_buff_multibuffer_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

