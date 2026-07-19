/******************************************************************************
 * File    : test_event.c
 * Project : Embedded RTOS
 * Description : Event Unit Test
 ******************************************************************************/

#include <stdio.h>

#include "kernel.h"
#include "event.h"

#define FLAG1 (1U << 0)
#define FLAG2 (1U << 1)

int main(void)
{
    Event_t event;

    printf("=========================================\n");
    printf("         RTOS Event Unit Test\n");
    printf("=========================================\n\n");

    if (Kernel_Init() == STATUS_OK)
        printf("PASS : Kernel_Init()\n");
    else
    {
        printf("FAIL : Kernel_Init()\n");
        return -1;
    }

    if (Event_Create(&event) == STATUS_OK)
        printf("PASS : Event_Create()\n");
    else
    {
        printf("FAIL : Event_Create()\n");
        return -1;
    }

    if (Event_Get(&event) == 0)
        printf("PASS : Initial Flags\n");
    else
        printf("FAIL : Initial Flags\n");

    Event_Set(&event, FLAG1);

    if (Event_Get(&event) == FLAG1)
        printf("PASS : Event_Set()\n");
    else
        printf("FAIL : Event_Set()\n");

    if (Event_WaitAny(&event, FLAG1))
        printf("PASS : Event_WaitAny()\n");
    else
        printf("FAIL : Event_WaitAny()\n");

    Event_Set(&event, FLAG2);

    if (Event_WaitAll(&event, FLAG1 | FLAG2))
        printf("PASS : Event_WaitAll()\n");
    else
        printf("FAIL : Event_WaitAll()\n");

    Event_Clear(&event, FLAG1);

    if (Event_Get(&event) == FLAG2)
        printf("PASS : Event_Clear()\n");
    else
        printf("FAIL : Event_Clear()\n");

    if (Event_Reset(&event) == STATUS_OK)
        printf("PASS : Event_Reset()\n");
    else
        printf("FAIL : Event_Reset()\n");

    printf("\n=========================================\n");
    printf("Event Unit Test Completed Successfully\n");
    printf("=========================================\n");

    return 0;
}