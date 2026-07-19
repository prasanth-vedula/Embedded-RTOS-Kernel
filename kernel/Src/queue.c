/******************************************************************************
 * File    : queue.c
 * Project : Embedded RTOS
 * Description : Queue Implementation
 ******************************************************************************/

#include <string.h>

#include "queue.h"

/******************************************************************************
 * Create Queue
 ******************************************************************************/

Status_t Queue_Create(
    Queue_t *queue,
    void *buffer,
    uint32_t itemSize,
    uint32_t length)
{
    if ((queue == NULL) || (buffer == NULL) ||
        (itemSize == 0U) || (length == 0U))
    {
        return STATUS_ERROR;
    }

    queue->buffer = (uint8_t *)buffer;
    queue->itemSize = itemSize;
    queue->length = length;

    queue->head = 0U;
    queue->tail = 0U;
    queue->count = 0U;

    return STATUS_OK;
}

/******************************************************************************
 * Reset Queue
 ******************************************************************************/

Status_t Queue_Reset(
    Queue_t *queue)
{
    if (queue == NULL)
    {
        return STATUS_ERROR;
    }

    queue->head = 0U;
    queue->tail = 0U;
    queue->count = 0U;

    return STATUS_OK;
}

/******************************************************************************
 * Send Item
 ******************************************************************************/

Status_t Queue_Send(
    Queue_t *queue,
    const void *item)
{
    if ((queue == NULL) || (item == NULL))
    {
        return STATUS_ERROR;
    }

    if (Queue_IsFull(queue))
    {
        return STATUS_ERROR;
    }

    memcpy(
        &queue->buffer[queue->tail * queue->itemSize],
        item,
        queue->itemSize);

    queue->tail++;

    if (queue->tail >= queue->length)
    {
        queue->tail = 0U;
    }

    queue->count++;

    return STATUS_OK;
}

/******************************************************************************
 * Receive Item
 ******************************************************************************/

Status_t Queue_Receive(
    Queue_t *queue,
    void *item)
{
    if ((queue == NULL) || (item == NULL))
    {
        return STATUS_ERROR;
    }

    if (Queue_IsEmpty(queue))
    {
        return STATUS_ERROR;
    }

    memcpy(
        item,
        &queue->buffer[queue->head * queue->itemSize],
        queue->itemSize);

    queue->head++;

    if (queue->head >= queue->length)
    {
        queue->head = 0U;
    }

    queue->count--;

    return STATUS_OK;
}

/******************************************************************************
 * Peek Item
 ******************************************************************************/

Status_t Queue_Peek(
    Queue_t *queue,
    void *item)
{
    if ((queue == NULL) || (item == NULL))
    {
        return STATUS_ERROR;
    }

    if (Queue_IsEmpty(queue))
    {
        return STATUS_ERROR;
    }

    memcpy(
        item,
        &queue->buffer[queue->head * queue->itemSize],
        queue->itemSize);

    return STATUS_OK;
}

/******************************************************************************
 * Queue Empty
 ******************************************************************************/

Bool_t Queue_IsEmpty(
    Queue_t *queue)
{
    if (queue == NULL)
    {
        return TRUE;
    }

    return (queue->count == 0U);
}

/******************************************************************************
 * Queue Full
 ******************************************************************************/

Bool_t Queue_IsFull(
    Queue_t *queue)
{
    if (queue == NULL)
    {
        return FALSE;
    }

    return (queue->count >= queue->length);
}

/******************************************************************************
 * Queue Count
 ******************************************************************************/

uint32_t Queue_Count(
    Queue_t *queue)
{
    if (queue == NULL)
    {
        return 0U;
    }

    return queue->count;
}

/******************************************************************************
 * Queue Free Space
 ******************************************************************************/

uint32_t Queue_SpacesAvailable(
    Queue_t *queue)
{
    if (queue == NULL)
    {
        return 0U;
    }

    return (queue->length - queue->count);
}