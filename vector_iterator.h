#ifndef VECTOR_ITERATOR_H
#define VECTOR_ITERATOR_H

#include <stdbool.h>

typedef struct iterator_vector iterator_vector;
typedef struct vector vector;

struct iterator_vector
{
    vector *ptr_vector;
    int *(*element)(iterator_vector *iter_ptr);
    int index;
    char type_of_movement;
    bool is_const;
    void (*next)(iterator_vector *iter_ptr);
    void (*prev)(iterator_vector *iter_ptr);
    bool (*compare)(iterator_vector *iter_ptr1, iterator_vector *iter_ptr2);
};

void init_iterator_vector_fwd(iterator_vector *iter_ptr, vector *ptr_vector);
void init_iterator_vector_rev(iterator_vector *iter_ptr, vector *ptr_vector);

#endif