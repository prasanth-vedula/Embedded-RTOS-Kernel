#ifndef KERNEL_H
#define KERNEL_H

/******************************************************************************
 * File    : kernel.h
 * Project : Embedded RTOS
 * Author  : Prasanth
 ******************************************************************************/

#include "types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * Kernel State
 ******************************************************************************/

typedef enum
{
    KERNEL_STOPPED = 0,
    KERNEL_INITIALIZED,
    KERNEL_RUNNING,
    KERNEL_SUSPENDED
} KernelState_t;

/******************************************************************************
 * Public API
 ******************************************************************************/

/* Initialize kernel */
Status_t Kernel_Init(void);

/* Start scheduler */
Status_t Kernel_Start(void);

/* Stop scheduler */
Status_t Kernel_Stop(void);

/* Suspend scheduler */
Status_t Kernel_Suspend(void);

/* Resume scheduler */
Status_t Kernel_Resume(void);

/* Execute one scheduler cycle */
void Kernel_Run(void);

/* Tick handler */
void Kernel_Tick(void);

/* Delay current task */
Status_t Kernel_Delay(uint32_t ticks);

/* Yield CPU */
void Kernel_Yield(void);

/* Get current state */
KernelState_t Kernel_GetState(void);

/* Kernel uptime */
uint64_t Kernel_GetTickCount(void);

#ifdef __cplusplus
}
#endif

#endif