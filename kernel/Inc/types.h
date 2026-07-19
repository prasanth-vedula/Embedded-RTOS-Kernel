/**
 * @file types.h
 * @brief Common type definitions for Embedded RTOS Kernel
 *
 * This file contains common data types, enums,
 * callback definitions, and status codes shared
 * across the entire RTOS kernel.
 *
 * Author : Vedula China Venkata Prasanth
 * Version: 1.0.0
 */

#ifndef TYPES_H
#define TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
/*----------------------------------------------------------
 * Compatibility Types
 *---------------------------------------------------------*/

typedef bool Bool_t;

typedef enum
{
    STATUS_OK = 0,
    STATUS_ERROR,
    STATUS_TIMEOUT,
    STATUS_INVALID_PARAMETER,
    STATUS_OUT_OF_MEMORY,
    STATUS_QUEUE_FULL,
    STATUS_QUEUE_EMPTY,
    STATUS_SEMAPHORE_UNAVAILABLE,
    STATUS_MUTEX_LOCKED,
    STATUS_TASK_NOT_FOUND,
    STATUS_TIMER_EXPIRED

} Status_t;

/*----------------------------------------------------------
 * Version Information
 *---------------------------------------------------------*/

#define RTOS_VERSION_MAJOR        1U
#define RTOS_VERSION_MINOR        0U
#define RTOS_VERSION_PATCH        0U

/*----------------------------------------------------------
 * Boolean Compatibility
 *---------------------------------------------------------*/

#ifndef TRUE
#define TRUE     (1U)
#endif

#ifndef FALSE
#define FALSE    (0U)
#endif

/*----------------------------------------------------------
 * Basic Kernel Types
 *---------------------------------------------------------*/

typedef uint8_t     rtos_u8_t;
typedef uint16_t    rtos_u16_t;
typedef uint32_t    rtos_u32_t;
typedef uint64_t    rtos_u64_t;

typedef int8_t      rtos_s8_t;
typedef int16_t     rtos_s16_t;
typedef int32_t     rtos_s32_t;
typedef int64_t     rtos_s64_t;

typedef uintptr_t   rtos_addr_t;

typedef uint32_t    TickType_t;

typedef uint32_t    StackType_t;

typedef void (*TaskFunction_t)(void *);

typedef void (*TimerCallback_t)(void *);

/*----------------------------------------------------------
 * Kernel Status
 *---------------------------------------------------------*/

typedef enum
{
    RTOS_OK = 0,

    RTOS_ERROR,

    RTOS_TIMEOUT,

    RTOS_INVALID_PARAMETER,

    RTOS_OUT_OF_MEMORY,

    RTOS_QUEUE_FULL,

    RTOS_QUEUE_EMPTY,

    RTOS_SEMAPHORE_UNAVAILABLE,

    RTOS_MUTEX_LOCKED,

    RTOS_TASK_NOT_FOUND,

    RTOS_TIMER_EXPIRED

} RTOS_Status_t;

/*----------------------------------------------------------
 * Task States
 *---------------------------------------------------------*/

typedef enum
{
    TASK_READY = 0,

    TASK_RUNNING,

    TASK_BLOCKED,

    TASK_SUSPENDED,

    TASK_SLEEPING,

    TASK_TERMINATED

} TaskState_t;

/*----------------------------------------------------------
 * Queue Mode
 *---------------------------------------------------------*/

typedef enum
{
    QUEUE_FIFO = 0,

    QUEUE_PRIORITY

} QueueMode_t;

/*----------------------------------------------------------
 * Scheduler Policy
 *---------------------------------------------------------*/

typedef enum
{
    SCHEDULER_ROUND_ROBIN = 0,

    SCHEDULER_PRIORITY

} SchedulerPolicy_t;

/*----------------------------------------------------------
 * Forward Declarations
 *---------------------------------------------------------*/

struct TaskControlBlock;
struct QueueControlBlock;
struct SemaphoreControlBlock;
struct MutexControlBlock;
struct TimerControlBlock;

typedef struct TaskControlBlock TaskControlBlock_t;
typedef struct QueueControlBlock QueueControlBlock_t;
typedef struct SemaphoreControlBlock SemaphoreControlBlock_t;
typedef struct MutexControlBlock MutexControlBlock_t;
typedef struct TimerControlBlock TimerControlBlock_t;

/*----------------------------------------------------------
 * Generic List Node
 *---------------------------------------------------------*/

typedef struct ListNode
{
    void *data;

    struct ListNode *next;

    struct ListNode *previous;

} ListNode_t;

/*----------------------------------------------------------
 * Generic Kernel Handle
 *---------------------------------------------------------*/

typedef void *KernelHandle_t;

/*----------------------------------------------------------
 * Common Constants
 *---------------------------------------------------------*/

#define RTOS_WAIT_FOREVER      ((TickType_t)0xFFFFFFFFU)

#define RTOS_NO_WAIT           ((TickType_t)0U)

#define RTOS_MAX_PRIORITY      (10U)

#define RTOS_MIN_PRIORITY      (0U)
/*----------------------------------------------------------
 * Compatibility Macros
 *---------------------------------------------------------*/

#define STATUS_SUCCESS STATUS_OK
#define STATUS_FAIL    STATUS_ERROR

#ifdef __cplusplus
}
#endif

#endif /* TYPES_H */