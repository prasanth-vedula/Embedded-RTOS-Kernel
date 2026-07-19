#ifndef SEMAPHORE_H
#define SEMAPHORE_H

/******************************************************************************
 * File    : semaphore.h
 * Project : Embedded RTOS
 * Description : Counting Semaphore Interface
 ******************************************************************************/

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * Semaphore Structure
 ******************************************************************************/

typedef struct
{
    volatile uint32_t count;
    uint32_t maxCount;

} Semaphore_t;

/******************************************************************************
 * API
 ******************************************************************************/

/* Initialize Semaphore */
Status_t Semaphore_Create(
    Semaphore_t *sem,
    uint32_t initialCount,
    uint32_t maxCount);

/* Acquire Semaphore */
Status_t Semaphore_Take(
    Semaphore_t *sem);

/* Release Semaphore */
Status_t Semaphore_Give(
    Semaphore_t *sem);

/* Reset Semaphore */
Status_t Semaphore_Reset(
    Semaphore_t *sem);

/* Get Current Count */
uint32_t Semaphore_GetCount(
    Semaphore_t *sem);

/* Check Availability */
Bool_t Semaphore_IsAvailable(
    Semaphore_t *sem);

#ifdef __cplusplus
}
#endif

#endif