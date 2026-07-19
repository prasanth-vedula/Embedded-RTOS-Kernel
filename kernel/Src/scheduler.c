/**
 * @file scheduler.c
 * @brief RTOS Scheduler Implementation
 *
 * Author : Vedula China Venkata Prasanth
 * Version : 1.0.0
 */

#include "scheduler.h"
#include "kernel.h"
#include "task.h"
#include "config.h"

#include <stdio.h>
#include <string.h>
#include <stddef.h>

/*=========================================================
                Static Variables
=========================================================*/

static ReadyQueue_t g_readyQueue;

static SchedulerState_t g_schedulerState =
    SCHEDULER_STOPPED;

static SchedulerStatistics_t g_schedulerStats;

static TickType_t g_tickCount = 0U;

static bool g_schedulerLocked = false;

/*=========================================================
                Internal Functions
=========================================================*/

static void Scheduler_InsertByPriority(
    TaskControlBlock_t *task);

static TaskControlBlock_t *Scheduler_FindHighestPriority(void);

/*=========================================================
                Scheduler Initialization
=========================================================*/

RTOS_Status_t Scheduler_Init(void)
{
    List_Init(&g_readyQueue.readyList);

    g_readyQueue.readyTaskCount = 0U;

    memset(
        &g_schedulerStats,
        0,
        sizeof(SchedulerStatistics_t));

    g_tickCount = 0U;

    g_schedulerLocked = false;

    g_schedulerState = SCHEDULER_STOPPED;

    return RTOS_OK;
}

RTOS_Status_t Scheduler_Start(void)
{
    if (g_schedulerState == SCHEDULER_RUNNING)
    {
        return RTOS_OK;
    }

    g_schedulerState = SCHEDULER_RUNNING;

    return RTOS_OK;
}

RTOS_Status_t Scheduler_Stop(void)
{
    g_schedulerState = SCHEDULER_STOPPED;

    return RTOS_OK;
}

/*=========================================================
                Ready Queue Management
=========================================================*/

RTOS_Status_t Scheduler_AddTask(
    TaskControlBlock_t *task)
{
    if (task == NULL)
    {
        return RTOS_INVALID_PARAMETER;
    }

    Scheduler_InsertByPriority(task);

    g_readyQueue.readyTaskCount++;

    return RTOS_OK;
}

RTOS_Status_t Scheduler_RemoveTask(
    TaskControlBlock_t *task)
{
    if (task == NULL)
    {
        return RTOS_INVALID_PARAMETER;
    }

    List_Remove(
        &g_readyQueue.readyList,
        &task->listNode);

    if (g_readyQueue.readyTaskCount > 0U)
    {
        g_readyQueue.readyTaskCount--;
    }

    return RTOS_OK;
}

RTOS_Status_t Scheduler_UpdateTaskState(
    TaskControlBlock_t *task)
{
    if (task == NULL)
    {
        return RTOS_INVALID_PARAMETER;
    }

    Scheduler_ReorderReadyList();

    return RTOS_OK;
}

/*=========================================================
                Ready List Ordering
=========================================================*/

static void Scheduler_InsertByPriority(
    TaskControlBlock_t *task)
{
    ListNode_t *current;

    if (List_IsEmpty(&g_readyQueue.readyList))
    {
        List_PushBack(
            &g_readyQueue.readyList,
            &task->listNode);

        return;
    }

    current = List_Front(
        &g_readyQueue.readyList);

    while (current != NULL)
    {
        TaskControlBlock_t *existing =
            (TaskControlBlock_t *)current->data;

        if (task->priority >
            existing->priority)
        {
            List_InsertBefore(
                &g_readyQueue.readyList,
                current,
                &task->listNode);

            return;
        }

        current = current->next;
    }

    List_PushBack(
        &g_readyQueue.readyList,
        &task->listNode);
}

RTOS_Status_t Scheduler_ReorderReadyList(void)
{
    ListNode_t *current;

    List_t tempList;

    List_Init(&tempList);

    current = List_Front(
        &g_readyQueue.readyList);

    while (current != NULL)
    {
        ListNode_t *next = current->next;

        current->next = NULL;
        current->previous = NULL;

        List_PushBack(&tempList, current);

        current = next;
    }

    List_Clear(&g_readyQueue.readyList);

    current = List_Front(&tempList);

    while (current != NULL)
    {
        ListNode_t *next = current->next;

        current->next = NULL;
        current->previous = NULL;

        Scheduler_InsertByPriority(
            (TaskControlBlock_t *)current->data);

        current = next;
    }

    return RTOS_OK;
}
/*=========================================================
                Task Selection
=========================================================*/

static TaskControlBlock_t *Scheduler_FindHighestPriority(void)
{
    ListNode_t *node;

    node = List_Front(&g_readyQueue.readyList);

    while (node != NULL)
    {
        TaskControlBlock_t *task =
            (TaskControlBlock_t *)node->data;

        if (task->state == TASK_READY)
        {
            return task;
        }

        node = node->next;
    }

    return NULL;
}

TaskControlBlock_t *Scheduler_GetNextReadyTask(void)
{
    return Scheduler_FindHighestPriority();
}

TaskControlBlock_t *Scheduler_GetCurrentTask(void)
{
    return Task_GetCurrentTask();
}

/*=========================================================
                Scheduling Algorithm
=========================================================*/

void Scheduler_Schedule(void)
{
    TaskControlBlock_t *nextTask;

    if (g_schedulerLocked)
    {
        return;
    }

    if (g_schedulerState != SCHEDULER_RUNNING)
    {
        return;
    }

    nextTask = Scheduler_FindHighestPriority();

    if (nextTask == NULL)
    {
        return;
    }

    if (Task_GetCurrentTask() != nextTask)
    {
        /* Update the current task pointer in task.c using the setter */
        Task_SetCurrentTask(nextTask);
        
        Task_ContextSwitch(nextTask);

        g_schedulerStats.totalContextSwitches++;
    }
}

void Scheduler_RequestContextSwitch(void)
{
    Scheduler_Schedule();
}

/*=========================================================
                Tick Processing
=========================================================*/

void Scheduler_TickHandler(void)
{
    if (g_schedulerState != SCHEDULER_RUNNING)
    {
        return;
    }

    g_tickCount++;

    g_schedulerStats.totalTicks++;

    Task_TickHandler();

#if RTOS_USE_PREEMPTION

    Scheduler_Schedule();

#endif
}

TickType_t Scheduler_GetTickCount(void)
{
    return g_tickCount;
}

/*=========================================================
                Idle Task
=========================================================*/

void Scheduler_IdleTask(void *parameter)
{
    (void)parameter;

    while (1)
    {
        g_schedulerStats.idleTicks++;
    }
}

/*=========================================================
                Scheduler State
=========================================================*/

SchedulerState_t Scheduler_GetState(void)
{
    return g_schedulerState;
}

bool Scheduler_IsRunning(void)
{
    return (g_schedulerState == SCHEDULER_RUNNING);
}

/*=========================================================
                Scheduler Statistics
=========================================================*/

SchedulerStatistics_t Scheduler_GetStatistics(void)
{
    return g_schedulerStats;
}

void Scheduler_ResetStatistics(void)
{
    memset(
        &g_schedulerStats,
        0,
        sizeof(SchedulerStatistics_t));
}

void Scheduler_PrintStatistics(void)
{
#if RTOS_ENABLE_TRACE

    printf("\n=========================================\n");
    printf("        RTOS SCHEDULER STATISTICS\n");
    printf("=========================================\n");

    printf("Scheduler State      : %u\n",
            (unsigned int)g_schedulerState);

    printf("System Tick          : %u\n",
            (unsigned int)g_tickCount);

    printf("Ready Tasks          : %u\n",
            (unsigned int)g_readyQueue.readyTaskCount);

    printf("Context Switches     : %u\n",
            (unsigned int)g_schedulerStats.totalContextSwitches);

    printf("Total Scheduler Tick : %u\n",
            (unsigned int)g_schedulerStats.totalTicks);

    printf("Idle Tick            : %u\n",
            (unsigned int)g_schedulerStats.idleTicks);

    printf("=========================================\n");

#endif
}

/*=========================================================
                Scheduler Lock
=========================================================*/

void Scheduler_Lock(void)
{
    g_schedulerLocked = true;
}

void Scheduler_Unlock(void)
{
    g_schedulerLocked = false;
}

/*=========================================================
                Utility Functions
=========================================================*/

uint32_t Scheduler_GetReadyTaskCount(void)
{
    return g_readyQueue.readyTaskCount;
}

bool Scheduler_HasReadyTask(void)
{
    return (g_readyQueue.readyTaskCount > 0U);
}

void Scheduler_DumpReadyQueue(void)
{
#if RTOS_ENABLE_TRACE

    ListNode_t *node;

    printf("\n=========== READY QUEUE ===========\n");

    node = List_Front(&g_readyQueue.readyList);

    while (node != NULL)
    {
        TaskControlBlock_t *task =
            (TaskControlBlock_t *)node->data;

        printf("Task %-20s Priority %2u State %2u\n",
                task->name,
                (unsigned int)task->priority,
                (unsigned int)task->state);

        node = node->next;
    }

    printf("===================================\n");

#endif
}void Scheduler_Run(void)
{
    Scheduler_Schedule();
}

void Scheduler_Tick(void)
{
    Scheduler_TickHandler();
}

void Scheduler_Yield(void)
{
    Scheduler_RequestContextSwitch();
}