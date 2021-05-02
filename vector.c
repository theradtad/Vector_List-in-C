#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

static int size(vector *ptr_vect)
{
    return ptr_vect->sz;
}

static int capacity(vector *ptr_vect)
{
    return ptr_vect->cap;
}
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

static bool empty(vector *ptr_vect)
{
    if (ptr_vect->sz == 0)
        return true;
    return false;
}

static void shrink_to_fit(vector *ptr_vect)
{
    int *arr = realloc(ptr_vect->arr, sizeof(int) * ptr_vect->sz);
    ptr_vect->cap = ptr_vect->sz;
    ptr_vect->arr = arr;
}

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
static void pop_back(vector *ptr_vect)
{
    if (ptr_vect->sz > 0)
    {
        --ptr_vect->sz;
    }
}

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

    free(ptr_vect->arr);
    ptr_vect->arr = temp_arr;
}

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

static void clear(vector *ptr_vect)
{
    ptr_vect->sz = 0;
}

static int *at(vector *ptr_vect, int position)
{
    if (ptr_vect->sz <= position || position < 0)
    {
        fprintf(stderr, "Out of Range\n");
        exit(-1);
    }

    return &ptr_vect->arr[position];
}

static int *front(vector *ptr_vect)
{
    if (ptr_vect->sz == 0)
    {
        fprintf(stderr, "Error: Access to Empty list \n");
        exit(-1);
    }

    return &ptr_vect->arr[0];
}
static int *back(vector *ptr_vect)
{
    if (ptr_vect->sz == 0)
    {
        fprintf(stderr, "Error: Access to Empty list \n");
        exit(-1);
    }

    return &ptr_vect->arr[ptr_vect->sz - 1];
}

static void swap(vector *ptr_vect1, vector *ptr_vect2)
{
    vector temp;
    temp = *ptr_vect1;
    *ptr_vect1 = *ptr_vect2;
    *ptr_vect2 = temp;
}

int *data(vector *ptr_vect)
{
    return ptr_vect->arr;
}

iterator_vector emplace(vector *ptr_vect, iterator_vector ptr_iter, int element)
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
}

iterator_vector begin(vector *ptr_vect)
{
    iterator_vector it;
    init_iterator_vector_fwd(&it, ptr_vect);
    it.is_const = false;
    return it;
}

iterator_vector end(vector *ptr_vect)
{
    iterator_vector it;
    init_iterator_vector_fwd(&it, ptr_vect);

    if (it.ptr_vector->sz == 0)
        it.index = -1;
    else
        it.index = it.ptr_vector->sz - 1;

    it.is_const = false;
    return it;
}

iterator_vector rbegin(vector *ptr_vect)
{
    iterator_vector it;
    init_iterator_vector_rev(&it, ptr_vect);
    it.is_const = false;
    return it;
}

iterator_vector rend(vector *ptr_vect)
{
    iterator_vector it;
    init_iterator_vector_rev(&it, ptr_vect);
    it.is_const = false;
    it.index = 0;
    return it;
}

iterator_vector cbegin(vector *ptr_vect)
{
    iterator_vector it;
    init_iterator_vector_fwd(&it, ptr_vect);
    it.is_const = true;
    return it;
}

iterator_vector cend(vector *ptr_vect)
{
    iterator_vector it;
    init_iterator_vector_fwd(&it, ptr_vect);
    it.index = it.ptr_vector->sz - 1;
    it.is_const = true;
    return it;
}

iterator_vector crbegin(vector *ptr_vect)
{
    iterator_vector it;
    init_iterator_vector_rev(&it, ptr_vect);
    it.is_const = true;
    return it;
}

iterator_vector crend(vector *ptr_vect)
{
    iterator_vector it;
    init_iterator_vector_rev(&it, ptr_vect);
    it.is_const = true;
    it.index = 0;
    return it;
}

void init_vector(vector *ptr_vect)
{
    ptr_vect->arr = NULL;
    ptr_vect->sz = 0;
    ptr_vect->cap = 0;
    ptr_vect->size = size;
    ptr_vect->capacity = capacity;
    ptr_vect->resize = resize;
    ptr_vect->empty = empty;
    ptr_vect->shrink_to_fit = shrink_to_fit;
    ptr_vect->assign = assign;
    ptr_vect->push_back = push_back;
    ptr_vect->pop_back = pop_back;
    ptr_vect->insert = insert;
    ptr_vect->erase = erase;
    ptr_vect->clear = clear;
    ptr_vect->swap = swap;
    ptr_vect->at = at;
    ptr_vect->front = front;
    ptr_vect->back = back;
    ptr_vect->data = data;
    ptr_vect->emplace = emplace;
    ptr_vect->begin = begin;
    ptr_vect->end = end;
    ptr_vect->rbegin = rbegin;
    ptr_vect->rend = rend;
    ptr_vect->cbegin = cbegin;
    ptr_vect->cend = cend;
    ptr_vect->crbegin = crbegin;
    ptr_vect->crend = crend;
}