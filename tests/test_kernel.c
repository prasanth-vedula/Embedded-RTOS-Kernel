/******************************************************************************
 * File    : test_kernel.c
 * Project : Embedded RTOS
 * Description : Kernel Unit Test
 ******************************************************************************/

#include <stdio.h>

#include "kernel.h"

int main(void)
{
    Status_t status;

    printf("=========================================\n");
    printf("        RTOS Kernel Unit Test\n");
    printf("=========================================\n\n");

    printf("[TEST 1] Kernel Initialization\n");

    status = Kernel_Init();

    if (status == STATUS_OK)
    {
        printf("PASS : Kernel_Init()\n");
    }
    else
    {
        printf("FAIL : Kernel_Init()\n");
        return -1;
    }

    printf("\n");

    printf("[TEST 2] Kernel Start\n");

    status = Kernel_Start();

    if (status == STATUS_OK)
    {
        printf("PASS : Kernel_Start()\n");
    }
    else
    {
        printf("FAIL : Kernel_Start()\n");
    }

    printf("\n");

    printf("[TEST 3] Kernel Stop\n");

    status = Kernel_Stop();

    if (status == STATUS_OK)
    {
        printf("PASS : Kernel_Stop()\n");
    }
    else
    {
        printf("FAIL : Kernel_Stop()\n");
    }

    printf("\n=========================================\n");
    printf("Kernel Unit Test Completed Successfully\n");
    printf("=========================================\n");

    return 0;
}