#ifndef ITERATOR_H
#define ITERATOR_H

#include<stdbool.h>

typedef struct list list;
typedef struct node node;

typedef struct iterator_list iterator_list;

struct iterator_list
{
    list *ptr_list;
    node *index;
    char type;
    char fwd_or_back;
    int* (*element)(iterator_list *iter_ptr);
    void (*next)(iterator_list *iter_ptr);
    void (*prev)(iterator_list *iter_ptr);
    bool (*is_end)(iterator_list *iter_ptr);
    bool (*is_begin)(iterator_list *iter_ptr);
    bool (*compare)(iterator_list *iter_ptr1, iterator_list iter_ptr2);
};

void init_iterator_list_fwd(iterator_list* iter_ptr, list *ptr_list, char ch);
void init_iterator_list_rev(iterator_list* iter_ptr, list *ptr_list, char ch);
void init_iterator_list_const(iterator_list* iter_ptr, list *ptr_list, char ch);
void init_iterator_list_const_rev(iterator_list* iter_ptr, list *ptr_list, char ch);

#endif