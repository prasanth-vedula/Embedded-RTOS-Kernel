# Embedded RTOS Architecture

## Overview

The Embedded RTOS is a lightweight Real-Time Operating System developed in C for embedded applications. The kernel is modular, making each subsystem independent, reusable, and easy to maintain.

---

# High-Level Architecture

```
+------------------------------------------------------+
|                  Application Layer                   |
|------------------------------------------------------|
| Demo Programs | Unit Tests | User Applications       |
+------------------------------------------------------+
                      |
                      V
+------------------------------------------------------+
|                    RTOS Kernel                        |
|------------------------------------------------------|
| Scheduler | Tasks | Queue | Semaphore | Mutex        |
| Timer | Event Flags | Memory Manager | Hooks         |
+------------------------------------------------------+
                      |
                      V
+------------------------------------------------------+
|             Hardware Abstraction Layer               |
|------------------------------------------------------|
| Port Layer | System Tick | CPU Interface             |
+------------------------------------------------------+
```

---

# Kernel Modules

## Kernel

Responsible for initialization, startup, shutdown, and overall RTOS control.

---

## Scheduler

Implements task scheduling and context switching.

Responsibilities:

- Ready queue management
- Priority scheduling
- Round-robin scheduling
- Tick processing
- Context switching
- Runtime statistics

---

## Task Manager

Maintains Task Control Blocks (TCBs).

Responsible for:

- Task creation
- Task deletion
- Suspend / Resume
- Priority management
- Task state transitions

---

## Queue

Provides inter-task communication using FIFO queues.

Supports:

- Send
- Receive
- Reset
- Queue state checking

---

## Semaphore

Provides synchronization between multiple tasks.

Supports:

- Binary semaphore
- Counting semaphore
- Take
- Give
- Reset

---

## Mutex

Provides mutual exclusion for protecting shared resources.

Supports:

- Lock
- Unlock
- Ownership tracking
- Reset

---

## Software Timer

Implements software timers.

Supports:

- One-shot timers
- Periodic timers
- Callback execution
- Restart
- Stop

---

## Event Flags

Supports event-based synchronization.

Features:

- Set flags
- Clear flags
- Wait for Any
- Wait for All

---

## Memory Manager

Responsible for runtime memory allocation and deallocation.

---

## Port Layer

Acts as the hardware abstraction layer between the RTOS kernel and the target processor.

---

# Directory Structure

```
embedded-rtos-kernel/

kernel/
    Inc/
    Src/

examples/

tests/

docs/

screenshots/
```

---

# Design Goals

- Modular architecture
- Portable implementation
- Low memory footprint
- Easy maintenance
- Scalable kernel
- Educational reference implementation

---

# Verification

All kernel modules have been verified through dedicated demonstration programs and unit tests included in this repository.