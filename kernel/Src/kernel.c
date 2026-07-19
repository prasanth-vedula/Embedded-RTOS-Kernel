/******************************************************************************
 * File    : kernel.c
 * Project : Embedded RTOS
 * Author  : Prasanth
 ******************************************************************************/

#include "kernel.h"
#include "scheduler.h"
#include "task.h"
#include "config.h"

/******************************************************************************
 * Static Variables
 ******************************************************************************/

static volatile KernelState_t kernelState = KERNEL_STOPPED;
static volatile uint64_t kernelTickCount = 0;

/******************************************************************************
 * Kernel Initialization
 ******************************************************************************/

Status_t Kernel_Init(void)
{
    if (kernelState != KERNEL_STOPPED)
    {
        return STATUS_ERROR;
    }

    Scheduler_Init();

    kernelTickCount = 0;
    kernelState = KERNEL_INITIALIZED;

    return STATUS_OK;
}

/******************************************************************************
 * Start Kernel
 ******************************************************************************/

Status_t Kernel_Start(void)
{
    if (kernelState != KERNEL_INITIALIZED)
    {
        return STATUS_ERROR;
    }

    kernelState = KERNEL_RUNNING;

    Scheduler_Start();

    return STATUS_OK;
}

/******************************************************************************
 * Stop Kernel
 ******************************************************************************/

Status_t Kernel_Stop(void)
{
    if (kernelState == KERNEL_STOPPED)
    {
        return STATUS_ERROR;
    }

    kernelState = KERNEL_STOPPED;

    Scheduler_Stop();

    return STATUS_OK;
}

/******************************************************************************
 * Suspend Scheduler
 ******************************************************************************/

Status_t Kernel_Suspend(void)
{
    if (kernelState != KERNEL_RUNNING)
    {
        return STATUS_ERROR;
    }

    kernelState = KERNEL_SUSPENDED;

    return STATUS_OK;
}

/******************************************************************************
 * Resume Scheduler
 ******************************************************************************/

Status_t Kernel_Resume(void)
{
    if (kernelState != KERNEL_SUSPENDED)
    {
        return STATUS_ERROR;
    }

    kernelState = KERNEL_RUNNING;

    return STATUS_OK;
}

/******************************************************************************
 * Execute One Kernel Cycle
 ******************************************************************************/

void Kernel_Run(void)
{
    if (kernelState != KERNEL_RUNNING)
    {
        return;
    }

    Scheduler_Run();
}

/******************************************************************************
 * System Tick
 ******************************************************************************/

void Kernel_Tick(void)
{
    if (kernelState != KERNEL_RUNNING)
    {
        return;
    }

    kernelTickCount++;

    Scheduler_Tick();
}

/******************************************************************************
 * Delay Current Task
 ******************************************************************************/

Status_t Kernel_Delay(uint32_t ticks)
{
    return Task_Delay(ticks);
}

/******************************************************************************
 * Yield CPU
 ******************************************************************************/

void Kernel_Yield(void)
{
    Scheduler_Yield();
}

/******************************************************************************
 * Kernel State
 ******************************************************************************/

KernelState_t Kernel_GetState(void)
{
    return kernelState;
}

/******************************************************************************
 * Tick Counter
 ******************************************************************************/

uint64_t Kernel_GetTickCount(void)
{
    return kernelTickCount;
}