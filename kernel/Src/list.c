/**
 * @file list.c
 * @brief Generic Doubly Linked List Implementation
 *
 * Author : Vedula China Venkata Prasanth
 * Version: 1.0.0
 */

#include "list.h"

#include <stdio.h>
#include <stddef.h>

/*=========================================================
                    Initialization
=========================================================*/

void List_Init(List_t *list)
{
    if (list == NULL)
    {
        return;
    }

    list->head = NULL;
    list->tail = NULL;
    list->length = 0U;
}

void List_Clear(List_t *list)
{
    if (list == NULL)
    {
        return;
    }

    list->head = NULL;
    list->tail = NULL;
    list->length = 0U;
}

/*=========================================================
                    Insertion
=========================================================*/

RTOS_Status_t List_PushFront(
    List_t *list,
    ListNode_t *node)
{
    if ((list == NULL) || (node == NULL))
    {
        return RTOS_INVALID_PARAMETER;
    }

    node->previous = NULL;
    node->next = list->head;

    if (list->head != NULL)
    {
        list->head->previous = node;
    }
    else
    {
        list->tail = node;
    }

    list->head = node;
    list->length++;

    return RTOS_OK;
}

RTOS_Status_t List_PushBack(
    List_t *list,
    ListNode_t *node)
{
    if ((list == NULL) || (node == NULL))
    {
        return RTOS_INVALID_PARAMETER;
    }

    node->next = NULL;
    node->previous = list->tail;

    if (list->tail != NULL)
    {
        list->tail->next = node;
    }
    else
    {
        list->head = node;
    }

    list->tail = node;
    list->length++;

    return RTOS_OK;
}

RTOS_Status_t List_InsertAfter(
    List_t *list,
    ListNode_t *position,
    ListNode_t *node)
{
    if ((list == NULL) || (position == NULL) || (node == NULL))
    {
        return RTOS_INVALID_PARAMETER;
    }

    if (position == list->tail)
    {
        return List_PushBack(list, node);
    }

    node->next = position->next;
    node->previous = position;

    position->next->previous = node;
    position->next = node;

    list->length++;

    return RTOS_OK;
}

RTOS_Status_t List_InsertBefore(
    List_t *list,
    ListNode_t *position,
    ListNode_t *node)
{
    if ((list == NULL) || (position == NULL) || (node == NULL))
    {
        return RTOS_INVALID_PARAMETER;
    }

    if (position == list->head)
    {
        return List_PushFront(list, node);
    }

    node->next = position;
    node->previous = position->previous;

    position->previous->next = node;
    position->previous = node;

    list->length++;

    return RTOS_OK;
}

/*=========================================================
                    Removal
=========================================================*/

ListNode_t *List_PopFront(List_t *list)
{
    if ((list == NULL) || (list->head == NULL))
    {
        return NULL;
    }

    ListNode_t *node = list->head;

    list->head = node->next;

    if (list->head != NULL)
    {
        list->head->previous = NULL;
    }
    else
    {
        list->tail = NULL;
    }

    node->next = NULL;
    node->previous = NULL;

    list->length--;

    return node;
}

ListNode_t *List_PopBack(List_t *list)
{
    if ((list == NULL) || (list->tail == NULL))
    {
        return NULL;
    }

    ListNode_t *node = list->tail;

    list->tail = node->previous;

    if (list->tail != NULL)
    {
        list->tail->next = NULL;
    }
    else
    {
        list->head = NULL;
    }

    node->next = NULL;
    node->previous = NULL;

    list->length--;

    return node;
}

RTOS_Status_t List_Remove(
    List_t *list,
    ListNode_t *node)
{
    if ((list == NULL) || (node == NULL))
    {
        return RTOS_INVALID_PARAMETER;
    }

    if (node == list->head)
    {
        List_PopFront(list);
        return RTOS_OK;
    }

    if (node == list->tail)
    {
        List_PopBack(list);
        return RTOS_OK;
    }

    if (node->previous != NULL)
    {
        node->previous->next = node->next;
    }

    if (node->next != NULL)
    {
        node->next->previous = node->previous;
    }

    node->next = NULL;
    node->previous = NULL;

    list->length--;

    return RTOS_OK;
}

/*=========================================================
                    Search
=========================================================*/

ListNode_t *List_Find(
    List_t *list,
    void *data)
{
    if (list == NULL)
    {
        return NULL;
    }

    ListNode_t *current = list->head;

    while (current != NULL)
    {
        if (current->data == data)
        {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

bool List_Contains(
    List_t *list,
    ListNode_t *node)
{
    return (List_Find(list, node->data) != NULL);
}

/*=========================================================
                    Accessors
=========================================================*/

ListNode_t *List_Front(const List_t *list)
{
    return (list != NULL) ? list->head : NULL;
}

ListNode_t *List_Back(const List_t *list)
{
    return (list != NULL) ? list->tail : NULL;
}

rtos_u32_t List_Size(const List_t *list)
{
    return (list != NULL) ? list->length : 0U;
}

bool List_IsEmpty(const List_t *list)
{
    return (list == NULL) || (list->length == 0U);
}

/*=========================================================
                    Utilities
=========================================================*/

void List_ForEach(
    List_t *list,
    void (*callback)(ListNode_t *))
{
    if ((list == NULL) || (callback == NULL))
    {
        return;
    }

    ListNode_t *current = list->head;

    while (current != NULL)
    {
        callback(current);
        current = current->next;
    }
}

RTOS_Status_t List_Reverse(List_t *list)
{
    if (list == NULL)
    {
        return RTOS_INVALID_PARAMETER;
    }

    ListNode_t *current = list->head;
    ListNode_t *temp = NULL;

    while (current != NULL)
    {
        temp = current->previous;
        current->previous = current->next;
        current->next = temp;
        current = current->previous;
    }

    temp = list->head;
    list->head = list->tail;
    list->tail = temp;

    return RTOS_OK;
}

void List_Print(const List_t *list)
{
    if (list == NULL)
    {
        return;
    }

    printf("\n========== RTOS LIST ==========\n");

    ListNode_t *current = list->head;

    while (current != NULL)
    {
        printf("Node : %p  Data : %p\n",
               (void *)current,
               current->data);

        current = current->next;
    }

    printf("Length : %u\n", (unsigned int)list->length);
}