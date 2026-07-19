/******************************************************************************
 * File    : hooks.c
 * Project : Embedded RTOS
 * Description : Default Hook Implementations
 ******************************************************************************/

#include "hooks.h"

/******************************************************************************
 * Idle Hook
 ******************************************************************************/

void Hook_Idle(void)
{
    /*
     * Executed when no task is ready.
     *
     * User may override this function to:
     *  - Enter low power mode
     *  - Execute background diagnostics
     *  - Measure CPU idle percentage
     */
}

/******************************************************************************
 * Tick Hook
 ******************************************************************************/

void Hook_Tick(void)
{
    /*
     * Executed every system tick.
     *
     * User may override for
     * periodic monitoring.
     */
}

/******************************************************************************
 * Memory Allocation Failure
 ******************************************************************************/

void Hook_MallocFailed(void)
{
    /*
     * Memory pool exhausted.
     */

    while (1)
    {
    }
}

/******************************************************************************
 * Stack Overflow
 ******************************************************************************/

void Hook_StackOverflow(void)
{
    /*
     * Stack corruption detected.
     */

    while (1)
    {
    }
}

/******************************************************************************
 * Assertion Failure
 ******************************************************************************/

void Hook_AssertFailed(
    const char *file,
    uint32_t line)
{
    (void)file;
    (void)line;

    /*
     * Useful breakpoint location
     * while debugging.
     */

    while (1)
    {
    }
}

/******************************************************************************
 * Fatal Kernel Error
 ******************************************************************************/

void Hook_FatalError(
    Status_t errorCode)
{
    (void)errorCode;

    /*
     * Kernel unrecoverable error.
     */

    while (1)
    {
    }
}