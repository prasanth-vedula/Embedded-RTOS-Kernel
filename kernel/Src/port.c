/******************************************************************************
 * File    : port.c
 * Project : Embedded RTOS
 * Description : Generic Hardware Port Layer
 ******************************************************************************/

#include "port.h"
#include "kernel.h"

/******************************************************************************
 * Static Variables
 ******************************************************************************/

static volatile uint32_t criticalNesting = 0U;

/******************************************************************************
 * Initialize Port
 ******************************************************************************/

Status_t Port_Init(void)
{
    criticalNesting = 0U;

    return STATUS_OK;
}

/******************************************************************************
 * Start Scheduler
 ******************************************************************************/

void Port_StartScheduler(void)
{
    Kernel_Start();

    while (1)
    {
        Kernel_Run();
    }
}

/******************************************************************************
 * Context Switch
 ******************************************************************************/

void Port_ContextSwitch(void)
{
    /* Reserved for architecture-specific implementation */
}

/******************************************************************************
 * Enter Critical Section
 ******************************************************************************/

void Port_EnterCritical(void)
{
    Port_DisableInterrupts();

    criticalNesting++;
}

/******************************************************************************
 * Exit Critical Section
 ******************************************************************************/

void Port_ExitCritical(void)
{
    if (criticalNesting > 0U)
    {
        criticalNesting--;
    }

    if (criticalNesting == 0U)
    {
        Port_EnableInterrupts();
    }
}

/******************************************************************************
 * Disable Interrupts
 ******************************************************************************/

void Port_DisableInterrupts(void)
{
    /*
     * Cortex-M implementation example:
     * __disable_irq();
     *
     * Generic implementation intentionally left empty.
     */
}

/******************************************************************************
 * Enable Interrupts
 ******************************************************************************/

void Port_EnableInterrupts(void)
{
    /*
     * Cortex-M implementation example:
     * __enable_irq();
     */
}

/******************************************************************************
 * System Tick Interrupt
 ******************************************************************************/

void Port_SysTickHandler(void)
{
    Kernel_Tick();
}

/******************************************************************************
 * Yield CPU
 ******************************************************************************/

void Port_Yield(void)
{
    Port_ContextSwitch();
}