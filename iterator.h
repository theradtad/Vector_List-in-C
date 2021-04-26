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
    int* (*element)(iterator_list *iter_ptr);
    void (*next)(iterator_list *iter_ptr);
    void (*prev)(iterator_list *iter_ptr);
    bool (*is_end)(iterator_list *iter_ptr);
};

void init_iterator_list(iterator_list* iter_ptr, list *ptr_list, char ch);

#endif