#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "list_iterator.h"

static int* element_list(iterator_list *iter_ptr)
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

static void next_list(iterator_list* iter_ptr)
{
    if(iter_ptr->index != NULL)
    {
        iter_ptr->index = iter_ptr->index->next;
    }
}

static void prev_list(iterator_list* iter_ptr)
{ 
    if(iter_ptr->index != NULL)
    {
        iter_ptr->index = iter_ptr->index->prev;
    }
}

static bool is_begin_list(iterator_list* iter_ptr)
{
    if(iter_ptr->index == NULL)
        return true;
    return false;
}


static bool compare_list(iterator_list* iter_ptr1, iterator_list iter_ptr2)
{
    if(iter_ptr1->base_iterator.type != iter_ptr2.base_iterator.type)
    {
        if(!(iter_ptr1->base_iterator.type == 'F' && iter_ptr2.base_iterator.type =='C') && !(iter_ptr1->base_iterator.type == 'C' && iter_ptr2.base_iterator.type =='F') && !(iter_ptr1->base_iterator.type == 'R' && iter_ptr2.base_iterator.type =='K') && !(iter_ptr1->base_iterator.type == 'K' && iter_ptr2.base_iterator.type =='R'))  
            fprintf(stderr, "Error: Incomparable base_iterator Types \n");
            exit(-1);
    }
    if(iter_ptr1->index == iter_ptr2.index)
        return true;
    return false;
}

static void reset_list(iterator_list *iter_ptr)
{
    if(iter_ptr->base_iterator.type_of_movement == 'H')
    {
        iter_ptr->index = iter_ptr->ptr_container->head;
    }
    else
    {
        iter_ptr->index = iter_ptr->ptr_container->tail;
    }
}

static iterator_list_vtable iter_list_vtbl_fwd = 
{
    element_list,
    next_list,
    prev_list,
    is_begin_list,
    is_begin_list,
    compare_list,
    reset_list
};

static iterator_list_vtable iter_list_vtbl_rev = 
{
    element_list,
    prev_list,
    next_list,
    is_begin_list,
    is_begin_list,
    compare_list,
    reset_list
};

void init_iterator_list_fwd(iterator_list* iter_ptr, list *ptr_container, char ch)
{   
    if(ch == 'H')
    {
        iter_ptr->index = ptr_container->head;
        init_base_iterator(&iter_ptr->base_iterator,'F','H');
    }
    else
    {
        iter_ptr->index = ptr_container->tail;
        init_base_iterator(&iter_ptr->base_iterator,'F','T');
    }
    iter_ptr->ptr_vtable = &iter_list_vtbl_fwd;
    iter_ptr->ptr_container = ptr_container;
}

void init_iterator_list_rev(iterator_list* iter_ptr, list *ptr_container, char ch)
{
    if(ch == 'H')
    {
        iter_ptr->index = ptr_container->head;
        init_base_iterator(&iter_ptr->base_iterator,'R','H');
    }
    else
    {
        iter_ptr->index = ptr_container->tail;
        init_base_iterator(&iter_ptr->base_iterator,'R','T');
    }
    iter_ptr->ptr_vtable = &iter_list_vtbl_rev;
    iter_ptr->ptr_container = ptr_container;
}

void init_iterator_list_const(iterator_list* iter_ptr, list *ptr_container, char ch)
{
    if(ch == 'H')
    {
        iter_ptr->index = ptr_container->head;
        init_base_iterator(&iter_ptr->base_iterator,'C','H');
    }
    else
    {
        iter_ptr->index = ptr_container->tail;
        init_base_iterator(&iter_ptr->base_iterator,'C','T');
    }
    iter_ptr->ptr_vtable = &iter_list_vtbl_fwd;
    iter_ptr->ptr_container = ptr_container;
}

void init_iterator_list_const_rev(iterator_list* iter_ptr, list *ptr_container, char ch)
{
    if(ch == 'H')
    {
        iter_ptr->index = ptr_container->head;
        init_base_iterator(&iter_ptr->base_iterator,'K','H');
    }
    else
    {
        iter_ptr->index = ptr_container->tail;
        init_base_iterator(&iter_ptr->base_iterator,'K','T');
    }
    iter_ptr->ptr_vtable = &iter_list_vtbl_rev;
    iter_ptr->ptr_container = ptr_container;
}