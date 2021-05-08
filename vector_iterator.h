#ifndef VECTOR_ITERATOR_H
#define VECTOR_ITERATOR_H

#include <stdbool.h>
#include "iterator.h"

typedef struct vector vector;
typedef struct iterator_vector_vtable iterator_vector_vtable;

// vector iterator class: Derived class whose Base class is iterator.
// It contains a vtable pointer to replicate concepts of OOP in C.
// ptr_container is a pointer to the vector.
// index is a pointer to each element of the list.
// base iterator is the object of the base class (iterator).
typedef struct
{
    iterator_vector_vtable *ptr_vtable;
    iterator base_iterator;
    vector *ptr_container;
    int index;
} iterator_vector;

// structure that represents all the functions of the iterator_vector class.
struct iterator_vector_vtable
{
    int *(*element)(iterator_vector *iter_ptr);
    void (*next)(iterator_vector *iter_ptr);
    void (*prev)(iterator_vector *iter_ptr);
    bool (*is_begin)(iterator_vector *iter_ptr);
    bool (*is_end)(iterator_vector *iter_ptr);
    bool (*compare)(iterator_vector *iter_ptr1, iterator_vector iter_ptr2);
    void (*reset)(iterator_vector *iter_ptr);
};

void init_iterator_vector_fwd(iterator_vector *iter_ptr, vector *ptr_container, char ch);
void init_iterator_vector_rev(iterator_vector *iter_ptr, vector *ptr_container, char ch);
#endif