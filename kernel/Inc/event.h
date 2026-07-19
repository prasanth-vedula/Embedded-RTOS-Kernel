#ifndef EVENT_H
#define EVENT_H

/******************************************************************************
 * File    : event.h
 * Project : Embedded RTOS
 * Description : Event Flags Interface
 ******************************************************************************/

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * Event Type
 ******************************************************************************/

typedef uint32_t EventFlags_t;

/******************************************************************************
 * Event Object
 ******************************************************************************/

typedef struct
{
    volatile EventFlags_t flags;

} Event_t;

/******************************************************************************
 * API
 ******************************************************************************/

/* Initialize Event */
Status_t Event_Create(
    Event_t *event);

/* Set Event Flags */
Status_t Event_Set(
    Event_t *event,
    EventFlags_t flags);

/* Clear Event Flags */
Status_t Event_Clear(
    Event_t *event,
    EventFlags_t flags);

/* Read Current Flags */
EventFlags_t Event_Get(
    Event_t *event);

/* Wait Until All Flags Are Set */
Bool_t Event_WaitAll(
    Event_t *event,
    EventFlags_t flags);

/* Wait Until Any Flag Is Set */
Bool_t Event_WaitAny(
    Event_t *event,
    EventFlags_t flags);

/* Reset Event */
Status_t Event_Reset(
    Event_t *event);

#ifdef __cplusplus
}
#endif

#endif