/******************************************************************************
 * File    : test_timer.c
 * Project : Embedded RTOS
 * Description : Timer Unit Test
 ******************************************************************************/

#include <stdio.h>

#include "kernel.h"
#include "timer.h"

static int callbackExecuted = 0;

void TestCallback(void *argument)
{
    (void)argument;
    callbackExecuted++;
}

int main(void)
{
    Timer_t timer;

    printf("=========================================\n");
    printf("         RTOS Timer Unit Test\n");
    printf("=========================================\n\n");

    if (Kernel_Init() == STATUS_OK)
        printf("PASS : Kernel_Init()\n");
    else
    {
        printf("FAIL : Kernel_Init()\n");
        return -1;
    }

    if (Timer_Create(&timer,
                     TIMER_ONE_SHOT,
                     5,
                     TestCallback,
                     NULL) == STATUS_OK)
        printf("PASS : Timer_Create()\n");
    else
    {
        printf("FAIL : Timer_Create()\n");
        return -1;
    }

    if (Timer_Start(&timer) == STATUS_OK)
        printf("PASS : Timer_Start()\n");
    else
        printf("FAIL : Timer_Start()\n");

    for(int i = 0; i < 5; i++)
        Timer_Tick(&timer);

    if(callbackExecuted == 1)
        printf("PASS : Timer Callback\n");
    else
        printf("FAIL : Timer Callback\n");

    if(!Timer_IsRunning(&timer))
        printf("PASS : Timer Stop After Expiry\n");
    else
        printf("FAIL : Timer Stop After Expiry\n");

    if(Timer_Restart(&timer) == STATUS_OK)
        printf("PASS : Timer_Restart()\n");
    else
        printf("FAIL : Timer_Restart()\n");

    if(Timer_Stop(&timer) == STATUS_OK)
        printf("PASS : Timer_Stop()\n");
    else
        printf("FAIL : Timer_Stop()\n");

    printf("\n=========================================\n");
    printf("Timer Unit Test Completed Successfully\n");
    printf("=========================================\n");

    return 0;
}