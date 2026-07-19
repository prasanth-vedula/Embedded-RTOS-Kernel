/******************************************************************************
 * File    : event.c
 * Project : Embedded RTOS
 * Description : Event Flags Implementation
 ******************************************************************************/

#include <stddef.h>
#include "event.h""

/******************************************************************************
 * Create Event
 ******************************************************************************/

Status_t Event_Create(
    Event_t *event)
{
    if (event == NULL)
    {
        return STATUS_ERROR;
    }

    event->flags = 0U;

    return STATUS_OK;
}

/******************************************************************************
 * Set Event Flags
 ******************************************************************************/

Status_t Event_Set(
    Event_t *event,
    EventFlags_t flags)
{
    if (event == NULL)
    {
        return STATUS_ERROR;
    }

    event->flags |= flags;

    return STATUS_OK;
}

/******************************************************************************
 * Clear Event Flags
 ******************************************************************************/

Status_t Event_Clear(
    Event_t *event,
    EventFlags_t flags)
{
    if (event == NULL)
    {
        return STATUS_ERROR;
    }

    event->flags &= ~flags;

    return STATUS_OK;
}

/******************************************************************************
 * Get Event Flags
 ******************************************************************************/

EventFlags_t Event_Get(
    Event_t *event)
{
    if (event == NULL)
    {
        return 0U;
    }

    return event->flags;
}

/******************************************************************************
 * Wait Until All Flags Are Set
 ******************************************************************************/

Bool_t Event_WaitAll(
    Event_t *event,
    EventFlags_t flags)
{
    if (event == NULL)
    {
        return FALSE;
    }

    return ((event->flags & flags) == flags);
}

/******************************************************************************
 * Wait Until Any Flag Is Set
 ******************************************************************************/

Bool_t Event_WaitAny(
    Event_t *event,
    EventFlags_t flags)
{
    if (event == NULL)
    {
        return FALSE;
    }

    return ((event->flags & flags) != 0U);
}

/******************************************************************************
 * Reset Event
 ******************************************************************************/

Status_t Event_Reset(
    Event_t *event)
{
    if (event == NULL)
    {
        return STATUS_ERROR;
    }

    event->flags = 0U;

    return STATUS_OK;
}