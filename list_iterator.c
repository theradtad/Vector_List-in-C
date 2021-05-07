#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "list_iterator.h"

// Returns the address of the current element to which the index points to.
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

// Moves the index pointer to the next element in the list.
static void next_list(iterator_list* iter_ptr)
{
    if(iter_ptr->index != NULL)
    {
        iter_ptr->index = iter_ptr->index->next;
    }
}

// Moves the index pointer to the previous element in the list.
static void prev_list(iterator_list* iter_ptr)
{ 
    if(iter_ptr->index != NULL)
    {
        iter_ptr->index = iter_ptr->index->prev;
    }
}

// Checks if the index is NULL which would indicate the index is past the last element or before the first element.
static bool is_begin_list(iterator_list* iter_ptr)
{
    if(iter_ptr->index == NULL)
        return true;
    return false;
}

// Compares two iterator objects, comparision works only if both iterator_list objects are forward iterators or both are reverse iterators.
static bool compare_list(iterator_list* iter_ptr1, iterator_list iter_ptr2)
{
    if(iter_ptr1->base_iterator.type != iter_ptr2.base_iterator.type)
    {  
        printf("Error: Incomparable base_iterator Types \n");
        exit(-1);
    }
    if(iter_ptr1->index == iter_ptr2.index)
        return true;
    return false;
}

// Resets the index pointer to the initial element that it was pointing to before next or prev was called on it.
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

// used to initialize a forward iterator in the list. Calls base iterators init as well.
// The argument ch is used to indicate wether begin member function of list is calling this function or wether end member function of list is calling it. 
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

// used to initialize the reverse iterator in list.
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