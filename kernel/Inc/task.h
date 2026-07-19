/**
 * @file task.h
 * @brief RTOS Task Management Interface
 *
 * Defines the Task Control Block (TCB),
 * task creation parameters, task states,
 * and public APIs used by the scheduler.
 *
 * Author : Vedula China Venkata Prasanth
 * Version : 1.0.0
 */

#ifndef TASK_H
#define TASK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"
#include "config.h"
#include "list.h"

#include <stdint.h>
#include <stdbool.h>

/*=========================================================
                    Task Constants
=========================================================*/

#define RTOS_MAX_TASK_NAME_LENGTH      32U

#define RTOS_INVALID_TASK_ID           0xFFFFFFFFU

/*=========================================================
                    Task Priority
=========================================================*/

typedef uint8_t TaskPriority_t;

/*=========================================================
                    Task Identifier
=========================================================*/

typedef uint32_t TaskID_t;

/*=========================================================
                    Stack Pointer
=========================================================*/

typedef StackType_t* StackPointer_t;

/*=========================================================
                    Task Control Block
=========================================================*/

typedef struct TaskControlBlock
{
    /* Task Identification */

    TaskID_t id;

    char name[RTOS_MAX_TASK_NAME_LENGTH];

    /* Task Entry */

    TaskFunction_t taskFunction;

    void *parameters;

    /* Stack */

    StackPointer_t stackBase;

    StackPointer_t stackPointer;

    uint32_t stackSize;

    /* Scheduling */

    TaskPriority_t priority;

    TaskState_t state;

    TickType_t wakeTick;

    TickType_t runtimeTicks;

    /* Linked List */

    ListNode_t listNode;

    /* Statistics */

    uint32_t contextSwitches;

    uint32_t cpuUsage;

    /* Flags */

    bool suspended;

    bool deleted;

} TaskControlBlock_t;

/*=========================================================
                Task Configuration Structure
=========================================================*/

typedef struct
{
    const char *taskName;

    TaskFunction_t taskFunction;

    void *taskParameter;

    TaskPriority_t priority;

    uint32_t stackSize;

} TaskConfig_t;

/*=========================================================
                    Task Information
=========================================================*/

typedef struct
{
    TaskID_t id;

    char name[RTOS_MAX_TASK_NAME_LENGTH];

    TaskPriority_t priority;

    TaskState_t state;

    uint32_t stackSize;

    uint32_t runtimeTicks;

    uint32_t contextSwitches;

} TaskInfo_t;

/*=========================================================
                    Public APIs
=========================================================*/

RTOS_Status_t Task_Create(
    const TaskConfig_t *config,
    TaskControlBlock_t **task);

RTOS_Status_t Task_Delete(
    TaskControlBlock_t *task);

RTOS_Status_t Task_Suspend(
    TaskControlBlock_t *task);

RTOS_Status_t Task_Resume(
    TaskControlBlock_t *task);

RTOS_Status_t Task_Delay(
    TickType_t ticks);

RTOS_Status_t Task_SetPriority(
    TaskControlBlock_t *task,
    TaskPriority_t priority);

TaskPriority_t Task_GetPriority(
    const TaskControlBlock_t *task);

TaskState_t Task_GetState(
    const TaskControlBlock_t *task);

TaskControlBlock_t *Task_GetCurrent(void);

/******************************************************************************
 * Get Current Running Task
 ******************************************************************************/
TaskControlBlock_t *Task_GetCurrentTask(void);

void Task_SetCurrentTask(TaskControlBlock_t *task);

TaskID_t Task_GetID(
    const TaskControlBlock_t *task);

const char *Task_GetName(
    const TaskControlBlock_t *task);

RTOS_Status_t Task_GetInfo(
    const TaskControlBlock_t *task,
    TaskInfo_t *info);

uint32_t Task_GetRuntime(
    const TaskControlBlock_t *task);

bool Task_IsReady(
    const TaskControlBlock_t *task);

bool Task_IsSuspended(
    const TaskControlBlock_t *task);

bool Task_IsDeleted(
    const TaskControlBlock_t *task);

/*=========================================================
                Internal Scheduler APIs
=========================================================*/

void Task_SystemInit(void);

void Task_UpdateRuntime(void);

void Task_TickHandler(void);

void Task_ContextSwitch(
    TaskControlBlock_t *nextTask);

TaskControlBlock_t *Task_SelectNext(void);

#ifdef __cplusplus
}
#endif

#endif /* TASK_H */