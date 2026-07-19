/**
 * @file task.c
 * @brief RTOS Task Management Implementation
 *
 * Author : Vedula China Venkata Prasanth
 * Version : 1.0.0
 */

#include "task.h"
#include "scheduler.h"
#include "kernel.h"
#include "config.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

/*=========================================================
                Static Variables
=========================================================*/

static TaskControlBlock_t g_taskTable[RTOS_MAX_TASKS];

static uint32_t g_taskCount = 0U;

static TaskID_t g_nextTaskID = 1U;

static TaskControlBlock_t *g_currentTask = NULL;

/*=========================================================
                Internal Helper Functions
=========================================================*/

static void Task_ResetTCB(TaskControlBlock_t *task);

static RTOS_Status_t Task_AllocateStack(
    TaskControlBlock_t *task,
    uint32_t stackSize);

static void Task_FreeStack(
    TaskControlBlock_t *task);

static bool Task_IsValidPriority(
    TaskPriority_t priority);

static bool Task_IsValidHandle(
    const TaskControlBlock_t *task);

static TaskControlBlock_t *Task_FindFreeSlot(void);

/*=========================================================
                Internal Helpers
=========================================================*/

static void Task_ResetTCB(TaskControlBlock_t *task)
{
    if (task == NULL)
    {
        return;
    }

    memset(task, 0, sizeof(TaskControlBlock_t));

    task->id = RTOS_INVALID_TASK_ID;
    task->priority = RTOS_DEFAULT_TASK_PRIORITY;
    task->state = TASK_TERMINATED;
}

static bool Task_IsValidPriority(TaskPriority_t priority)
{
    return (priority <= RTOS_MAX_PRIORITY);
}

static bool Task_IsValidHandle(
    const TaskControlBlock_t *task)
{
    if (task == NULL)
    {
        return false;
    }

    if (task->id == RTOS_INVALID_TASK_ID)
    {
        return false;
    }

    return true;
}

static TaskControlBlock_t *Task_FindFreeSlot(void)
{
    uint32_t i;

    for (i = 0; i < RTOS_MAX_TASKS; i++)
    {
        if (g_taskTable[i].id == RTOS_INVALID_TASK_ID)
        {
            return &g_taskTable[i];
        }
    }

    return NULL;
}

/*=========================================================
                Stack Management
=========================================================*/

static RTOS_Status_t Task_AllocateStack(
    TaskControlBlock_t *task,
    uint32_t stackSize)
{
    if (task == NULL)
    {
        return RTOS_INVALID_PARAMETER;
    }

    task->stackBase =
        (StackPointer_t)malloc(
            stackSize * sizeof(StackType_t));

    if (task->stackBase == NULL)
    {
        return RTOS_OUT_OF_MEMORY;
    }

    task->stackPointer = task->stackBase;

    task->stackSize = stackSize;

    return RTOS_OK;
}

static void Task_FreeStack(
    TaskControlBlock_t *task)
{
    if (task == NULL)
    {
        return;
    }

    if (task->stackBase != NULL)
    {
        free(task->stackBase);
    }

    task->stackBase = NULL;
    task->stackPointer = NULL;
    task->stackSize = 0U;
}

/*=========================================================
                Kernel Initialization
=========================================================*/

void Task_SystemInit(void)
{
    uint32_t i;

    for (i = 0; i < RTOS_MAX_TASKS; i++)
    {
        Task_ResetTCB(&g_taskTable[i]);
    }

    g_taskCount = 0U;

    g_nextTaskID = 1U;

    g_currentTask = NULL;
}

/*=========================================================
                Task Creation
=========================================================*/

RTOS_Status_t Task_Create(
    const TaskConfig_t *config,
    TaskControlBlock_t **task)
{
    TaskControlBlock_t *newTask;

    RTOS_Status_t status;

    if ((config == NULL) || (task == NULL))
    {
        return RTOS_INVALID_PARAMETER;
    }

    if (g_taskCount >= RTOS_MAX_TASKS)
    {
        return RTOS_OUT_OF_MEMORY;
    }

    if (!Task_IsValidPriority(config->priority))
    {
        return RTOS_INVALID_PARAMETER;
    }

    newTask = Task_FindFreeSlot();

    if (newTask == NULL)
    {
        return RTOS_OUT_OF_MEMORY;
    }

    Task_ResetTCB(newTask);

    status = Task_AllocateStack(
        newTask,
        config->stackSize);

    if (status != RTOS_OK)
    {
        return status;
    }

    newTask->id = g_nextTaskID++;

    strncpy(
        newTask->name,
        config->taskName,
        RTOS_MAX_TASK_NAME_LENGTH - 1U);

    newTask->taskFunction = config->taskFunction;

    newTask->parameters = config->taskParameter;

    newTask->priority = config->priority;

    newTask->state = TASK_READY;

    newTask->runtimeTicks = 0U;

    newTask->contextSwitches = 0U;

    newTask->cpuUsage = 0U;

    newTask->deleted = false;

    newTask->suspended = false;

    newTask->listNode.data = newTask;

    g_taskCount++;

    *task = newTask;

    Scheduler_AddTask(newTask);

    return RTOS_OK;
}
/*=========================================================
                Task Deletion
=========================================================*/

RTOS_Status_t Task_Delete(
    TaskControlBlock_t *task)
{
    if (!Task_IsValidHandle(task))
    {
        return RTOS_INVALID_PARAMETER;
    }

    Scheduler_RemoveTask(task);

    Task_FreeStack(task);

    task->deleted = true;
    task->state = TASK_TERMINATED;
    task->id = RTOS_INVALID_TASK_ID;

    if (g_taskCount > 0U)
    {
        g_taskCount--;
    }

    return RTOS_OK;
}

/*=========================================================
                Task Suspend
=========================================================*/

RTOS_Status_t Task_Suspend(
    TaskControlBlock_t *task)
{
    if (!Task_IsValidHandle(task))
    {
        return RTOS_INVALID_PARAMETER;
    }

    if (task->state == TASK_SUSPENDED)
    {
        return RTOS_OK;
    }

    task->state = TASK_SUSPENDED;
    task->suspended = true;

    Scheduler_UpdateTaskState(task);

    return RTOS_OK;
}

/*=========================================================
                Task Resume
=========================================================*/

RTOS_Status_t Task_Resume(
    TaskControlBlock_t *task)
{
    if (!Task_IsValidHandle(task))
    {
        return RTOS_INVALID_PARAMETER;
    }

    task->state = TASK_READY;
    task->suspended = false;

    Scheduler_UpdateTaskState(task);

    return RTOS_OK;
}

/*=========================================================
                Task Delay
=========================================================*/

RTOS_Status_t Task_Delay(
    TickType_t ticks)
{
    if (g_currentTask == NULL)
    {
        return RTOS_ERROR;
    }

    g_currentTask->wakeTick =
        Kernel_GetTickCount() + ticks;

    g_currentTask->state = TASK_SLEEPING;

    Scheduler_UpdateTaskState(g_currentTask);

    Scheduler_RequestContextSwitch();

    return RTOS_OK;
}

/*=========================================================
                Priority APIs
=========================================================*/

RTOS_Status_t Task_SetPriority(
    TaskControlBlock_t *task,
    TaskPriority_t priority)
{
    if (!Task_IsValidHandle(task))
    {
        return RTOS_INVALID_PARAMETER;
    }

    if (!Task_IsValidPriority(priority))
    {
        return RTOS_INVALID_PARAMETER;
    }

    task->priority = priority;

    Scheduler_ReorderReadyList();

    return RTOS_OK;
}

TaskPriority_t Task_GetPriority(
    const TaskControlBlock_t *task)
{
    if (!Task_IsValidHandle(task))
    {
        return RTOS_MIN_PRIORITY;
    }

    return task->priority;
}

/*=========================================================
                Current Task
=========================================================*/

TaskControlBlock_t *Task_GetCurrent(void)
{
    return g_currentTask;
}

/******************************************************************************
 * Get Current Running Task
 ******************************************************************************/
TaskControlBlock_t *Task_GetCurrentTask(void)
{
    return g_currentTask;
}

void Task_SetCurrentTask(TaskControlBlock_t *task)
{
    g_currentTask = task;
}

TaskID_t Task_GetID(
    const TaskControlBlock_t *task)
{
    if (!Task_IsValidHandle(task))
    {
        return RTOS_INVALID_TASK_ID;
    }

    return task->id;
}

const char *Task_GetName(
    const TaskControlBlock_t *task)
{
    if (!Task_IsValidHandle(task))
    {
        return "";
    }

    return task->name;
}

/*=========================================================
                Task State
=========================================================*/

TaskState_t Task_GetState(
    const TaskControlBlock_t *task)
{
    if (!Task_IsValidHandle(task))
    {
        return TASK_TERMINATED;
    }

    return task->state;
}

bool Task_IsReady(
    const TaskControlBlock_t *task)
{
    return (Task_GetState(task) == TASK_READY);
}

bool Task_IsSuspended(
    const TaskControlBlock_t *task)
{
    if (!Task_IsValidHandle(task))
    {
        return false;
    }

    return task->suspended;
}

bool Task_IsDeleted(
    const TaskControlBlock_t *task)
{
    if (!Task_IsValidHandle(task))
    {
        return true;
    }

    return task->deleted;
}
/*=========================================================
                Runtime Statistics
=========================================================*/

uint32_t Task_GetRuntime(
    const TaskControlBlock_t *task)
{
    if (!Task_IsValidHandle(task))
    {
        return 0U;
    }

    return task->runtimeTicks;
}

RTOS_Status_t Task_GetInfo(
    const TaskControlBlock_t *task,
    TaskInfo_t *info)
{
    if ((!Task_IsValidHandle(task)) || (info == NULL))
    {
        return RTOS_INVALID_PARAMETER;
    }

    memset(info, 0, sizeof(TaskInfo_t));

    info->id = task->id;

    strncpy(
        info->name,
        task->name,
        RTOS_MAX_TASK_NAME_LENGTH);

    info->priority = task->priority;

    info->state = task->state;

    info->stackSize = task->stackSize;

    info->runtimeTicks = task->runtimeTicks;

    info->contextSwitches = task->contextSwitches;

    return RTOS_OK;
}

/*=========================================================
                Runtime Tick Update
=========================================================*/

void Task_UpdateRuntime(void)
{
    if (g_currentTask == NULL)
    {
        return;
    }

    g_currentTask->runtimeTicks++;
}

/*=========================================================
                Tick Handler
=========================================================*/

void Task_TickHandler(void)
{
    uint32_t i;

    Task_UpdateRuntime();

    for (i = 0U; i < RTOS_MAX_TASKS; i++)
    {
        TaskControlBlock_t *task = &g_taskTable[i];

        if ((task->id != RTOS_INVALID_TASK_ID) &&
            (task->state == TASK_SLEEPING))
        {
            if (Kernel_GetTickCount() >= task->wakeTick)
            {
                task->state = TASK_READY;

                Scheduler_UpdateTaskState(task);
            }
        }
    }
}

/*=========================================================
                Context Switching
=========================================================*/

void Task_ContextSwitch(
    TaskControlBlock_t *nextTask)
{
    if (!Task_IsValidHandle(nextTask))
    {
        return;
    }

    if (g_currentTask != NULL)
    {
        if (g_currentTask->state == TASK_RUNNING)
        {
            g_currentTask->state = TASK_READY;
        }
    }

    g_currentTask = nextTask;

    g_currentTask->state = TASK_RUNNING;

    g_currentTask->contextSwitches++;
}

/*=========================================================
                Scheduler Support
=========================================================*/

TaskControlBlock_t *Task_SelectNext(void)
{
    return Scheduler_GetNextReadyTask();
}

/*=========================================================
                Debug Statistics
=========================================================*/

uint32_t Task_GetTaskCount(void)
{
    return g_taskCount;
}

void Task_PrintStatistics(void)
{
#if RTOS_ENABLE_TRACE

    uint32_t i;

    printf("\n============================================\n");
    printf("        RTOS TASK STATISTICS\n");
    printf("============================================\n");

    printf("Total Tasks : %u\n\n",
            (unsigned int)g_taskCount);

    for (i = 0U; i < RTOS_MAX_TASKS; i++)
    {
        TaskControlBlock_t *task = &g_taskTable[i];

        if (task->id == RTOS_INVALID_TASK_ID)
        {
            continue;
        }

        printf("Task ID          : %u\n",
               (unsigned int)task->id);

        printf("Name             : %s\n",
               task->name);

        printf("Priority         : %u\n",
               (unsigned int)task->priority);

        printf("Runtime Ticks    : %u\n",
               (unsigned int)task->runtimeTicks);

        printf("Context Switches : %u\n",
               (unsigned int)task->contextSwitches);

        printf("--------------------------------------------\n");
    }

#endif
}