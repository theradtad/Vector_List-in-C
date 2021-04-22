#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>

typedef struct vector vector;

struct vector
{
    int *arr;
    int sz;
    int cap;
    int (*size)(vector *ptr_vect);
    int (*capacity)(vector *ptr_vect);
    void (*resize)(vector *ptr_vect, int n, int val);
    bool (*empty)(vector *ptr_vect);
    void (*shrink_to_fit)(vector *ptr_vect);
    void (*assign)(vector *ptr_vect, int sz, int value);
    void (*push_back)(vector *ptr_vect, int g);
    void (*pop_back)(vector *ptr_vect);
    void (*insert)(vector *ptr_vect, int position, int val);
    void (*erase)(vector *ptr_vect, int position);
    void (*clear)(vector *ptr_vect);
    int (*at)(vector *ptr_vect, int position);
    int (*front)(vector *ptr_vect);
    int (*back)(vector *ptr_vect);
    int* (*data)(vector *ptr_vect);
};

void init_vector(vector* ptr_vect);
#endif

//reserve
// iterator functions even insert and erase
// erase, resize and assign being polymorphic
//swap
// emplace and emplace_back
