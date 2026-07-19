/******************************************************************************
 * File    : test_queue.c
 * Project : Embedded RTOS
 * Description : Queue Unit Test
 ******************************************************************************/

#include <stdio.h>

#include "kernel.h"
#include "queue.h"

#define QUEUE_LENGTH 5

int main(void)
{
    Queue_t queue;
    int buffer[QUEUE_LENGTH];

    int tx = 100;
    int rx = 0;

    printf("=========================================\n");
    printf("         RTOS Queue Unit Test\n");
    printf("=========================================\n\n");

    /* Kernel Initialization */
    if (Kernel_Init() == STATUS_OK)
        printf("PASS : Kernel_Init()\n");
    else
    {
        printf("FAIL : Kernel_Init()\n");
        return -1;
    }

    /* Queue Creation */
    if (Queue_Create(&queue,
                     buffer,
                     sizeof(int),
                     QUEUE_LENGTH) == STATUS_OK)
        printf("PASS : Queue_Create()\n");
    else
    {
        printf("FAIL : Queue_Create()\n");
        return -1;
    }

    /* Queue Empty Check */
    if (Queue_IsEmpty(&queue))
        printf("PASS : Queue_IsEmpty()\n");
    else
        printf("FAIL : Queue_IsEmpty()\n");

    /* Queue Send */
    if (Queue_Send(&queue, &tx) == STATUS_OK)
        printf("PASS : Queue_Send()\n");
    else
        printf("FAIL : Queue_Send()\n");

    /* Queue Count */
    if (Queue_Count(&queue) == 1)
        printf("PASS : Queue_Count()\n");
    else
        printf("FAIL : Queue_Count()\n");

    /* Queue Receive */
    if (Queue_Receive(&queue, &rx) == STATUS_OK)
        printf("PASS : Queue_Receive()\n");
    else
        printf("FAIL : Queue_Receive()\n");

    /* Data Verification */
    if (rx == tx)
        printf("PASS : Queue Data Integrity\n");
    else
        printf("FAIL : Queue Data Integrity\n");

    /* Queue Empty Again */
    if (Queue_IsEmpty(&queue))
        printf("PASS : Queue Empty After Receive\n");
    else
        printf("FAIL : Queue Empty After Receive\n");

    printf("\n=========================================\n");
    printf("Queue Unit Test Completed Successfully\n");
    printf("=========================================\n");

    return 0;
}