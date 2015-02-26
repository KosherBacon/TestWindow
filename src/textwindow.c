#include <stdio.h>

#include "list.h"

// Just so it compiles right now.
int main()
{
    list list;
    list_create(&list, sizeof(int), NULL);
    for (int i = 0; i < 100; i++)
    {
        list_insert(&list, i, &i);
    }
    printf("%i\n", *(int*) list_get(&list, 1));
    list_destroy(&list);
    return 0;
}
