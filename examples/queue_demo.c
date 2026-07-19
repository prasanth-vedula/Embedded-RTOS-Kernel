/******************************************************************************
 * File    : queue_demo.c
 * Project : Embedded RTOS
 * Description : Queue API Demonstration
 ******************************************************************************/

#include <stdio.h>

#include "kernel.h"
#include "queue.h"

#define QUEUE_LENGTH    5

int main(void)
{
    Queue_t queue;

    /* Queue storage buffer */
    int queueBuffer[QUEUE_LENGTH];

    int txData;
    int rxData;

    printf("=========================================\n");
    printf("        RTOS Queue Demonstration\n");
    printf("=========================================\n\n");

    if (Kernel_Init() != STATUS_OK)
    {
        printf("Kernel initialization failed!\n");
        return -1;
    }

    if (Queue_Create(&queue,
                     queueBuffer,
                     sizeof(int),
                     QUEUE_LENGTH) != STATUS_OK)
    {
        printf("Queue creation failed!\n");
        return -1;
    }

    printf("Queue created successfully.\n\n");

    for(txData = 10; txData <= 50; txData += 10)
    {
        if(Queue_Send(&queue, &txData) == STATUS_OK)
        {
            printf("Sent     : %d\n", txData);
        }
        else
        {
            printf("Queue Full\n");
        }
    }

    printf("\n");

    while(!Queue_IsEmpty(&queue))
    {
        if(Queue_Receive(&queue, &rxData) == STATUS_OK)
        {
            printf("Received : %d\n", rxData);
        }
    }

    printf("\nQueue demonstration completed.\n");

    return 0;
}