#ifndef VECTOR_H
#define VECTOR_H
#include "vector_iterator.h"

#include <stdbool.h>

typedef struct vector vector;
typedef struct vector_vtable vector_vtable;

//the structure for vector
struct vector
{
    int *arr;
    int sz;
    int cap;
    vector_vtable *ptr_vtable;
};

//structure for the vtable for vector that has function pointers.
struct vector_vtable
{
    int (*size)(vector *ptr_vect);
    int (*capacity)(vector *ptr_vect);
    void (*resize)(vector *ptr_vect, int n, int val);
    bool (*empty)(vector *ptr_vect);
    void (*shrink_to_fit)(vector *ptr_vect);
    void (*assign)(vector *ptr_vect, int sz, int value);
    void (*push_back)(vector *ptr_vect, int g);
    void (*pop_back)(vector *ptr_vect);
    void (*insert)(vector *ptr_vect, iterator_vector ptr_iter, int val);
    void (*erase)(vector *ptr_vect, iterator_vector ptr_iter);
    void (*clear)(vector *ptr_vect);
    void (*swap)(vector *ptr_vect1, vector *ptr_vect2);
    int *(*at)(vector *ptr_vect, int position);
    int *(*front)(vector *ptr_vect);
    int *(*back)(vector *ptr_vect);
    int *(*data)(vector *ptr_vect);
    iterator_vector (*emplace)(vector *ptr_vect, iterator_vector ptr_iter, int element);
    void (*emplace_back)(vector *ptr_vect, int element);
    iterator_vector *(*begin)(vector *ptr_vect);
    iterator_vector *(*end)(vector *ptr_vect);
    iterator_vector *(*rbegin)(vector *ptr_vect);
    iterator_vector *(*rend)(vector *ptr_vect);
    iterator_vector *(*cbegin)(vector *ptr_vect);
    iterator_vector *(*cend)(vector *ptr_vect);
    iterator_vector *(*crbegin)(vector *ptr_vect);
    iterator_vector *(*crend)(vector *ptr_vect);
};

void init_vector(vector *ptr_vect);
void init_vector_vtable(vector_vtable *ptr_vtable);
#endif

//reserve
// iterator functions even insert and erase
// erase, resize and assign being polymorphic
//swap
// emplace and emplace_back
