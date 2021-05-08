#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "vector_iterator.h"

// Returns the address of the current element to which the index points to.
int *element_vector(iterator_vector *iter_ptr)
{
    if ((iter_ptr->index >= 0) && (iter_ptr->index < iter_ptr->ptr_container->sz))
    {
        return &(iter_ptr->ptr_container->arr[iter_ptr->index]);
    }
    else
    {
        printf("\nError: Index out of range \n");
        exit(-1);
    }
}

// Moves the index pointer to the next element in the vector.
void next_vector(iterator_vector *iter_ptr)
{
    if ((iter_ptr->index >= 0) && (iter_ptr->index < iter_ptr->ptr_container->sz))
    {
        ++iter_ptr->index;
    }
}

// Moves the index pointer to the previous element in the vector.
void prev_vector(iterator_vector *iter_ptr)
{
    if ((iter_ptr->index >= 0) && (iter_ptr->index < iter_ptr->ptr_container->sz))
    {
        --iter_ptr->index;
    }
}

// Checks if the index is < 0 which would indicate the index is before the first element.
bool is_begin_vector(iterator_vector *iter_ptr)
{
    if (iter_ptr->index < 0)
        return true;
    return false;
}

// Checks if the index is >= vector size which would indicate that its the end of the vector.
bool is_end_vector(iterator_vector *iter_ptr)
{
    if (iter_ptr->index >= iter_ptr->ptr_container->sz)
        return true;
    return false;
}

// Compares two vectors using 2 iterator objects, comparision works only if both iterator_list objects are forward iterators or both are reverse iterators.
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

// Resets the index pointer to the initial element that it was pointing to before next or prev was called on it.
static void reset_vector(iterator_vector *iter_ptr)
{
    if (iter_ptr->base_iterator.type_of_movement == 'H')
    {
        iter_ptr->index = 0;
    }
    else
    {
        iter_ptr->index = iter_ptr->ptr_container->sz - 1;
    }
}

// static void copy_vector(iterator_vector *iter_ptr_source, iterator *iter_ptr_destination)
// {
//     iter_ptr_destination = (iterator *)iter_ptr_source->ptr_container->ptr_vtable->begin(iter_ptr_source->ptr_container);
//     printf("%d\n", *(iter_ptr_destination->ptr_vtable->element(iter_ptr_destination)));
// }

static iterator_vector_vtable iter_vector_vtbl_fwd =
    {
        element_vector,
        next_vector,
        prev_vector,
        is_begin_vector,
        is_end_vector,
        compare_vector,
        reset_vector,
};

static iterator_vector_vtable iter_vector_vtbl_rev =
    {
        element_vector,
        prev_vector,
        next_vector,
        is_end_vector,
        is_begin_vector,
        compare_vector,
        reset_vector,
};

// used to initialize a forward iterator in the vector. Calls base iterators init as well.
// The argument ch is used to indicate whether begin member function of vector is calling this function or whether end member function of vector is calling it.
void init_iterator_vector_fwd(iterator_vector *iter_ptr, vector *ptr_container, char ch)
{
    iter_ptr->ptr_container = ptr_container;
    iter_ptr->ptr_vtable = &iter_vector_vtbl_fwd;
    if (ch == 'H')
    {
        iter_ptr->index = 0;
        init_base_iterator(&iter_ptr->base_iterator, 'F', 'H');
    }
    else
    {
        iter_ptr->index = ptr_container->sz - 1;
        init_base_iterator(&iter_ptr->base_iterator, 'F', 'T');
    }
}

// used to initialize the reverse iterator in vector.
void init_iterator_vector_rev(iterator_vector *iter_ptr, vector *ptr_container, char ch)
{
    iter_ptr->ptr_container = ptr_container;
    iter_ptr->ptr_vtable = &iter_vector_vtbl_rev;
    if (ch == 'H')
    {
        iter_ptr->index = 0;
        init_base_iterator(&iter_ptr->base_iterator, 'R', 'H');
    }
    else
    {
        iter_ptr->index = ptr_container->sz - 1;
        init_base_iterator(&iter_ptr->base_iterator, 'R', 'T');
    }
}

// used to initialize the constant forward iterator in vector.
void init_iterator_vector_const(iterator_vector *iter_ptr, vector *ptr_container, char ch)
{
    iter_ptr->ptr_container = ptr_container;
    iter_ptr->ptr_vtable = &iter_vector_vtbl_fwd;
    if (ch == 'H')
    {
        iter_ptr->index = 0;
        init_base_iterator(&iter_ptr->base_iterator, 'C', 'H');
    }
    else
    {
        iter_ptr->index = ptr_container->sz - 1;
        init_base_iterator(&iter_ptr->base_iterator, 'C', 'T');
    }
}

// used to initialize the constant reverse iterator in vector.
void init_iterator_vector_const_rev(iterator_vector *iter_ptr, vector *ptr_container, char ch)
{
    iter_ptr->ptr_container = ptr_container;
    iter_ptr->ptr_vtable = &iter_vector_vtbl_rev;
    if (ch == 'H')
    {
        iter_ptr->index = 0;
        init_base_iterator(&iter_ptr->base_iterator, 'K', 'H');
    }
    else
    {
        iter_ptr->index = ptr_container->sz - 1;
        init_base_iterator(&iter_ptr->base_iterator, 'K', 'T');
    }
}