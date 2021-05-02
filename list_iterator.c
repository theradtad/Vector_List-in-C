#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "list_iterator.h"

int* element(iterator_list *iter_ptr)
{
    if(iter_ptr->index != NULL)
    {
        return &iter_ptr->index->val;
    }
    else
    {
        printf("\nError: Index out of range \n");
        exit(-1);
    }
}

void next(iterator_list* iter_ptr)
{
    if(iter_ptr->index != NULL)
    {
        iter_ptr->index = iter_ptr->index->next;
    }
}

void prev(iterator_list* iter_ptr)
{ 
    if(iter_ptr->index != NULL)
    {
        iter_ptr->index = iter_ptr->index->prev;
    }
}
bool is_begin(iterator_list* iter_ptr)
{
    if(iter_ptr->index == NULL)
        return true;
    return false;
}


bool compare(iterator_list* iter_ptr1, iterator_list iter_ptr2)
{
    if(iter_ptr1->type != iter_ptr2.type)
    {
        if(!(iter_ptr1->type == 'F' && iter_ptr2.type =='C') && !(iter_ptr1->type == 'C' && iter_ptr2.type =='F') && !(iter_ptr1->type == 'R' && iter_ptr2.type =='K') && !(iter_ptr1->type == 'K' && iter_ptr2.type =='R'))  
            fprintf(stderr, "Error: Incomparable types \n");
            exit(-1);
    }
    if(iter_ptr1->index == iter_ptr2.index)
        return true;
    return false;
}

void init_iterator_list_fwd(iterator_list* iter_ptr, list *ptr_list, char ch)
{   
    iter_ptr->ptr_list = ptr_list;
    if(ch == 'H')
    {
        iter_ptr->index = ptr_list->head;
        iter_ptr->fwd_or_back = 'H';
    }
    else
    {
        iter_ptr->index = ptr_list->tail;
        iter_ptr->fwd_or_back = 'T';
    }
    iter_ptr->type = 'F';
    iter_ptr->element = element;
    iter_ptr->next = next;
    iter_ptr->prev = prev;
    iter_ptr->is_begin = is_begin;
    iter_ptr->is_end = is_begin;
    iter_ptr->compare = compare;
}

void init_iterator_list_rev(iterator_list* iter_ptr, list *ptr_list, char ch)
{
    iter_ptr->ptr_list = ptr_list;
    if(ch == 'H')
    {
        iter_ptr->index = ptr_list->head;
        iter_ptr->fwd_or_back = 'H';
    }
    else
    {
        iter_ptr->index = ptr_list->tail;
        iter_ptr->fwd_or_back = 'T';
    }
    iter_ptr->type = 'R';
    iter_ptr->element = element;
    iter_ptr->next = prev;
    iter_ptr->prev = next;
    iter_ptr->is_begin = is_begin;
    iter_ptr->is_end = is_begin;
    iter_ptr->compare = compare;
}

void init_iterator_list_const(iterator_list* iter_ptr, list *ptr_list, char ch)
{
    iter_ptr->ptr_list = ptr_list;
    if(ch == 'H')
    {
        iter_ptr->index = ptr_list->head;
        iter_ptr->fwd_or_back = 'H';
    }
    else
    {
        iter_ptr->index = ptr_list->tail;
        iter_ptr->fwd_or_back = 'T';
    }
    iter_ptr->type = 'C';
    iter_ptr->element = element;
    iter_ptr->next = prev;
    iter_ptr->prev = next;
    iter_ptr->is_begin = is_begin;
    iter_ptr->is_end = is_begin;
    iter_ptr->compare = compare;
}

void init_iterator_list_const_rev(iterator_list* iter_ptr, list *ptr_list, char ch)
{
    iter_ptr->ptr_list = ptr_list;
    if(ch == 'H')
    {
        iter_ptr->index = ptr_list->head;
        iter_ptr->fwd_or_back = 'H';
    }
    else
    {
        iter_ptr->index = ptr_list->tail;
        iter_ptr->fwd_or_back = 'T';
    }
    iter_ptr->type = 'K';
    iter_ptr->element = element;
    iter_ptr->next = prev;
    iter_ptr->prev = next;
    iter_ptr->is_begin = is_begin;
    iter_ptr->is_end = is_begin;
    iter_ptr->compare = compare;
}