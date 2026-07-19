/**
 * @file list.h
 * @brief Generic Doubly Linked List Interface
 *
 * This module provides the generic doubly linked list
 * implementation used throughout the RTOS.
 *
 * It is utilized by:
 *  - Scheduler Ready List
 *  - Blocked Task List
 *  - Delayed Task List
 *  - Timer List
 *  - Queue Waiting List
 *
 * Author : Vedula China Venkata Prasanth
 * Version: 1.0.0
 */

#ifndef LIST_H
#define LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"

/*=========================================================
                    Data Structures
=========================================================*/

/**
 * @brief RTOS List
 */
typedef struct
{
    ListNode_t *head;

    ListNode_t *tail;

    rtos_u32_t length;

} List_t;

/*=========================================================
                    Initialization
=========================================================*/

/**
 * @brief Initialize a linked list.
 *
 * @param list Pointer to list.
 */
void List_Init(List_t *list);

/**
 * @brief Clear all nodes from the list.
 *
 * @param list Pointer to list.
 */
void List_Clear(List_t *list);

/*=========================================================
                    Insertion
=========================================================*/

/**
 * @brief Insert node at front.
 */
RTOS_Status_t List_PushFront(
    List_t *list,
    ListNode_t *node);

/**
 * @brief Insert node at end.
 */
RTOS_Status_t List_PushBack(
    List_t *list,
    ListNode_t *node);

/**
 * @brief Insert node after another node.
 */
RTOS_Status_t List_InsertAfter(
    List_t *list,
    ListNode_t *position,
    ListNode_t *node);

/**
 * @brief Insert node before another node.
 */
RTOS_Status_t List_InsertBefore(
    List_t *list,
    ListNode_t *position,
    ListNode_t *node);

/*=========================================================
                    Removal
=========================================================*/

/**
 * @brief Remove first node.
 */
ListNode_t *List_PopFront(
    List_t *list);

/**
 * @brief Remove last node.
 */
ListNode_t *List_PopBack(
    List_t *list);

/**
 * @brief Remove specific node.
 */
RTOS_Status_t List_Remove(
    List_t *list,
    ListNode_t *node);

/*=========================================================
                    Search
=========================================================*/

/**
 * @brief Find node containing data.
 */
ListNode_t *List_Find(
    List_t *list,
    void *data);

/**
 * @brief Check if list contains node.
 */
bool List_Contains(
    List_t *list,
    ListNode_t *node);

/*=========================================================
                    Accessors
=========================================================*/

/**
 * @brief Get first node.
 */
ListNode_t *List_Front(
    const List_t *list);

/**
 * @brief Get last node.
 */
ListNode_t *List_Back(
    const List_t *list);

/**
 * @brief Get list length.
 */
rtos_u32_t List_Size(
    const List_t *list);

/**
 * @brief Check if list is empty.
 */
bool List_IsEmpty(
    const List_t *list);

/*=========================================================
                    Utilities
=========================================================*/

/**
 * @brief Traverse every node.
 */
void List_ForEach(
    List_t *list,
    void (*callback)(ListNode_t *));

/**
 * @brief Reverse list.
 */
RTOS_Status_t List_Reverse(
    List_t *list);

/**
 * @brief Print list (debug).
 */
void List_Print(
    const List_t *list);

#ifdef __cplusplus
}
#endif

#endif /* LIST_H */