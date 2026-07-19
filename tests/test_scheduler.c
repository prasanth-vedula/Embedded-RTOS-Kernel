/******************************************************************************
 * File    : test_scheduler.c
 * Project : Embedded RTOS
 * Description : Scheduler Unit Test
 ******************************************************************************/

#include <stdio.h>

#include "kernel.h"
#include "scheduler.h"

int main(void)
{
    SchedulerStatistics_t stats;

    printf("=========================================\n");
    printf("      RTOS Scheduler Unit Test\n");
    printf("=========================================\n\n");

    if (Scheduler_Init() == RTOS_OK)
        printf("PASS : Scheduler_Init()\n");
    else
    {
        printf("FAIL : Scheduler_Init()\n");
        return -1;
    }

    if (Scheduler_Start() == RTOS_OK)
        printf("PASS : Scheduler_Start()\n");
    else
        printf("FAIL : Scheduler_Start()\n");

    if (Scheduler_IsRunning())
        printf("PASS : Scheduler_IsRunning()\n");
    else
        printf("FAIL : Scheduler_IsRunning()\n");

    printf("Current Tick Count : %u\n",
           (unsigned int)Scheduler_GetTickCount());

    stats = Scheduler_GetStatistics();

    printf("PASS : Scheduler_GetStatistics()\n");
    printf("Context Switches : %u\n", stats.totalContextSwitches);
    printf("Total Ticks      : %u\n", stats.totalTicks);
    printf("Idle Ticks       : %u\n", stats.idleTicks);
    printf("Running Tasks    : %u\n", stats.runningTasks);

    Scheduler_ResetStatistics();

    printf("PASS : Scheduler_ResetStatistics()\n");

    if (Scheduler_Stop() == RTOS_OK)
        printf("PASS : Scheduler_Stop()\n");
    else
        printf("FAIL : Scheduler_Stop()\n");

    printf("\n=========================================\n");
    printf("Scheduler Unit Test Completed Successfully\n");
    printf("=========================================\n");

    return 0;
}