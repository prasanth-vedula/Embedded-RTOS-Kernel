# Testing Guide

## Overview

The Embedded RTOS project includes demonstration programs and unit tests for validating each kernel module.

---

# Demo Applications

The following demo applications demonstrate the functionality of each RTOS component.

| Demo | Status |
|------|--------|
| Queue Demo | ✅ Passed |
| Semaphore Demo | ✅ Passed |
| Mutex Demo | ✅ Passed |
| Timer Demo | ✅ Passed |
| Event Demo | ✅ Passed |

---

# Unit Tests

The following unit tests verify the correctness of each RTOS module.

| Test | Status |
|------|--------|
| Kernel Test | ✅ Passed |
| Scheduler Test | ✅ Passed |
| Queue Test | ✅ Passed |
| Semaphore Test | ✅ Passed |
| Mutex Test | ✅ Passed |
| Timer Test | ✅ Passed |
| Event Test | ✅ Passed |

---

# Compilation

Compile demo applications using:

```bash
gcc -Ikernel/Inc examples/<demo>.c kernel/*.o -o demo.exe
```

Compile unit tests using:

```bash
gcc -Ikernel/Inc tests/<test>.c kernel/*.o -o test.exe
```

---

# Validation Results

All demonstration programs compiled successfully.

All unit tests executed successfully.

No compilation errors remained after final integration.

---

# Test Environment

Operating System

- Windows 11

Compiler

- GCC 16.1.0 (MinGW-W64)

Language

- C (C11 Compatible)

---

# Summary

✔ Queue Module Verified

✔ Semaphore Module Verified

✔ Mutex Module Verified

✔ Timer Module Verified

✔ Event Module Verified

✔ Scheduler Module Verified

✔ Kernel Module Verified

All implemented RTOS modules passed functional verification successfully.