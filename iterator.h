#ifndef ITERATOR_H
#define ITERATOR_H

#include <stdbool.h>

typedef struct iterator_vtable iterator_vtable;

typedef struct
{
    iterator_vtable *ptr_vtable;
    char type_of_movement;
    char type;
} iterator;

struct iterator_vtable
{
    int *(*element)(iterator *iter_ptr);
    void (*next)(iterator *iter_ptr);
    void (*prev)(iterator *iter_ptr);
    bool (*is_begin)(iterator *iter_ptr);
    bool (*is_end)(iterator *iter_ptr);
    bool (*compare)(iterator *iter_ptr1, iterator *iter_ptr2);
    void (*reset)(iterator *iter_ptr);
};

void init_base_iterator(iterator *iter_ptr, char type, char type_of_movement);

#endif