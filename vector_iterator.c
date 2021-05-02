#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "vector_iterator.h"

int* element_vector(iterator_vector *iter_ptr)
{
    if((iter_ptr->index >= 0) && (iter_ptr->index < iter_ptr->ptr_vector->sz))
    {
        return &(iter_ptr->ptr_vector->arr[iter_ptr->index]);
    }
    else
    {
        printf("\nError: Index out of range \n");
        exit(-1);
    }
}

void next_vector(iterator_vector* iter_ptr)
{
    if((iter_ptr->index >= 0) && (iter_ptr->index < iter_ptr->ptr_vector->sz))
    {
        ++iter_ptr->index;
    }
}

void prev_vector(iterator_vector* iter_ptr)
{ 
    if((iter_ptr->index >= 0) && (iter_ptr->index < iter_ptr->ptr_vector->sz))
    {
        --iter_ptr->index;
    }
}
bool is_begin_vector(iterator_vector* iter_ptr)
{
    if(iter_ptr->index < 0)
        return true;
    return false;
}

bool is_end_vector(iterator_vector* iter_ptr)
{
    if(iter_ptr->index >= iter_ptr->ptr_vector->sz)
        return true;
    return false;
}

bool compare_vector(iterator_vector* iter_ptr1, iterator_vector iter_ptr2)
{
    if(iter_ptr1->type != iter_ptr2.type)
    {
        if(!(iter_ptr1->type == 'F' && iter_ptr2.type =='C') && !(iter_ptr1->type == 'C' && iter_ptr2.type =='F') && !(iter_ptr1->type == 'R' && iter_ptr2.type =='K') && !(iter_ptr1->type == 'K' && iter_ptr2.type =='R'))  
            printf("\nError: Incomparable types \n");
            exit(-1);
    }
    if(iter_ptr1->index == iter_ptr2.index)
        return true;
    return false;
}

void init_iterator_vector_fwd(iterator_vector* iter_ptr, vector *ptr_vector, char ch)
{   
    iter_ptr->ptr_vector = ptr_vector;
    if(ch == 'H')
    {
        iter_ptr->index = 0;
        iter_ptr->fwd_or_back = 'H';
    }
    else
    {
        iter_ptr->index = ptr_vector->sz - 1;
        iter_ptr->fwd_or_back = 'T';
    }
    iter_ptr->type = 'F';
    iter_ptr->element = element_vector;
    iter_ptr->next = next_vector;
    iter_ptr->prev = prev_vector;
    iter_ptr->is_begin = is_begin_vector;
    iter_ptr->is_end = is_end_vector;
    iter_ptr->compare = compare_vector;
}

void init_iterator_vector_rev(iterator_vector* iter_ptr, vector *ptr_vector, char ch)
{
    iter_ptr->ptr_vector = ptr_vector;
    if(ch == 'H')
    {
        iter_ptr->index = 0;
        iter_ptr->fwd_or_back = 'H';
    }
    else
    {
        iter_ptr->index = ptr_vector->sz - 1;
        iter_ptr->fwd_or_back = 'T';
    }
    iter_ptr->type = 'R';
    iter_ptr->element = element_vector;
    iter_ptr->next = prev_vector;
    iter_ptr->prev = next_vector;
    iter_ptr->is_begin = is_end_vector;
    iter_ptr->is_end = is_begin_vector;
    iter_ptr->compare = compare_vector;
}

void init_iterator_vector_const(iterator_vector* iter_ptr, vector *ptr_vector, char ch)
{
    iter_ptr->ptr_vector = ptr_vector;
    if(ch == 'H')
    {
        iter_ptr->index = 0;
        iter_ptr->fwd_or_back = 'H';
    }
    else
    {
        iter_ptr->index = ptr_vector->sz - 1;
        iter_ptr->fwd_or_back = 'T';
    }
    iter_ptr->type = 'C';
    iter_ptr->element = element_vector;
    iter_ptr->next = prev_vector;
    iter_ptr->prev = next_vector;
    iter_ptr->is_begin = is_begin_vector;
    iter_ptr->is_end = is_end_vector;
    iter_ptr->compare = compare_vector;
}

void init_iterator_vector_const_rev(iterator_vector* iter_ptr, vector *ptr_vector, char ch)
{
    iter_ptr->ptr_vector = ptr_vector;
    if(ch == 'H')
    {
        iter_ptr->index = 0;
        iter_ptr->fwd_or_back = 'H';
    }
    else
    {
        iter_ptr->index = ptr_vector->sz - 1;
        iter_ptr->fwd_or_back = 'T';
    }
    iter_ptr->type = 'K';
    iter_ptr->element = element_vector;
    iter_ptr->next = prev_vector;
    iter_ptr->prev = next_vector;
    iter_ptr->is_begin = is_end_vector;
    iter_ptr->is_end = is_begin_vector;
    iter_ptr->compare = compare_vector;
}