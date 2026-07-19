/**
 * @file config.h
 * @brief RTOS Kernel Configuration File
 *
 * This file contains all configurable parameters
 * for the Embedded RTOS Kernel.
 *
 * Author : Vedula China Venkata Prasanth
 * Version: 1.0.0
 */

#ifndef CONFIG_H
#define CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"

/*=========================================================
                    Kernel Information
=========================================================*/

#define RTOS_KERNEL_NAME                "Embedded RTOS Kernel"

#define RTOS_VERSION_STRING             "1.0.0"

/*=========================================================
                    CPU Configuration
=========================================================*/

#define RTOS_CPU_CLOCK_HZ               (72000000UL)

#define RTOS_TICK_RATE_HZ               (1000U)

#define RTOS_TICK_PERIOD_MS             (1000U / RTOS_TICK_RATE_HZ)

/*=========================================================
                    Scheduler Configuration
=========================================================*/

#define RTOS_USE_PREEMPTION             (1U)

#define RTOS_USE_ROUND_ROBIN            (1U)

#define RTOS_TIME_SLICE_TICKS           (10U)

#define RTOS_MAX_TASKS                  (32U)

#define RTOS_IDLE_TASK_PRIORITY         (0U)

#define RTOS_DEFAULT_TASK_PRIORITY      (5U)

/*=========================================================
                    Stack Configuration
=========================================================*/

#define RTOS_MIN_STACK_SIZE             (256U)

#define RTOS_DEFAULT_STACK_SIZE         (512U)

#define RTOS_IDLE_TASK_STACK_SIZE       (256U)

/*=========================================================
                    Queue Configuration
=========================================================*/

#define RTOS_MAX_QUEUES                 (16U)

#define RTOS_MAX_QUEUE_LENGTH           (128U)

/*=========================================================
                    Semaphore Configuration
=========================================================*/

#define RTOS_MAX_SEMAPHORES             (16U)

/*=========================================================
                    Mutex Configuration
=========================================================*/

#define RTOS_MAX_MUTEXES                (16U)

#define RTOS_USE_PRIORITY_INHERITANCE   (1U)

/*=========================================================
                    Timer Configuration
=========================================================*/

#define RTOS_MAX_TIMERS                 (16U)

#define RTOS_TIMER_TASK_PRIORITY        (8U)

/*=========================================================
                    Memory Configuration
=========================================================*/

#define RTOS_USE_STATIC_MEMORY          (1U)

#define RTOS_USE_DYNAMIC_MEMORY         (0U)

/*=========================================================
                    Debug Configuration
=========================================================*/

#define RTOS_ENABLE_ASSERT              (1U)

#define RTOS_ENABLE_TRACE               (1U)

#define RTOS_ENABLE_RUNTIME_STATS       (1U)

/*=========================================================
                    API Configuration
=========================================================*/

#define RTOS_INCLUDE_TASK_DELETE        (1U)

#define RTOS_INCLUDE_TASK_DELAY         (1U)

#define RTOS_INCLUDE_QUEUE              (1U)

#define RTOS_INCLUDE_SEMAPHORE          (1U)

#define RTOS_INCLUDE_MUTEX              (1U)

#define RTOS_INCLUDE_TIMER              (1U)

/*=========================================================
                    Hook Functions
=========================================================*/

#define RTOS_USE_IDLE_HOOK              (0U)

#define RTOS_USE_TICK_HOOK              (0U)

#define RTOS_USE_MALLOC_FAILED_HOOK     (0U)

#define RTOS_USE_STACK_OVERFLOW_HOOK    (0U)

/*=========================================================
                    Interrupt Priorities
=========================================================*/

#define RTOS_MAX_SYSCALL_INTERRUPT_PRIORITY      (5U)

#define RTOS_KERNEL_INTERRUPT_PRIORITY           (15U)

/*=========================================================
                    Timeouts
=========================================================*/

#define RTOS_DEFAULT_TIMEOUT            (1000U)

#define RTOS_WAIT_FOREVER_TIMEOUT       RTOS_WAIT_FOREVER

/*=========================================================
                    Alignment
=========================================================*/

#define RTOS_MEMORY_ALIGNMENT           (8U)

/*=========================================================
                    Utility Macros
=========================================================*/

#define RTOS_MS_TO_TICKS(ms) \
    ((TickType_t)(((ms) * RTOS_TICK_RATE_HZ) / 1000U))

#define RTOS_TICKS_TO_MS(ticks) \
    ((ticks) * RTOS_TICK_PERIOD_MS)

#ifdef __cplusplus
}
#endif

#endif /* CONFIG_H */