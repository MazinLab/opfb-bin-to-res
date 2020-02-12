// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2.1 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XBIN_TO_RES_H
#define XBIN_TO_RES_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xbin_to_res_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
#else
typedef struct {
    u16 DeviceId;
    u32 Ctrl_BaseAddress;
} XBin_to_res_Config;
#endif

typedef struct {
    u32 Ctrl_BaseAddress;
    u32 IsReady;
} XBin_to_res;

typedef struct {
    u32 word_0;
    u32 word_1;
    u32 word_2;
} XBin_to_res_Resmap_v;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XBin_to_res_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XBin_to_res_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XBin_to_res_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XBin_to_res_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XBin_to_res_Initialize(XBin_to_res *InstancePtr, u16 DeviceId);
XBin_to_res_Config* XBin_to_res_LookupConfig(u16 DeviceId);
int XBin_to_res_CfgInitialize(XBin_to_res *InstancePtr, XBin_to_res_Config *ConfigPtr);
#else
int XBin_to_res_Initialize(XBin_to_res *InstancePtr, const char* InstanceName);
int XBin_to_res_Release(XBin_to_res *InstancePtr);
#endif


u32 XBin_to_res_Get_resmap_V_BaseAddress(XBin_to_res *InstancePtr);
u32 XBin_to_res_Get_resmap_V_HighAddress(XBin_to_res *InstancePtr);
u32 XBin_to_res_Get_resmap_V_TotalBytes(XBin_to_res *InstancePtr);
u32 XBin_to_res_Get_resmap_V_BitWidth(XBin_to_res *InstancePtr);
u32 XBin_to_res_Get_resmap_V_Depth(XBin_to_res *InstancePtr);
u32 XBin_to_res_Write_resmap_V_Words(XBin_to_res *InstancePtr, int offset, int *data, int length);
u32 XBin_to_res_Read_resmap_V_Words(XBin_to_res *InstancePtr, int offset, int *data, int length);
u32 XBin_to_res_Write_resmap_V_Bytes(XBin_to_res *InstancePtr, int offset, char *data, int length);
u32 XBin_to_res_Read_resmap_V_Bytes(XBin_to_res *InstancePtr, int offset, char *data, int length);

#ifdef __cplusplus
}
#endif

#endif
