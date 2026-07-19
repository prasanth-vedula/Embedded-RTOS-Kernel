# Building Embedded RTOS

## Requirements

- GCC Compiler (MinGW GCC 16 or later)
- Windows 10/11
- Command Prompt
- Git (optional)

---

## Project Structure

```
embedded-rtos-kernel/
│
├── kernel/
│   ├── Inc/
│   └── Src/
│
├── examples/
├── tests/
├── screenshots/
└── docs/
```

---

## Compile Example Programs

Example:

```bash
gcc -Ikernel/Inc examples/queue_demo.c kernel/*.o -o queue_demo.exe
```

Run:

```bash
queue_demo.exe
```

---

## Compile Unit Tests

Example:

```bash
gcc -Ikernel/Inc tests/test_queue.c kernel/*.o -o test_queue.exe
```

Run:

```bash
test_queue.exe
```

---

## Build Steps

1. Compile kernel source files.
2. Generate object (.o) files.
3. Compile demo applications.
4. Compile unit tests.
5. Execute tests.
6. Verify all tests pass successfully.

---

## Tested Environment

- Windows 11
- GCC 16.1.0 (MinGW-W64)
- Command Prompt