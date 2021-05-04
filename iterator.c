#include <stdio.h>
#include <stdlib.h>
#include "iterator.h"

static int *element(iterator *iter_ptr)
{
    return NULL;
}

static void next(iterator *iter_ptr)
{
    ;
}

static void prev(iterator *iter_ptr)
{
    ;
}

static bool is_begin(iterator *iter_ptr)
{
    return true;
}

static bool is_end(iterator *iter_ptr)
{
    return true;
}
static bool compare(iterator *iter_ptr1, iterator *iter_ptr2)
{
    return true;
}

void reset(iterator *iter_ptr)
{
    ;
}

static iterator_vtable iterator_vtbl =
    {
        element,
        next,
        prev,
        is_begin,
        is_end,
        compare,
        reset};

void init_base_iterator(iterator *iter_ptr, char type, char type_of_movement)
{
    iter_ptr->ptr_vtable = &iterator_vtbl;
    iter_ptr->type_of_movement = type_of_movement;
    iter_ptr->type = type;
}
