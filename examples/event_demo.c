/******************************************************************************
 * File    : event_demo.c
 * Project : Embedded RTOS
 * Description : Event Flags Demonstration
 ******************************************************************************/

#include <stdio.h>

#include "kernel.h"
#include "event.h"

#define EVENT_FLAG1    (1U << 0)
#define EVENT_FLAG2    (1U << 1)
#define EVENT_FLAG3    (1U << 2)

int main(void)
{
    Event_t event;

    printf("=========================================\n");
    printf("         RTOS Event Demonstration\n");
    printf("=========================================\n\n");

    if (Kernel_Init() != STATUS_OK)
    {
        printf("Kernel initialization failed!\n");
        return -1;
    }

    if (Event_Create(&event) != STATUS_OK)
    {
        printf("Event creation failed!\n");
        return -1;
    }

    printf("Event created successfully.\n");
    printf("Current Flags : 0x%08X\n\n", Event_Get(&event));

    /* Set Flag 1 */
    Event_Set(&event, EVENT_FLAG1);

    printf("Set FLAG1\n");
    printf("Flags : 0x%08X\n\n", Event_Get(&event));

    /* Set Flag 2 */
    Event_Set(&event, EVENT_FLAG2);

    printf("Set FLAG2\n");
    printf("Flags : 0x%08X\n\n", Event_Get(&event));

    /* Wait Any */
    if (Event_WaitAny(&event, EVENT_FLAG1 | EVENT_FLAG3))
    {
        printf("WaitAny() Success\n");
    }
    else
    {
        printf("WaitAny() Failed\n");
    }

    /* Wait All */
    if (Event_WaitAll(&event, EVENT_FLAG1 | EVENT_FLAG2))
    {
        printf("WaitAll() Success\n");
    }
    else
    {
        printf("WaitAll() Failed\n");
    }

    printf("\n");

    /* Clear FLAG1 */
    Event_Clear(&event, EVENT_FLAG1);

    printf("Clear FLAG1\n");
    printf("Flags : 0x%08X\n\n", Event_Get(&event));

    /* Reset Event */
    Event_Reset(&event);

    printf("Event Reset\n");
    printf("Flags : 0x%08X\n\n", Event_Get(&event));

    printf("Event demonstration completed.\n");

    return 0;
}