#ifndef HOOKS_H
#define HOOKS_H

/******************************************************************************
 * File    : hooks.h
 * Project : Embedded RTOS
 * Description : RTOS Hook Functions
 ******************************************************************************/

#include "types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * Hook Functions
 ******************************************************************************/

/* Called when no task is ready to execute */
void Hook_Idle(void);

/* Called every system tick */
void Hook_Tick(void);

/* Called when memory allocation fails */
void Hook_MallocFailed(void);

/* Called when a stack overflow is detected */
void Hook_StackOverflow(void);

/* Called when an assertion fails */
void Hook_AssertFailed(
    const char *file,
    uint32_t line);

/* Called when a fatal kernel error occurs */
void Hook_FatalError(
    Status_t errorCode);

#ifdef __cplusplus
}
#endif

#endif