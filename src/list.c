#include <stdlib.h>
#include <assert.h>
// Temporary
#include <stdio.h>

#include "list.h"

void list_create(list *list, int element_size, free_function free_fn)
{
    assert(element_size > 0);

    list->length = 0;
    list->element_size = element_size;
    list->front = NULL;
    list->end = NULL;
    list->free_fn = free_fn;
}

void list_destroy(list *list)
{
    list_node *current;
    while (list->front != NULL)
    {
        current = list->front;
        list->front = current->next;

        if (list->free_fn)
        {
            list->free_fn(current->data);
        }

        free(current->data);
        free(current);
    }
}

void list_insert(list *list, int pos, void *element)
{
    assert(pos >= 0);
    assert(pos <= list->length);

    list_node *node = malloc(sizeof(list_node));
    node->data = malloc(list->element_size);
    node->next = NULL;

    memcpy(node->data, element, list->element_size);

    if (pos == 0)
    {
        if (list->length == 0)
        {
            list->front = node;
            list->end = node;
        }
        else
        {
            node->next = list->front;
            list->front = node;
        }
    }
    else
    {
        int index = 0;
        list_node *current = list->front;
        while (index < pos - 1)
        {
            current = current->next;
            index++;
        }
        list_node *next = current->next;
        node->next = next;
        current->next = node;
        if (pos == list->length)
        {
            list->end = node;
        }
    }
    list->length++;
}

void * list_remove(list *list, int pos)
{
    assert(pos >= 0);
    assert(list->length > 0);
    assert(pos <= list->length);

    list_node *current = list->front;
    for (int i = 0; i < pos - 1; i++)
    {
        current = current->next;
    }
    list_node *removed = current->next;
    current->next = removed->next;
    if (pos == list->length - 1)
    {
        list->end = current;
    }
    if (pos == 0)
    {
        list->front = current;
    }
    void *data = removed->data;
    free(removed);
    return data;
}

void * list_get(list *list, int pos)
{
    assert(pos >= 0);
    assert(pos < list->length);

    list_node *current = list->front;
    for (int i = 0; i < pos; i++)
    {
        current = current->next;
    }
    return current->data;
}

int list_length(list *list)
{
    return list->length;
}
