#ifndef QUEUE_H
#define QUEUE_H

/******************************************************************************
 * File    : queue.h
 * Project : Embedded RTOS
 * Description : RTOS Queue Interface
 ******************************************************************************/

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * Queue Structure
 ******************************************************************************/

typedef struct QueueControlBlock
{
    uint8_t *buffer;

    uint32_t itemSize;

    uint32_t length;

    uint32_t head;

    uint32_t tail;

    uint32_t count;

} Queue_t;

/******************************************************************************
 * API
 ******************************************************************************/

/* Create Queue */
Status_t Queue_Create(
    Queue_t *queue,
    void *buffer,
    uint32_t itemSize,
    uint32_t length);

/* Reset Queue */
Status_t Queue_Reset(
    Queue_t *queue);

/* Send Item */
Status_t Queue_Send(
    Queue_t *queue,
    const void *item);

/* Receive Item */
Status_t Queue_Receive(
    Queue_t *queue,
    void *item);

/* Peek Item */
Status_t Queue_Peek(
    Queue_t *queue,
    void *item);

/* Check Empty */
Bool_t Queue_IsEmpty(
    Queue_t *queue);

/* Check Full */
Bool_t Queue_IsFull(
    Queue_t *queue);

/* Number of Stored Items */
uint32_t Queue_Count(
    Queue_t *queue);

/* Free Slots */
uint32_t Queue_SpacesAvailable(
    Queue_t *queue);

#ifdef __cplusplus
}
#endif

#endif