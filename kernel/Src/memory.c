/******************************************************************************
 * File    : memory.c
 * Project : Embedded RTOS
 * Description : Static Memory Pool Implementation
 ******************************************************************************/

#include "memory.h"

/******************************************************************************
 * Create Memory Pool
 ******************************************************************************/

Status_t MemoryPool_Create(
    MemoryPool_t *memoryPool,
    void *poolMemory,
    void *allocationMap,
    uint32_t blockSize,
    uint32_t totalBlocks)
{
    uint32_t i;

    if ((memoryPool == NULL) ||
        (poolMemory == NULL) ||
        (allocationMap == NULL) ||
        (blockSize == 0U) ||
        (totalBlocks == 0U))
    {
        return STATUS_ERROR;
    }

    memoryPool->pool = (uint8_t *)poolMemory;
    memoryPool->allocationMap = (uint8_t *)allocationMap;
    memoryPool->blockSize = blockSize;
    memoryPool->totalBlocks = totalBlocks;
    memoryPool->freeBlocks = totalBlocks;

    for (i = 0U; i < totalBlocks; i++)
    {
        memoryPool->allocationMap[i] = 0U;
    }

    return STATUS_OK;
}

/******************************************************************************
 * Allocate Memory Block
 ******************************************************************************/

void *MemoryPool_Allocate(
    MemoryPool_t *memoryPool)
{
    uint32_t i;

    if (memoryPool == NULL)
    {
        return NULL;
    }

    if (memoryPool->freeBlocks == 0U)
    {
        return NULL;
    }

    for (i = 0U; i < memoryPool->totalBlocks; i++)
    {
        if (memoryPool->allocationMap[i] == 0U)
        {
            memoryPool->allocationMap[i] = 1U;
            memoryPool->freeBlocks--;

            return (void *)(memoryPool->pool +
                            (i * memoryPool->blockSize));
        }
    }

    return NULL;
}

/******************************************************************************
 * Free Memory Block
 ******************************************************************************/

Status_t MemoryPool_Free(
    MemoryPool_t *memoryPool,
    void *block)
{
    uint32_t index;

    if ((memoryPool == NULL) || (block == NULL))
    {
        return STATUS_ERROR;
    }

    if ((uint8_t *)block < memoryPool->pool)
    {
        return STATUS_ERROR;
    }

    index = ((uint8_t *)block - memoryPool->pool) /
            memoryPool->blockSize;

    if (index >= memoryPool->totalBlocks)
    {
        return STATUS_ERROR;
    }

    if (memoryPool->allocationMap[index] == 0U)
    {
        return STATUS_ERROR;
    }

    memoryPool->allocationMap[index] = 0U;
    memoryPool->freeBlocks++;

    return STATUS_OK;
}

/******************************************************************************
 * Reset Memory Pool
 ******************************************************************************/

Status_t MemoryPool_Reset(
    MemoryPool_t *memoryPool)
{
    uint32_t i;

    if (memoryPool == NULL)
    {
        return STATUS_ERROR;
    }

    for (i = 0U; i < memoryPool->totalBlocks; i++)
    {
        memoryPool->allocationMap[i] = 0U;
    }

    memoryPool->freeBlocks = memoryPool->totalBlocks;

    return STATUS_OK;
}

/******************************************************************************
 * Get Free Blocks
 ******************************************************************************/

uint32_t MemoryPool_GetFreeBlocks(
    MemoryPool_t *memoryPool)
{
    if (memoryPool == NULL)
    {
        return 0U;
    }

    return memoryPool->freeBlocks;
}

/******************************************************************************
 * Get Used Blocks
 ******************************************************************************/

uint32_t MemoryPool_GetUsedBlocks(
    MemoryPool_t *memoryPool)
{
    if (memoryPool == NULL)
    {
        return 0U;
    }

    return (memoryPool->totalBlocks -
            memoryPool->freeBlocks);
}