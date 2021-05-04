#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "vector_iterator.h"

int *element_vector(iterator_vector *iter_ptr)
{
    if ((iter_ptr->index >= 0) && (iter_ptr->index < iter_ptr->ptr_vector->sz))
    {
        return &(iter_ptr->ptr_vector->arr[iter_ptr->index]);
    }
    else
    {
        printf("\nError: Index out of range \n");
        exit(-1);
    }
}

void next_vector(iterator_vector *iter_ptr)
{
    if ((iter_ptr->index >= 0) && (iter_ptr->index < iter_ptr->ptr_vector->sz))
    {
        ++iter_ptr->index;
    }
}

void prev_vector(iterator_vector *iter_ptr)
{
    if ((iter_ptr->index >= 0) && (iter_ptr->index < iter_ptr->ptr_vector->sz))
    {
        --iter_ptr->index;
    }
}
bool is_begin_vector(iterator_vector *iter_ptr)
{
    if (iter_ptr->index < 0)
        return true;
    return false;
}

bool is_end_vector(iterator_vector *iter_ptr)
{
    if (iter_ptr->index >= iter_ptr->ptr_vector->sz)
        return true;
    return false;
}

bool compare_vector(iterator_vector *iter_ptr1, iterator_vector iter_ptr2)
{
    if (iter_ptr1->base_iterator.type != iter_ptr2.base_iterator.type)
    {
        if (!(iter_ptr1->base_iterator.type == 'F' && iter_ptr2.base_iterator.type == 'C') && !(iter_ptr1->base_iterator.type == 'C' && iter_ptr2.base_iterator.type == 'F') && !(iter_ptr1->base_iterator.type == 'R' && iter_ptr2.base_iterator.type == 'K') && !(iter_ptr1->base_iterator.type == 'K' && iter_ptr2.base_iterator.type == 'R'))
            printf("\nError: Incomparable types \n");
        exit(-1);
    }
    if (iter_ptr1->index == iter_ptr2.index)
        return true;
    return false;
}

static void reset_vector(iterator_vector *iter_ptr)
{
    if (iter_ptr->base_iterator.type_of_movement == 'H')
    {
        iter_ptr->index = 0;
    }
    else
    {
        iter_ptr->index = iter_ptr->ptr_vector->sz - 1;
    }
}

static iterator_vector_vtable iter_vector_vtbl_fwd =
    {
        element_vector,
        next_vector,
        prev_vector,
        is_begin_vector,
        is_end_vector,
        compare_vector,
        reset_vector};

static iterator_vector_vtable iter_vector_vtbl_rev =
    {
        element_vector,
        prev_vector,
        next_vector,
        is_end_vector,
        is_begin_vector,
        compare_vector};

void init_iterator_vector_fwd(iterator_vector *iter_ptr, vector *ptr_vector, char ch)
{
    iter_ptr->ptr_vector = ptr_vector;
    iter_ptr->ptr_vtable = &iter_vector_vtbl_fwd;
    if (ch == 'H')
    {
        iter_ptr->index = 0;
        init_base_iterator(&iter_ptr->base_iterator, 'F', 'H');
    }
    else
    {
        iter_ptr->index = ptr_vector->sz - 1;
        init_base_iterator(&iter_ptr->base_iterator, 'F', 'T');
    }
}

void init_iterator_vector_rev(iterator_vector *iter_ptr, vector *ptr_vector, char ch)
{
    iter_ptr->ptr_vector = ptr_vector;
    iter_ptr->ptr_vtable = &iter_vector_vtbl_rev;
    if (ch == 'H')
    {
        iter_ptr->index = 0;
        init_base_iterator(&iter_ptr->base_iterator, 'R', 'H');
    }
    else
    {
        iter_ptr->index = ptr_vector->sz - 1;
        init_base_iterator(&iter_ptr->base_iterator, 'R', 'T');
    }
}

void init_iterator_vector_const(iterator_vector *iter_ptr, vector *ptr_vector, char ch)
{
    iter_ptr->ptr_vector = ptr_vector;
    iter_ptr->ptr_vtable = &iter_vector_vtbl_fwd;
    if (ch == 'H')
    {
        iter_ptr->index = 0;
        init_base_iterator(&iter_ptr->base_iterator, 'C', 'H');
    }
    else
    {
        iter_ptr->index = ptr_vector->sz - 1;
        init_base_iterator(&iter_ptr->base_iterator, 'C', 'T');
    }
}

void init_iterator_vector_const_rev(iterator_vector *iter_ptr, vector *ptr_vector, char ch)
{
    iter_ptr->ptr_vector = ptr_vector;
    iter_ptr->ptr_vtable = &iter_vector_vtbl_rev;
    if (ch == 'H')
    {
        iter_ptr->index = 0;
        init_base_iterator(&iter_ptr->base_iterator, 'K', 'H');
    }
    else
    {
        iter_ptr->index = ptr_vector->sz - 1;
        init_base_iterator(&iter_ptr->base_iterator, 'K', 'T');
    }
}