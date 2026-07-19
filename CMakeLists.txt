cmake_minimum_required(VERSION 3.16)

project(
    EmbeddedRTOS
    VERSION 1.0.0
    DESCRIPTION "Lightweight Modular Embedded RTOS Kernel"
    LANGUAGES C
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(
    kernel/Inc
)

file(GLOB KERNEL_SOURCES
    kernel/Src/*.c
)

add_library(rtos STATIC
    ${KERNEL_SOURCES}
)

add_executable(queue_demo
    examples/queue_demo.c
)

target_link_libraries(queue_demo
    rtos
)

add_executable(semaphore_demo
    examples/semaphore_demo.c
)

target_link_libraries(semaphore_demo
    rtos
)

add_executable(mutex_demo
    examples/mutex_demo.c
)

target_link_libraries(mutex_demo
    rtos
)

add_executable(timer_demo
    examples/timer_demo.c
)

target_link_libraries(timer_demo
    rtos
)

add_executable(event_demo
    examples/event_demo.c
)

target_link_libraries(event_demo
    rtos
)

enable_testing()

add_executable(test_kernel
    tests/test_kernel.c
)

target_link_libraries(test_kernel
    rtos
)

add_executable(test_scheduler
    tests/test_scheduler.c
)

target_link_libraries(test_scheduler
    rtos
)

add_executable(test_queue
    tests/test_queue.c
)

target_link_libraries(test_queue
    rtos
)

add_executable(test_semaphore
    tests/test_semaphore.c
)

target_link_libraries(test_semaphore
    rtos
)

add_executable(test_mutex
    tests/test_mutex.c
)

target_link_libraries(test_mutex
    rtos
)

add_executable(test_timer
    tests/test_timer.c
)

target_link_libraries(test_timer
    rtos
)

add_executable(test_event
    tests/test_event.c
)

target_link_libraries(test_event
    rtos
)

add_test(NAME KernelTest COMMAND test_kernel)
add_test(NAME SchedulerTest COMMAND test_scheduler)
add_test(NAME QueueTest COMMAND test_queue)
add_test(NAME SemaphoreTest COMMAND test_semaphore)
add_test(NAME MutexTest COMMAND test_mutex)
add_test(NAME TimerTest COMMAND test_timer)
add_test(NAME EventTest COMMAND test_event)