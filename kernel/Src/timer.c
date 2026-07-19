/******************************************************************************
 * File    : timer.c
 * Project : Embedded RTOS
 * Description : Software Timer Implementation
 ******************************************************************************/

#include <stddef.h>
#include "timer.h"

/******************************************************************************
 * Create Timer
 ******************************************************************************/

Status_t Timer_Create(
    Timer_t *timer,
    TimerMode_t mode,
    uint32_t period,
    TimerCallback_t callback,
    void *argument)
{
    if ((timer == NULL) ||
        (callback == NULL) ||
        (period == 0U))
    {
        return STATUS_ERROR;
    }

    timer->active = FALSE;
    timer->mode = mode;
    timer->period = period;
    timer->remaining = period;
    timer->callback = callback;
    timer->argument = argument;

    return STATUS_OK;
}

/******************************************************************************
 * Start Timer
 ******************************************************************************/

Status_t Timer_Start(
    Timer_t *timer)
{
    if (timer == NULL)
    {
        return STATUS_ERROR;
    }

    timer->remaining = timer->period;
    timer->active = TRUE;

    return STATUS_OK;
}

/******************************************************************************
 * Stop Timer
 ******************************************************************************/

Status_t Timer_Stop(
    Timer_t *timer)
{
    if (timer == NULL)
    {
        return STATUS_ERROR;
    }

    timer->active = FALSE;

    return STATUS_OK;
}

/******************************************************************************
 * Restart Timer
 ******************************************************************************/

Status_t Timer_Restart(
    Timer_t *timer)
{
    if (timer == NULL)
    {
        return STATUS_ERROR;
    }

    timer->remaining = timer->period;
    timer->active = TRUE;

    return STATUS_OK;
}

/******************************************************************************
 * Reset Timer
 ******************************************************************************/

Status_t Timer_Reset(
    Timer_t *timer)
{
    if (timer == NULL)
    {
        return STATUS_ERROR;
    }

    timer->remaining = timer->period;
    timer->active = FALSE;

    return STATUS_OK;
}

/******************************************************************************
 * Process Timer Tick
 ******************************************************************************/

void Timer_Tick(
    Timer_t *timer)
{
    if ((timer == NULL) || (timer->active == FALSE))
    {
        return;
    }

    if (timer->remaining > 0U)
    {
        timer->remaining--;
    }

    if (timer->remaining == 0U)
    {
        if (timer->callback != NULL)
        {
            timer->callback(timer->argument);
        }

        if (timer->mode == TIMER_PERIODIC)
        {
            timer->remaining = timer->period;
        }
        else
        {
            timer->active = FALSE;
        }
    }
}

/******************************************************************************
 * Timer Running State
 ******************************************************************************/

Bool_t Timer_IsRunning(
    Timer_t *timer)
{
    if (timer == NULL)
    {
        return FALSE;
    }

    return timer->active;
}