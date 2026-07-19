#ifndef MUTEX_H
#define MUTEX_H

/******************************************************************************
 * File    : mutex.h
 * Project : Embedded RTOS
 * Description : Mutex Interface
 ******************************************************************************/

#include "types.h"
#include "task.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * Mutex Structure
 ******************************************************************************/

typedef struct
{
    volatile Bool_t locked;

    TaskControlBlock_t *owner;

} Mutex_t;

/******************************************************************************
 * API
 ******************************************************************************/

/* Create Mutex */
Status_t Mutex_Create(
    Mutex_t *mutex);

/* Lock Mutex */
Status_t Mutex_Lock(
    Mutex_t *mutex);

/* Unlock Mutex */
Status_t Mutex_Unlock(
    Mutex_t *mutex);

/* Reset Mutex */
Status_t Mutex_Reset(
    Mutex_t *mutex);

/* Get Owner */
TaskControlBlock_t *Mutex_GetOwner(
    Mutex_t *mutex);

/* Check Locked */
Bool_t Mutex_IsLocked(
    Mutex_t *mutex);

#ifdef __cplusplus
}
#endif

#endif