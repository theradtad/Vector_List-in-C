#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

vector_vtable vector_vtbl;

//returns the size of the vector
static int size(vector *ptr_vect)
{
    return ptr_vect->sz;
}

//returns the capacity of the vector
static int capacity(vector *ptr_vect)
{
    return ptr_vect->cap;
}

//resizes the vector to a new size where in each element of the resized vector is equal to the parameter value.
static void resize(vector *ptr_vect, int n, int value)
{
    int *arr = realloc(ptr_vect->arr, sizeof(int) * n);
    for (int i = 0; i < n; ++i)
    {
        arr[i] = value;
    }
    ptr_vect->arr = arr;
    ptr_vect->cap = n;
    ptr_vect->sz = n;
}

//checks if the vector is empty
static bool empty(vector *ptr_vect)
{
    if (ptr_vect->sz == 0)
        return true;
    return false;
}

//to shrink the vector's capacity to the vector's size
static void shrink_to_fit(vector *ptr_vect)
{
    int *arr = realloc(ptr_vect->arr, sizeof(int) * ptr_vect->sz);
    ptr_vect->cap = ptr_vect->sz;
    ptr_vect->arr = arr;
}

//to set a vector with a specific size where each element is equal to the parameter value
static void assign(vector *ptr_vect, int sz, int value)
{
    if (sz > ptr_vect->sz)
    {
        int *arr = realloc(ptr_vect->arr, sizeof(int) * sz);
        for (int i = 0; i < sz; ++i)
        {
            arr[i] = value;
        }
        ptr_vect->cap = sz;
        ptr_vect->arr = arr;
    }
    else
    {
        for (int i = 0; i < sz; ++i)
        {
            ptr_vect->arr[i] = value;
        }
    }
    ptr_vect->sz = sz;
}

//adds an element to the end of the vector
static void push_back(vector *ptr_vect, int g)
{
    if (ptr_vect->sz < ptr_vect->cap)
    {
        ptr_vect->arr[ptr_vect->sz] = g;
        ++ptr_vect->sz;
    }
    else
    {
        int *arr = realloc(ptr_vect->arr, sizeof(int) * (ptr_vect->sz + 1));
        ptr_vect->arr = arr;
        ptr_vect->sz += 1;
        ptr_vect->cap += 1;
        ptr_vect->arr[ptr_vect->sz - 1] = g;
    }
}

//indirectly removes the last element of the vector by decreasing vector size by 1
static void pop_back(vector *ptr_vect)
{
    if (ptr_vect->sz > 0)
    {
        --ptr_vect->sz;
    }
}

//inserts an element to the vector to the position pointed to by the iterator passed as an arguement
static void insert(vector *ptr_vect, iterator_vector ptr_iter, int val)
{
    int *temp_arr = malloc(sizeof(int) * (ptr_vect->sz + 1));
    int position = ptr_iter.index;

    int i = 0;
    int j = 0;
    for (; i < position; ++i, ++j)
    {
        temp_arr[i] = ptr_vect->arr[i];
    }

    temp_arr[i] = val;
    ++i;

    for (; j < ptr_vect->sz; ++i, ++j)
    {
        temp_arr[i] = ptr_vect->arr[j];
    }

    ptr_vect->sz += 1;
    ptr_vect->cap += 1;

    free(ptr_vect->arr);
    ptr_vect->arr = temp_arr;
}

//removes an element from the vector from the position pointed to by the iterator passed as an arguement
static void erase(vector *ptr_vect, iterator_vector ptr_iter)
{
    int *temp_arr = malloc(sizeof(int) * (ptr_vect->sz - 1));
    int position = ptr_iter.index;

    int i = 0;
    int j = 0;
    for (; j < position; ++i, ++j)
    {
        temp_arr[i] = ptr_vect->arr[j];
    }

    ++j;

    for (; j < ptr_vect->sz; ++i, ++j)
    {
        temp_arr[i] = ptr_vect->arr[j];
    }

    ptr_vect->sz -= 1;

    free(ptr_vect->arr);
    ptr_vect->arr = temp_arr;
}

//indirectly clears the vector by setting the vector size to 0
static void clear(vector *ptr_vect)
{
    ptr_vect->sz = 0;
}

//returns the address of the vector element at the position specified as an arguement
static int *at(vector *ptr_vect, int position)
{
    if (ptr_vect->sz <= position || position < 0)
    {
        fprintf(stderr, "Out of Range\n");
        exit(-1);
    }

    return &ptr_vect->arr[position];
}

//returms the address of the first element of the vector
static int *front(vector *ptr_vect)
{
    if (ptr_vect->sz == 0)
    {
        fprintf(stderr, "Error: Access to Empty list \n");
        exit(-1);
    }

    return &ptr_vect->arr[0];
}

//returns the address of the last element of the vector
static int *back(vector *ptr_vect)
{
    if (ptr_vect->sz == 0)
    {
        fprintf(stderr, "Error: Access to Empty list \n");
        exit(-1);
    }

    return &ptr_vect->arr[ptr_vect->sz - 1];
}

//swaps 2 vectors
static void swap(vector *ptr_vect1, vector *ptr_vect2)
{
    vector temp;
    temp = *ptr_vect1;
    *ptr_vect1 = *ptr_vect2;
    *ptr_vect2 = temp;
}

//returns the address of the internal array the vector uses to store its elements
static int *data(vector *ptr_vect)
{
    return ptr_vect->arr;
}

//adds an element to the position specified by the iterator passed as an arguement by doing in-place.
static iterator_vector emplace(vector *ptr_vect, iterator_vector ptr_iter, int element)
{
    if (ptr_vect->sz < ptr_vect->cap)
    {
        int position = ptr_iter.index;
        for (int i = ptr_vect->sz; i > position; --i)
        {
            ptr_vect->arr[i] = ptr_vect->arr[i - 1];
        }
        ptr_vect->arr[position] = element;
        ptr_vect->sz += 1;
    }
    else if (ptr_vect->sz == ptr_vect->cap)
    {
        insert(ptr_vect, ptr_iter, element);
    }
    return ptr_iter;
}

//adds an element to the end of the vector by doing in-place.
static void emplace_back(vector *ptr_vect, int element)
{
    if (ptr_vect->sz < ptr_vect->cap)
    {
        int position = ptr_vect->sz;
        ptr_vect->arr[position] = element;
        ptr_vect->sz += 1;
    }
    else if (ptr_vect->sz == ptr_vect->cap)
    {
        ptr_vect->arr = realloc(ptr_vect->arr, sizeof(int) * (ptr_vect->sz + 1));
        int position = ptr_vect->sz;
        ptr_vect->arr[position] = element;
        ptr_vect->sz += 1;
        ptr_vect->cap += 1;
    }
}

//returns an iterator that points the beginning of the vector and that can move from left to right
iterator_vector *begin(vector *ptr_vect)
{
    iterator_vector *it = (iterator_vector *)malloc(sizeof(iterator_vector));
    init_iterator_vector_fwd(it, ptr_vect, 'H');
    return it;
}

//returns an iterator that points the end of the vector and that can move from left to right
iterator_vector *end(vector *ptr_vect)
{
    iterator_vector *it = (iterator_vector *)malloc(sizeof(iterator_vector));
    init_iterator_vector_fwd(it, ptr_vect, 'T');
    return it;
}

//returns an iterator that points the end of the vector and that can move from right to left
iterator_vector *rbegin(vector *ptr_vect)
{
    iterator_vector *it = (iterator_vector *)malloc(sizeof(iterator_vector));
    init_iterator_vector_rev(it, ptr_vect, 'T');
    return it;
}

//returns an iterator that points the beginning of the vector and that can move from right to left
iterator_vector *rend(vector *ptr_vect)
{
    iterator_vector *it = (iterator_vector *)malloc(sizeof(iterator_vector));
    init_iterator_vector_rev(it, ptr_vect, 'H');
    return it;
}

iterator_vector *cbegin(vector *ptr_vect)
{
    iterator_vector *it = (iterator_vector *)malloc(sizeof(iterator_vector));
    init_iterator_vector_const(it, ptr_vect, 'H');
    return it;
}

iterator_vector *cend(vector *ptr_vect)
{
    iterator_vector *it = (iterator_vector *)malloc(sizeof(iterator_vector));
    init_iterator_vector_const(it, ptr_vect, 'T');
    return it;
}

iterator_vector *crbegin(vector *ptr_vect)
{
    iterator_vector *it = (iterator_vector *)malloc(sizeof(iterator_vector));
    init_iterator_vector_const_rev(it, ptr_vect, 'T');
    return it;
}

iterator_vector *crend(vector *ptr_vect)
{
    iterator_vector *it = (iterator_vector *)malloc(sizeof(iterator_vector));
    init_iterator_vector_const_rev(it, ptr_vect, 'H');
    return it;
}

//sets the function pointers to the corresponding functions
void init_vector_vtable(vector_vtable *ptr_vtable)
{
    ptr_vtable->size = size;
    ptr_vtable->capacity = capacity;
    ptr_vtable->resize = resize;
    ptr_vtable->empty = empty;
    ptr_vtable->shrink_to_fit = shrink_to_fit;
    ptr_vtable->assign = assign;
    ptr_vtable->push_back = push_back;
    ptr_vtable->pop_back = pop_back;
    ptr_vtable->insert = insert;
    ptr_vtable->erase = erase;
    ptr_vtable->clear = clear;
    ptr_vtable->swap = swap;
    ptr_vtable->at = at;
    ptr_vtable->front = front;
    ptr_vtable->back = back;
    ptr_vtable->data = data;
    ptr_vtable->emplace = emplace;
    ptr_vtable->emplace_back = emplace_back;
    ptr_vtable->begin = begin;
    ptr_vtable->end = end;
    ptr_vtable->rbegin = rbegin;
    ptr_vtable->rend = rend;
    ptr_vtable->cbegin = cbegin;
    ptr_vtable->cend = cend;
    ptr_vtable->crbegin = crbegin;
    ptr_vtable->crend = crend;
}

//initializes the vector
void init_vector(vector *ptr_vect)
{
    ptr_vect->arr = NULL;
    ptr_vect->sz = 0;
    ptr_vect->cap = 0;
    ptr_vect->ptr_vtable = &vector_vtbl;
    init_vector_vtable(&vector_vtbl);
}