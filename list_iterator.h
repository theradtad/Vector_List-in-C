#ifndef LIST_ITERATOR_H
#define LIST_ITERATOR_H

#include <stdbool.h>
#include "iterator.h"

typedef struct list list;
typedef struct node node;
typedef struct iterator_list_vtable iterator_list_vtable;
typedef struct iterator_list iterator_list;

struct iterator_list
{
    iterator_list_vtable *ptr_vtable;
    iterator base_iterator;
    list *ptr_container;
    node* index;
};

struct iterator_list_vtable
{
    int *(*element)(iterator_list *iter_ptr);
    void (*next)(iterator_list *iter_ptr);
    void (*prev)(iterator_list *iter_ptr);
    bool (*is_begin)(iterator_list *iter_ptr);
    bool (*is_end)(iterator_list *iter_ptr);
    bool (*compare)(iterator_list *iter_ptr1, iterator_list iter_ptr2);
    void (*reset)(iterator_list *iter_ptr);
};

void init_iterator_list_fwd(iterator_list* iter_ptr, list *ptr_container, char ch);
void init_iterator_list_rev(iterator_list* iter_ptr, list *ptr_container, char ch);
void init_iterator_list_const(iterator_list* iter_ptr, list *ptr_container, char ch);
void init_iterator_list_const_rev(iterator_list* iter_ptr, list *ptr_container, char ch);

#endif