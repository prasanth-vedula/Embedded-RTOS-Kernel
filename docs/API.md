# Embedded RTOS API Reference

## Overview

This document describes the public APIs provided by the Embedded RTOS kernel.

---

# Kernel

| Function | Description |
|----------|-------------|
| `Kernel_Init()` | Initializes the RTOS kernel. |
| `Kernel_Start()` | Starts scheduler execution. |
| `Kernel_Stop()` | Stops the scheduler. |

---

# Scheduler

| Function | Description |
|----------|-------------|
| `Scheduler_Init()` | Initializes scheduler. |
| `Scheduler_Start()` | Starts scheduler operation. |
| `Scheduler_Stop()` | Stops scheduler. |
| `Scheduler_Schedule()` | Performs task scheduling. |
| `Scheduler_TickHandler()` | Processes system tick. |
| `Scheduler_GetCurrentTask()` | Returns current running task. |
| `Scheduler_GetStatistics()` | Returns scheduler statistics. |

---

# Task

| Function | Description |
|----------|-------------|
| `Task_Create()` | Creates a new task. |
| `Task_Delete()` | Deletes a task. |
| `Task_Suspend()` | Suspends a task. |
| `Task_Resume()` | Resumes a suspended task. |
| `Task_SetPriority()` | Changes task priority. |

---

# Queue

| Function | Description |
|----------|-------------|
| `Queue_Create()` | Creates a queue. |
| `Queue_Send()` | Sends data to queue. |
| `Queue_Receive()` | Receives data from queue. |
| `Queue_Reset()` | Clears queue contents. |
| `Queue_IsEmpty()` | Returns queue state. |

---

# Semaphore

| Function | Description |
|----------|-------------|
| `Semaphore_Create()` | Creates semaphore. |
| `Semaphore_Take()` | Takes semaphore. |
| `Semaphore_Give()` | Releases semaphore. |
| `Semaphore_Reset()` | Resets semaphore. |

---

# Mutex

| Function | Description |
|----------|-------------|
| `Mutex_Create()` | Creates mutex. |
| `Mutex_Lock()` | Locks mutex. |
| `Mutex_Unlock()` | Unlocks mutex. |
| `Mutex_Reset()` | Resets mutex. |

---

# Timer

| Function | Description |
|----------|-------------|
| `Timer_Create()` | Creates software timer. |
| `Timer_Start()` | Starts timer. |
| `Timer_Stop()` | Stops timer. |
| `Timer_Restart()` | Restarts timer. |
| `Timer_Tick()` | Updates timer tick. |

---

# Event Flags

| Function | Description |
|----------|-------------|
| `Event_Create()` | Creates event object. |
| `Event_Set()` | Sets event flags. |
| `Event_Clear()` | Clears event flags. |
| `Event_WaitAny()` | Waits for any event flag. |
| `Event_WaitAll()` | Waits for all event flags. |
| `Event_Reset()` | Clears all event flags. |

---

# Memory

| Function | Description |
|----------|-------------|
| `Memory_Init()` | Initializes memory manager. |
| `Memory_Allocate()` | Allocates memory block. |
| `Memory_Free()` | Frees allocated block. |

---

## API Status

All public APIs documented above were implemented and verified using the supplied demonstration programs and unit tests.