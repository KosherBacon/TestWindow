#ifndef __LIST_H
#define __LIST_H

typedef void (*free_function)(void *);

typedef enum {FALSE, TRUE} bool;

typedef bool (*list_iterator)(void *);

typedef struct _list_node {
    void *data;
    struct _list_node *next;
} list_node;

typedef struct {
    int length;
    int element_size;
    list_node *front;
    list_node *end;
    free_function free_fn;
} list;

void list_create(list *list, int element_size, free_function free_fn);

void list_destroy(list *list);

void list_insert(list *list, int pos, void *element);

void * list_remove(list *list, int pos);

void * list_get(list *list, int pos);

int list_length(list *list);

#endif
