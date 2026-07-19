/******************************************************************************
 * File    : timer_demo.c
 * Project : Embedded RTOS
 * Description : Software Timer Demonstration
 ******************************************************************************/

#include <stdio.h>

#include "kernel.h"
#include "timer.h"

/*----------------------------------------------------------
 * Timer Callback
 *---------------------------------------------------------*/
void TimerCallback(void *argument)
{
    printf(">>> Timer Callback Executed! Message: %s\n",
           (char *)argument);
}

/*----------------------------------------------------------
 * Main
 *---------------------------------------------------------*/
int main(void)
{
    Timer_t timer;

    printf("=========================================\n");
    printf("         RTOS Timer Demonstration\n");
    printf("=========================================\n\n");

    if (Kernel_Init() != STATUS_OK)
    {
        printf("Kernel initialization failed!\n");
        return -1;
    }

    if (Timer_Create(&timer,
                     TIMER_ONE_SHOT,
                     5,
                     TimerCallback,
                     "Hello RTOS") != STATUS_OK)
    {
        printf("Timer creation failed!\n");
        return -1;
    }

    printf("Timer created successfully.\n");

    if (Timer_Start(&timer) == STATUS_OK)
    {
        printf("Timer started.\n\n");
    }

    for (int tick = 1; tick <= 6; tick++)
    {
        printf("Tick %d\n", tick);

        Timer_Tick(&timer);

        if (Timer_IsRunning(&timer))
            printf("Timer Running\n");
        else
            printf("Timer Stopped\n");

        printf("\n");
    }

    printf("Restarting Timer...\n\n");

    Timer_Restart(&timer);

    for (int tick = 1; tick <= 6; tick++)
    {
        printf("Tick %d\n", tick);

        Timer_Tick(&timer);

        if (Timer_IsRunning(&timer))
            printf("Timer Running\n");
        else
            printf("Timer Stopped\n");

        printf("\n");
    }

    printf("Stopping Timer...\n");

    Timer_Stop(&timer);

    printf("Running Status : %s\n",
           Timer_IsRunning(&timer) ? "YES" : "NO");

    printf("\nTimer demonstration completed.\n");

    return 0;
}