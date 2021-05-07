#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include "list_iterator.h"

typedef iterator_list iterator_list;

// Structure that represents a node in the doubly linked list. It has prev and next pointer pointing to the previous and next element.
typedef struct node
{
    int val;
    struct node* prev;
    struct node* next;
}node;


typedef struct list list;
typedef struct list_vtable list_vtable;

// Represents a doubly linked list, that is meant serve as a replication of the list container in stl.
// Head points the first node in the doubly linked list.
// Tail points to the last node in the doubly linked list.
// ptr_vtable is the vtable pointer that points to all the functions of the list.
struct list
{
    node* head;
    node* tail;
    int sz;
    list_vtable *ptr_vtable;
};

// Vtable structure that points to all functions of the list class.
struct list_vtable
{
    int (*front)(const list *ptr_list);
    int (*back)(const list *ptr_list);
    void (*push_front)(list *ptr_list,int g);
    void (*push_back)(list *ptr_list,int g);
    void (*pop_front)(list *ptr_list);
    void (*pop_back)(list *ptr_list);
    bool (*empty)(const list *ptr_list);
    void (*insert)(list *ptr_list, iterator_list iter_ptr,int num_ele, int ele);
    void (*erase)(list *ptr_list, iterator_list iter_ptr);
    void (*assign)(list *ptr_list, int count, int value); 
    void (*remove)(list *ptr_list,int value);
    void (*remove_if)(list *ptr_list, bool (*fn)(int value));
    void (*reverse)(list *ptr_list);
    int (*size)(const list *ptr_list);
    void (*resize)(list *ptr_list, int count, int value);
    void (*sort)(list *ptr_list);
    void (*clear)(list *ptr_list);
    void (*unique)(list *ptr_list);
    void (*swap)(list *ptr_list,list *ptr_list2);
    void (*emplace_front)(list *ptr_list,int g);
    void (*emplace_back)(list *ptr_list,int g);
    void (*merge)(list *ptr_list,list *ptr_list2);
    void (*splice)(list *ptr_list, iterator_list iter_ptr, list *ptr_list2);
    iterator_list* (*emplace)(list *ptr_list, iterator_list iter_ptr, int ele);
    iterator_list* (*begin)(list *ptr_list);
    iterator_list* (*end)(list *ptr_list);
    iterator_list* (*rbegin)(list *ptr_list);
    iterator_list* (*rend)(list *ptr_list);
};

void init_list(list* ptr_list);

#endif

// need to implement template type