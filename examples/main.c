#include <stdio.h>
#include "kernel.h"

int main(void)
{
    printf("=====================================\n");
    printf("   Embedded RTOS Kernel Test\n");
    printf("=====================================\n\n");

    if (Kernel_Init() == STATUS_OK)
    {
        printf("Kernel initialized successfully.\n");
    }
    else
    {
        printf("Kernel initialization failed.\n");
        return -1;
    }

    printf("RTOS kernel compiled successfully!\n");

    return 0;
}