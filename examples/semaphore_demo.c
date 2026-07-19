/******************************************************************************
 * File    : semaphore_demo.c
 * Project : Embedded RTOS
 * Description : Semaphore API Demonstration
 ******************************************************************************/

#include <stdio.h>

#include "kernel.h"
#include "semaphore.h"

int main(void)
{
    Semaphore_t sem;

    printf("=========================================\n");
    printf("      RTOS Semaphore Demonstration\n");
    printf("=========================================\n\n");

    /* Initialize Kernel */
    if (Kernel_Init() != STATUS_OK)
    {
        printf("Kernel initialization failed!\n");
        return -1;
    }

    /* Create Semaphore */
    if (Semaphore_Create(&sem, 1, 3) != STATUS_OK)
    {
        printf("Semaphore creation failed!\n");
        return -1;
    }

    printf("Semaphore created successfully.\n");
    printf("Initial Count : %u\n\n", Semaphore_GetCount(&sem));

    /* Take Semaphore */
    if (Semaphore_Take(&sem) == STATUS_OK)
    {
        printf("Semaphore Taken\n");
    }

    printf("Count : %u\n\n", Semaphore_GetCount(&sem));

    /* Give Semaphore */
    if (Semaphore_Give(&sem) == STATUS_OK)
    {
        printf("Semaphore Released\n");
    }

    printf("Count : %u\n\n", Semaphore_GetCount(&sem));

    /* Take Again */
    if (Semaphore_Take(&sem) == STATUS_OK)
    {
        printf("Semaphore Taken Again\n");
    }

    printf("Count : %u\n\n", Semaphore_GetCount(&sem));

    /* Reset */
    Semaphore_Reset(&sem);

    printf("Semaphore Reset\n");
    printf("Count : %u\n\n", Semaphore_GetCount(&sem));

    printf("Semaphore demonstration completed.\n");

    return 0;
}