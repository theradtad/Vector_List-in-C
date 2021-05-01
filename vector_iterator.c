#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "vector_iterator.h"

int *element(iterator_vector *iter_ptr)
{
    return &iter_ptr->ptr_vector->arr[iter_ptr->index];
}

void next(iterator_vector *iter_ptr)
{
    iter_ptr->index += 1;
}

void prev(iterator_vector *iter_ptr)
{
    iter_ptr->index -= 1;
}

bool compare(iterator_vector *iter_ptr1, iterator_vector *iter_ptr2)
{
    if (iter_ptr1->type_of_movement == 'F')
    {
        if (iter_ptr1->index != iter_ptr2->index + 1)
            return 0;
        return 1;
    }
    else
    {
        if (iter_ptr1->index != iter_ptr2->index - 1)
            return 0;
        return 1;
    }
}

void init_iterator_vector_fwd(iterator_vector *iter_ptr, vector *ptr_vector)
{
    iter_ptr->ptr_vector = ptr_vector;
    iter_ptr->element = element;
    iter_ptr->next = next;
    iter_ptr->prev = prev;
    iter_ptr->index = 0;
    iter_ptr->compare = compare;
    iter_ptr->type_of_movement = 'F';
}

void init_iterator_vector_rev(iterator_vector *iter_ptr, vector *ptr_vector)
{
    iter_ptr->ptr_vector = ptr_vector;
    iter_ptr->element = element;
    iter_ptr->next = prev;
    iter_ptr->prev = next;
    iter_ptr->index = ptr_vector->sz - 1;
    iter_ptr->compare = compare;
    iter_ptr->type_of_movement = 'B';
}