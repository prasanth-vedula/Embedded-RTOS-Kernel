#ifndef TIMER_H
#define TIMER_H

/******************************************************************************
 * File    : timer.h
 * Project : Embedded RTOS
 * Description : Software Timer Interface
 ******************************************************************************/

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * Timer Callback
 ******************************************************************************/

typedef void (*TimerCallback_t)(void *argument);

/******************************************************************************
 * Timer Mode
 ******************************************************************************/

typedef enum
{
    TIMER_ONE_SHOT = 0,
    TIMER_PERIODIC

} TimerMode_t;

/******************************************************************************
 * Timer Control Block
 ******************************************************************************/

typedef struct
{
    Bool_t active;

    TimerMode_t mode;

    uint32_t period;

    uint32_t remaining;

    TimerCallback_t callback;

    void *argument;

} Timer_t;

/******************************************************************************
 * API
 ******************************************************************************/

/* Create Timer */
Status_t Timer_Create(
    Timer_t *timer,
    TimerMode_t mode,
    uint32_t period,
    TimerCallback_t callback,
    void *argument);

/* Start Timer */
Status_t Timer_Start(
    Timer_t *timer);

/* Stop Timer */
Status_t Timer_Stop(
    Timer_t *timer);

/* Restart Timer */
Status_t Timer_Restart(
    Timer_t *timer);

/* Reset Timer */
Status_t Timer_Reset(
    Timer_t *timer);

/* Process Tick */
void Timer_Tick(
    Timer_t *timer);

/* Check Running */
Bool_t Timer_IsRunning(
    Timer_t *timer);

#ifdef __cplusplus
}
#endif

#endif