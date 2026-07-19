# RTOS Scheduler

## Overview

The scheduler is the core component of the Embedded RTOS. It determines which task executes at any given time and manages task switching based on scheduling policies.

---

# Features

- Priority-based scheduling
- Round-robin scheduling
- Ready queue management
- Tick-driven scheduling
- Context switch support
- Runtime statistics
- Idle task support

---

# Scheduler Workflow

```
Kernel_Init()

↓

Scheduler_Init()

↓

Create Tasks

↓

Scheduler_Start()

↓

System Tick

↓

Scheduler_TickHandler()

↓

Update Ready Queue

↓

Select Highest Priority Task

↓

Context Switch

↓

Execute Selected Task
```

---

# Scheduling Algorithm

The scheduler follows a priority-based scheduling algorithm.

1. The system tick updates the scheduler.
2. The ready queue is examined.
3. The highest-priority ready task is selected.
4. If multiple tasks share the same priority, round-robin scheduling is applied.
5. Context switching transfers execution to the selected task.

---

# Scheduler States

| State | Description |
|--------|-------------|
| STOPPED | Scheduler is not running. |
| RUNNING | Scheduler is actively scheduling tasks. |
| SUSPENDED | Scheduling is temporarily paused. |

---

# Scheduler Statistics

The scheduler maintains runtime statistics including:

- Total Context Switches
- Total System Ticks
- Idle Ticks
- Running Tasks

These statistics can be obtained using:

```c
Scheduler_GetStatistics();
```

---

# Ready Queue

The scheduler maintains a ready queue containing all runnable tasks.

Each task enters the ready queue after creation or when it becomes ready for execution.

Tasks leave the ready queue when:

- Suspended
- Blocked
- Deleted

---

# Tick Processing

Every system tick performs the following operations:

- Increment system tick count
- Update software timers
- Evaluate task states
- Trigger scheduling if required

---

# Context Switching

The scheduler requests a context switch whenever:

- A higher-priority task becomes ready
- The current task blocks
- Round-robin time slice expires
- A task voluntarily yields the processor

---

# Idle Task

When no application task is ready to execute, the scheduler runs the idle task.

The idle task:

- Keeps the CPU occupied safely
- Prevents undefined execution
- Can be extended for power-saving operations

---

# Verification

The scheduler implementation has been verified using:

- Scheduler demonstration program
- Scheduler unit test
- Kernel integration tests

All scheduler tests completed successfully.