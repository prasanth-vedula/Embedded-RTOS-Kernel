/******************************************************************************
 * File    : semaphore.c
 * Project : Embedded RTOS
 * Description : Counting Semaphore Implementation
 ******************************************************************************/

#include "semaphore.h"

/******************************************************************************
 * Create Semaphore
 ******************************************************************************/

Status_t Semaphore_Create(
    Semaphore_t *sem,
    uint32_t initialCount,
    uint32_t maxCount)
{
    if ((sem == NULL) ||
        (maxCount == 0U) ||
        (initialCount > maxCount))
    {
        return STATUS_ERROR;
    }

    sem->count = initialCount;
    sem->maxCount = maxCount;

    return STATUS_OK;
}

/******************************************************************************
 * Take Semaphore
 ******************************************************************************/

Status_t Semaphore_Take(
    Semaphore_t *sem)
{
    if (sem == NULL)
    {
        return STATUS_ERROR;
    }

    if (sem->count == 0U)
    {
        return STATUS_ERROR;
    }

    sem->count--;

    return STATUS_OK;
}

/******************************************************************************
 * Give Semaphore
 ******************************************************************************/

Status_t Semaphore_Give(
    Semaphore_t *sem)
{
    if (sem == NULL)
    {
        return STATUS_ERROR;
    }

    if (sem->count >= sem->maxCount)
    {
        return STATUS_ERROR;
    }

    sem->count++;

    return STATUS_OK;
}

/******************************************************************************
 * Reset Semaphore
 ******************************************************************************/

Status_t Semaphore_Reset(
    Semaphore_t *sem)
{
    if (sem == NULL)
    {
        return STATUS_ERROR;
    }

    sem->count = 0U;

    return STATUS_OK;
}

/******************************************************************************
 * Get Semaphore Count
 ******************************************************************************/

uint32_t Semaphore_GetCount(
    Semaphore_t *sem)
{
    if (sem == NULL)
    {
        return 0U;
    }

    return sem->count;
}

/******************************************************************************
 * Check Availability
 ******************************************************************************/

Bool_t Semaphore_IsAvailable(
    Semaphore_t *sem)
{
    if (sem == NULL)
    {
        return FALSE;
    }

    return (sem->count > 0U);
}