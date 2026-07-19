#ifndef MEMORY_H
#define MEMORY_H

/******************************************************************************
 * File    : memory.h
 * Project : Embedded RTOS
 * Description : Static Memory Pool Manager
 ******************************************************************************/

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * Memory Pool Structure
 ******************************************************************************/

typedef struct
{
    uint8_t *pool;

    uint32_t blockSize;

    uint32_t totalBlocks;

    uint32_t freeBlocks;

    uint8_t *allocationMap;

} MemoryPool_t;

/******************************************************************************
 * API
 ******************************************************************************/

/* Initialize Memory Pool */
Status_t MemoryPool_Create(
    MemoryPool_t *memoryPool,
    void *poolMemory,
    void *allocationMap,
    uint32_t blockSize,
    uint32_t totalBlocks);

/* Allocate Memory Block */
void *MemoryPool_Allocate(
    MemoryPool_t *memoryPool);

/* Free Memory Block */
Status_t MemoryPool_Free(
    MemoryPool_t *memoryPool,
    void *block);

/* Reset Memory Pool */
Status_t MemoryPool_Reset(
    MemoryPool_t *memoryPool);

/* Get Number of Free Blocks */
uint32_t MemoryPool_GetFreeBlocks(
    MemoryPool_t *memoryPool);

/* Get Number of Used Blocks */
uint32_t MemoryPool_GetUsedBlocks(
    MemoryPool_t *memoryPool);

#ifdef __cplusplus
}
#endif

#endif