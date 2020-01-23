// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2.1 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XBIN_TO_RES_BUFF_MULTIBUFFER_H
#define XBIN_TO_RES_BUFF_MULTIBUFFER_H

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
#include "xbin_to_res_buff_multibuffer_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
#else
typedef struct {
    u16 DeviceId;
    u32 Axilites_BaseAddress;
} XBin_to_res_buff_multibuffer_Config;
#endif

typedef struct {
    u32 Axilites_BaseAddress;
    u32 IsReady;
} XBin_to_res_buff_multibuffer;

typedef struct {
    u32 word_0;
    u32 word_1;
    u32 word_2;
} XBin_to_res_buff_multibuffer_Rid_to_bin_v;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XBin_to_res_buff_multibuffer_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XBin_to_res_buff_multibuffer_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XBin_to_res_buff_multibuffer_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XBin_to_res_buff_multibuffer_ReadReg(BaseAddress, RegOffset) \
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
int XBin_to_res_buff_multibuffer_Initialize(XBin_to_res_buff_multibuffer *InstancePtr, u16 DeviceId);
XBin_to_res_buff_multibuffer_Config* XBin_to_res_buff_multibuffer_LookupConfig(u16 DeviceId);
int XBin_to_res_buff_multibuffer_CfgInitialize(XBin_to_res_buff_multibuffer *InstancePtr, XBin_to_res_buff_multibuffer_Config *ConfigPtr);
#else
int XBin_to_res_buff_multibuffer_Initialize(XBin_to_res_buff_multibuffer *InstancePtr, const char* InstanceName);
int XBin_to_res_buff_multibuffer_Release(XBin_to_res_buff_multibuffer *InstancePtr);
#endif

void XBin_to_res_buff_multibuffer_Start(XBin_to_res_buff_multibuffer *InstancePtr);
u32 XBin_to_res_buff_multibuffer_IsDone(XBin_to_res_buff_multibuffer *InstancePtr);
u32 XBin_to_res_buff_multibuffer_IsIdle(XBin_to_res_buff_multibuffer *InstancePtr);
u32 XBin_to_res_buff_multibuffer_IsReady(XBin_to_res_buff_multibuffer *InstancePtr);
void XBin_to_res_buff_multibuffer_EnableAutoRestart(XBin_to_res_buff_multibuffer *InstancePtr);
void XBin_to_res_buff_multibuffer_DisableAutoRestart(XBin_to_res_buff_multibuffer *InstancePtr);

u32 XBin_to_res_buff_multibuffer_Get_rid_to_bin_V_BaseAddress(XBin_to_res_buff_multibuffer *InstancePtr);
u32 XBin_to_res_buff_multibuffer_Get_rid_to_bin_V_HighAddress(XBin_to_res_buff_multibuffer *InstancePtr);
u32 XBin_to_res_buff_multibuffer_Get_rid_to_bin_V_TotalBytes(XBin_to_res_buff_multibuffer *InstancePtr);
u32 XBin_to_res_buff_multibuffer_Get_rid_to_bin_V_BitWidth(XBin_to_res_buff_multibuffer *InstancePtr);
u32 XBin_to_res_buff_multibuffer_Get_rid_to_bin_V_Depth(XBin_to_res_buff_multibuffer *InstancePtr);
u32 XBin_to_res_buff_multibuffer_Write_rid_to_bin_V_Words(XBin_to_res_buff_multibuffer *InstancePtr, int offset, int *data, int length);
u32 XBin_to_res_buff_multibuffer_Read_rid_to_bin_V_Words(XBin_to_res_buff_multibuffer *InstancePtr, int offset, int *data, int length);
u32 XBin_to_res_buff_multibuffer_Write_rid_to_bin_V_Bytes(XBin_to_res_buff_multibuffer *InstancePtr, int offset, char *data, int length);
u32 XBin_to_res_buff_multibuffer_Read_rid_to_bin_V_Bytes(XBin_to_res_buff_multibuffer *InstancePtr, int offset, char *data, int length);

void XBin_to_res_buff_multibuffer_InterruptGlobalEnable(XBin_to_res_buff_multibuffer *InstancePtr);
void XBin_to_res_buff_multibuffer_InterruptGlobalDisable(XBin_to_res_buff_multibuffer *InstancePtr);
void XBin_to_res_buff_multibuffer_InterruptEnable(XBin_to_res_buff_multibuffer *InstancePtr, u32 Mask);
void XBin_to_res_buff_multibuffer_InterruptDisable(XBin_to_res_buff_multibuffer *InstancePtr, u32 Mask);
void XBin_to_res_buff_multibuffer_InterruptClear(XBin_to_res_buff_multibuffer *InstancePtr, u32 Mask);
u32 XBin_to_res_buff_multibuffer_InterruptGetEnabled(XBin_to_res_buff_multibuffer *InstancePtr);
u32 XBin_to_res_buff_multibuffer_InterruptGetStatus(XBin_to_res_buff_multibuffer *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
