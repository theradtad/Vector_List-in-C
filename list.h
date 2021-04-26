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
    void (*assign)(list *ptr_list, int count, int value); 
    void (*remove)(list *ptr_list,int value);
    void (*reverse)(list *ptr_list);
    int (*size)(const list *ptr_list);
    void (*sort)(list *ptr_list);
    void (*clear)(list *ptr_list);
    void (*swap)(list *ptr_list,list *ptr_list2);
    iterator_list (*begin)(list *ptr_list);
    iterator_list (*end)(list *ptr_list);
};

void init_list(list* ptr_list);


#endif

// still need to add:
// list::begin() and list::end() in C++ STL– begin() function returns an iterator pointing to the first element of the list
// end()– end() function returns an iterator pointing to the theoretical last element which follows the last element.
// list rbegin() and rend() function in C++ STL– rbegin() returns a reverse iterator which points to the last element of the list. 
// rend() returns a reverse iterator which points to the position before the beginning of the list.
// list cbegin() and cend() function in C++ STL– cbegin() returns a constant random access iterator which points to the beginning of the list. 
// cend() returns a constant random access iterator which points to the end of the list.
// list crbegin() and crend() function in C++ STL– crbegin() returns a constant reverse iterator which points to the last element of the list i.e reversed beginning of container.
// crend() returns a constant reverse iterator which points to the theoretical element preceding the first element in the list i.e. the reverse end of the list.
// insert(pos_iter, ele_num, ele) pos_iter: iterator, ele_num: number of elements to insert, ele: value to be copied or moved to inserted elements
// (returns pointer to newly inserted ele)

//erase()