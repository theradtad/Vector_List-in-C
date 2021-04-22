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
    for(int i=0;i<n;++i)
    {
        arr[i] = value;
    }
    ptr_vect->arr = arr;
    ptr_vect->cap = n;
    ptr_vect->sz = n;
}

static bool empty(vector *ptr_vect)
{
    if(ptr_vect->sz == 0)
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
    if(sz > ptr_vect->sz)
    {
        int *arr = realloc(ptr_vect->arr, sizeof(int) * sz);
        for(int i=0;i<sz;++i)
        {
            arr[i] = value;
        }
        ptr_vect->cap = sz;
        ptr_vect->arr = arr;
    }
    else
    {
        for(int i=0;i<sz;++i)
        {
            ptr_vect->arr[i] = value;
        }
    }
    ptr_vect->sz = sz;
}
static void push_back(vector *ptr_vect, int g)
{
    if(ptr_vect->sz < ptr_vect->cap)
    {
        ptr_vect->arr[ptr_vect->sz] = g;
        ++ptr_vect->sz;
    }
    else
    {
        int *arr = realloc(ptr_vect->arr, sizeof(int) * (ptr_vect->sz+1));
        ptr_vect->arr = arr;
        ptr_vect->sz+=1;
        ptr_vect->cap+=1;
        ptr_vect->arr[ptr_vect->sz - 1] = g;
    }
}
static void pop_back(vector *ptr_vect)
{
    if(ptr_vect->sz > 0)
    {
        --ptr_vect->sz;
    }
}

static void insert(vector *ptr_vect, int position, int val)
{
    ;
}

static void erase(vector *ptr_vect, int position)
{
    ;
}

static void clear(vector *ptr_vect)
{
    ptr_vect->sz = 0;
}

static int at(vector *ptr_vect, int position)
{
    if(ptr_vect->sz <= position || position < 0)
    {
        fprintf(stderr, "Out of Range\n");
        exit(-1);
    }

    return ptr_vect->arr[position];
}
static int front(vector *ptr_vect)
{
    if(ptr_vect->sz == 0)
    {
        fprintf(stderr, "Error: Access to Empty list \n");
        exit(-1);
    }

    return ptr_vect->arr[0];
    
}
static int back(vector *ptr_vect)
{
    if(ptr_vect->sz == 0)
    {
        fprintf(stderr, "Error: Access to Empty list \n");
        exit(-1);
    }

    return ptr_vect->arr[ptr_vect->sz - 1];
}

int* data(vector *ptr_vect)
{
    return ptr_vect->arr;
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
    ptr_vect->at = at;
    ptr_vect->front = front;
    ptr_vect->back = back;
    ptr_vect->data = data;
}