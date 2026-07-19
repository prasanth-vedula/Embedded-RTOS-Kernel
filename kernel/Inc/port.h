#ifndef PORT_H
#define PORT_H

/******************************************************************************
 * File    : port.h
 * Project : Embedded RTOS
 * Description : Hardware Port Interface
 ******************************************************************************/

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * Critical Section API
 ******************************************************************************/

/* Initialize CPU Port */
Status_t Port_Init(void);

/* Start First Task */
void Port_StartScheduler(void);

/* Perform Context Switch */
void Port_ContextSwitch(void);

/* Enter Critical Section */
void Port_EnterCritical(void);

/* Exit Critical Section */
void Port_ExitCritical(void);

/* Disable Interrupts */
void Port_DisableInterrupts(void);

/* Enable Interrupts */
void Port_EnableInterrupts(void);

/* System Tick Handler */
void Port_SysTickHandler(void);

/* Trigger PendSV (Context Switch) */
void Port_Yield(void);

#ifdef __cplusplus
}
#endif

#endif