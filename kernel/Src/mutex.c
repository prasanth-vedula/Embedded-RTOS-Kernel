/******************************************************************************
 * File    : mutex.c
 * Project : Embedded RTOS
 * Description : Mutex Implementation
 ******************************************************************************/

#include "mutex.h"

/******************************************************************************
 * Create Mutex
 ******************************************************************************/

Status_t Mutex_Create(
    Mutex_t *mutex)
{
    if (mutex == NULL)
    {
        return STATUS_ERROR;
    }

    mutex->locked = FALSE;
    mutex->owner = NULL;

    return STATUS_OK;
}

/******************************************************************************
 * Lock Mutex
 ******************************************************************************/

Status_t Mutex_Lock(
    Mutex_t *mutex)
{
    if (mutex == NULL)
    {
        return STATUS_ERROR;
    }

    if (mutex->locked == TRUE)
    {
        return STATUS_ERROR;
    }

    mutex->locked = TRUE;

    /* Owner assignment will integrate with scheduler's current task */
    mutex->owner = Task_GetCurrentTask();

    return STATUS_OK;
}

/******************************************************************************
 * Unlock Mutex
 ******************************************************************************/

Status_t Mutex_Unlock(
    Mutex_t *mutex)
{
    if (mutex == NULL)
    {
        return STATUS_ERROR;
    }

    if (mutex->locked == FALSE)
    {
        return STATUS_ERROR;
    }

    /* Only the owner may unlock */
    if (mutex->owner != Task_GetCurrentTask())
    {
        return STATUS_ERROR;
    }

    mutex->locked = FALSE;
    mutex->owner = NULL;

    return STATUS_OK;
}

/******************************************************************************
 * Reset Mutex
 ******************************************************************************/

Status_t Mutex_Reset(
    Mutex_t *mutex)
{
    if (mutex == NULL)
    {
        return STATUS_ERROR;
    }

    mutex->locked = FALSE;
    mutex->owner = NULL;

    return STATUS_OK;
}

/******************************************************************************
 * Get Owner
 ******************************************************************************/

TaskControlBlock_t *Mutex_GetOwner(
    Mutex_t *mutex)
{
    if (mutex == NULL)
    {
        return NULL;
    }

    return mutex->owner;
}

/******************************************************************************
 * Check Lock State
 ******************************************************************************/

Bool_t Mutex_IsLocked(
    Mutex_t *mutex)
{
    if (mutex == NULL)
    {
        return FALSE;
    }

    return mutex->locked;
}