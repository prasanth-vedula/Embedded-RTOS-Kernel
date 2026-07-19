/******************************************************************************
 * File    : test_mutex.c
 * Project : Embedded RTOS
 * Description : Mutex Unit Test
 ******************************************************************************/

#include <stdio.h>

#include "kernel.h"
#include "mutex.h"

int main(void)
{
    Mutex_t mutex;

    printf("=========================================\n");
    printf("         RTOS Mutex Unit Test\n");
    printf("=========================================\n\n");

    if (Kernel_Init() == STATUS_OK)
        printf("PASS : Kernel_Init()\n");
    else
    {
        printf("FAIL : Kernel_Init()\n");
        return -1;
    }

    if (Mutex_Create(&mutex) == STATUS_OK)
        printf("PASS : Mutex_Create()\n");
    else
    {
        printf("FAIL : Mutex_Create()\n");
        return -1;
    }

    if (!Mutex_IsLocked(&mutex))
        printf("PASS : Initial Unlock State\n");
    else
        printf("FAIL : Initial Unlock State\n");

    if (Mutex_Lock(&mutex) == STATUS_OK)
        printf("PASS : Mutex_Lock()\n");
    else
        printf("FAIL : Mutex_Lock()\n");

    if (Mutex_IsLocked(&mutex))
        printf("PASS : Locked State\n");
    else
        printf("FAIL : Locked State\n");

    if (Mutex_Unlock(&mutex) == STATUS_OK)
        printf("PASS : Mutex_Unlock()\n");
    else
        printf("FAIL : Mutex_Unlock()\n");

    if (!Mutex_IsLocked(&mutex))
        printf("PASS : Unlock State\n");
    else
        printf("FAIL : Unlock State\n");

    if (Mutex_Reset(&mutex) == STATUS_OK)
        printf("PASS : Mutex_Reset()\n");
    else
        printf("FAIL : Mutex_Reset()\n");

    printf("\n=========================================\n");
    printf("Mutex Unit Test Completed Successfully\n");
    printf("=========================================\n");

    return 0;
}