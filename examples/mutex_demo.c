/******************************************************************************
 * File    : mutex_demo.c
 * Project : Embedded RTOS
 * Description : Mutex API Demonstration
 ******************************************************************************/

#include <stdio.h>

#include "kernel.h"
#include "mutex.h"

int main(void)
{
    Mutex_t mutex;

    printf("=========================================\n");
    printf("         RTOS Mutex Demonstration\n");
    printf("=========================================\n\n");

    /* Initialize Kernel */
    if (Kernel_Init() != STATUS_OK)
    {
        printf("Kernel initialization failed!\n");
        return -1;
    }

    /* Create Mutex */
    if (Mutex_Create(&mutex) != STATUS_OK)
    {
        printf("Mutex creation failed!\n");
        return -1;
    }

    printf("Mutex created successfully.\n");
    printf("Locked : %s\n\n",
           Mutex_IsLocked(&mutex) ? "YES" : "NO");

    /* Lock */
    if (Mutex_Lock(&mutex) == STATUS_OK)
    {
        printf("Mutex Locked Successfully\n");
    }
    else
    {
        printf("Mutex Lock Failed\n");
    }

    printf("Locked : %s\n\n",
           Mutex_IsLocked(&mutex) ? "YES" : "NO");

    /* Unlock */
    if (Mutex_Unlock(&mutex) == STATUS_OK)
    {
        printf("Mutex Unlocked Successfully\n");
    }
    else
    {
        printf("Mutex Unlock Failed\n");
    }

    printf("Locked : %s\n\n",
           Mutex_IsLocked(&mutex) ? "YES" : "NO");

    /* Reset */
    if (Mutex_Reset(&mutex) == STATUS_OK)
    {
        printf("Mutex Reset Successfully\n");
    }

    printf("Locked : %s\n\n",
           Mutex_IsLocked(&mutex) ? "YES" : "NO");

    printf("Mutex demonstration completed.\n");

    return 0;
}