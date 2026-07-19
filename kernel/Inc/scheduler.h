/**
 * @file scheduler.h
 * @brief RTOS Scheduler Interface
 *
 * Defines the scheduler APIs used for task management,
 * priority scheduling, round-robin scheduling,
 * context switching, and tick processing.
 *
 * Author : Vedula China Venkata Prasanth
 * Version : 1.0.0
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "task.h"
#include "list.h"
#include "config.h"
#include "types.h"

/*=========================================================
                    Scheduler States
=========================================================*/

typedef enum
{
    SCHEDULER_STOPPED = 0,

    SCHEDULER_RUNNING,

    SCHEDULER_SUSPENDED

} SchedulerState_t;

/*=========================================================
                    Ready Queue
=========================================================*/

typedef struct
{
    List_t readyList;

    uint32_t readyTaskCount;

} ReadyQueue_t;

/*=========================================================
                    Scheduler Statistics
=========================================================*/

typedef struct
{
    uint32_t totalContextSwitches;

    uint32_t totalTicks;

    uint32_t idleTicks;

    uint32_t runningTasks;

} SchedulerStatistics_t;

/*=========================================================
                    Initialization
=========================================================*/

RTOS_Status_t Scheduler_Init(void);

RTOS_Status_t Scheduler_Start(void);

RTOS_Status_t Scheduler_Stop(void);

/*=========================================================
                    Task Management
=========================================================*/

RTOS_Status_t Scheduler_AddTask(
    TaskControlBlock_t *task);

RTOS_Status_t Scheduler_RemoveTask(
    TaskControlBlock_t *task);

RTOS_Status_t Scheduler_UpdateTaskState(
    TaskControlBlock_t *task);

RTOS_Status_t Scheduler_ReorderReadyList(void);

/*=========================================================
                    Scheduling
=========================================================*/

TaskControlBlock_t *Scheduler_GetNextReadyTask(void);

TaskControlBlock_t *Scheduler_GetCurrentTask(void);

void Scheduler_Schedule(void);

void Scheduler_RequestContextSwitch(void);

/*=========================================================
                    Tick Processing
=========================================================*/

void Scheduler_TickHandler(void);

TickType_t Scheduler_GetTickCount(void);

/*=========================================================
                    Idle Task
=========================================================*/

void Scheduler_IdleTask(void *parameter);

/*=========================================================
                    Statistics
=========================================================*/

SchedulerStatistics_t Scheduler_GetStatistics(void);

void Scheduler_ResetStatistics(void);

void Scheduler_PrintStatistics(void);

/*=========================================================
                    Scheduler State
=========================================================*/

SchedulerState_t Scheduler_GetState(void);

bool Scheduler_IsRunning(void);

/*=========================================================
                    Internal Functions
=========================================================*/

void Scheduler_Lock(void);

void Scheduler_Unlock(void);
/*----------------------------------------------------------
 * Compatibility API
 *---------------------------------------------------------*/

void Scheduler_Run(void);

void Scheduler_Tick(void);

void Scheduler_Yield(void);

#ifdef __cplusplus
}
#endif

#endif /* SCHEDULER_H */