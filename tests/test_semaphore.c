/******************************************************************************
 * File    : test_semaphore.c
 * Project : Embedded RTOS
 * Description : Semaphore Unit Test
 ******************************************************************************/

#include <stdio.h>

#include "kernel.h"
#include "semaphore.h"

int main(void)
{
    Semaphore_t sem;

    printf("=========================================\n");
    printf("      RTOS Semaphore Unit Test\n");
    printf("=========================================\n\n");

    if (Kernel_Init() == STATUS_OK)
        printf("PASS : Kernel_Init()\n");
    else
    {
        printf("FAIL : Kernel_Init()\n");
        return -1;
    }

    if (Semaphore_Create(&sem, 1, 3) == STATUS_OK)
        printf("PASS : Semaphore_Create()\n");
    else
    {
        printf("FAIL : Semaphore_Create()\n");
        return -1;
    }

    if (Semaphore_GetCount(&sem) == 1)
        printf("PASS : Initial Count\n");
    else
        printf("FAIL : Initial Count\n");

    if (Semaphore_Take(&sem) == STATUS_OK)
        printf("PASS : Semaphore_Take()\n");
    else
        printf("FAIL : Semaphore_Take()\n");

    if (Semaphore_GetCount(&sem) == 0)
        printf("PASS : Count After Take\n");
    else
        printf("FAIL : Count After Take\n");

    if (Semaphore_Give(&sem) == STATUS_OK)
        printf("PASS : Semaphore_Give()\n");
    else
        printf("FAIL : Semaphore_Give()\n");

    if (Semaphore_GetCount(&sem) == 1)
        printf("PASS : Count After Give\n");
    else
        printf("FAIL : Count After Give\n");

    if (Semaphore_Reset(&sem) == STATUS_OK)
        printf("PASS : Semaphore_Reset()\n");
    else
        printf("FAIL : Semaphore_Reset()\n");

    printf("\n=========================================\n");
    printf("Semaphore Unit Test Completed Successfully\n");
    printf("=========================================\n");

    return 0;
}