#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "iterator.h"

int* element(iterator_list *iter_ptr)
{
    if(iter_ptr->index != NULL)
    {
        return &iter_ptr->index->val;
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

bool is_end(iterator_list* iter_ptr)
{
    if(iter_ptr->index == NULL)
        return true;
    return false;
}

void init_iterator_list(iterator_list* iter_ptr, list *ptr_list, char ch)
{   
    if(ch == 'H')
    {
        iter_ptr->ptr_list = ptr_list;
        iter_ptr->index = ptr_list->head;
    }
    else
    {
        iter_ptr->ptr_list = ptr_list;
        iter_ptr->index = ptr_list->tail;
    }
    
    iter_ptr->element = element;
    iter_ptr->next = next;
    iter_ptr->prev = prev;
    iter_ptr->is_end = is_end;
}