#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef struct iterator_list iterator_list;

typedef struct node
{
    int val;
    struct node* prev;
    struct node* next;
}node;


typedef struct list list;

struct list
{
    node* head;
    node* tail;
    int sz;
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
    iterator_list (*emplace)(list *ptr_list, iterator_list iter_ptr, int ele);
    iterator_list (*begin)(list *ptr_list);
    iterator_list (*end)(list *ptr_list);
    iterator_list (*rbegin)(list *ptr_list);
    iterator_list (*rend)(list *ptr_list);
    iterator_list (*cbegin)(list *ptr_list);
    iterator_list (*cend)(list *ptr_list);
    iterator_list (*crbegin)(list *ptr_list);
    iterator_list (*crend)(list *ptr_list);
};

void init_list(list* ptr_list);


#endif

// need to implement template type