// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.2 (64-bit)
// Tool Version Limit: 2023.10
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef XNN_ACT_H
#define XNN_ACT_H

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
#include "xnn_act_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
#ifdef SDT
    char *Name;
#else
    u16 DeviceId;
#endif
    u64 Bus_a_BaseAddress;
} XNn_act_Config;
#endif

typedef struct {
    u64 Bus_a_BaseAddress;
    u32 IsReady;
} XNn_act;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XNn_act_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XNn_act_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XNn_act_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XNn_act_ReadReg(BaseAddress, RegOffset) \
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
#ifdef SDT
int XNn_act_Initialize(XNn_act *InstancePtr, UINTPTR BaseAddress);
XNn_act_Config* XNn_act_LookupConfig(UINTPTR BaseAddress);
#else
int XNn_act_Initialize(XNn_act *InstancePtr, u16 DeviceId);
XNn_act_Config* XNn_act_LookupConfig(u16 DeviceId);
#endif
int XNn_act_CfgInitialize(XNn_act *InstancePtr, XNn_act_Config *ConfigPtr);
#else
int XNn_act_Initialize(XNn_act *InstancePtr, const char* InstanceName);
int XNn_act_Release(XNn_act *InstancePtr);
#endif


void XNn_act_Set_params(XNn_act *InstancePtr, u32 Data);
u32 XNn_act_Get_params(XNn_act *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
