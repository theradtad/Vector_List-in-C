#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include "algorithms.h"

void reverse(iterator* start, iterator* end)
{
    int sz = 0;
    for(;!(start->ptr_vtable->is_end(start)); start->ptr_vtable->next(start))
    {
        ++sz;
    }

    start->ptr_vtable->reset(start);
    for(int i=0;i<(sz/2);++i)
    {
        void *temp = *(start->ptr_vtable->element(start));
        *(start->ptr_vtable->element(start)) = *(end->ptr_vtable->element(end));
        *(end->ptr_vtable->element(end)) = temp;

        start->ptr_vtable->next(start);
        end->ptr_vtable->prev(end);
    }

    end->ptr_vtable->reset(end);
    start->ptr_vtable->reset(start);
}

void **min_element(iterator* start, iterator* end)
{
    int maxi = INT_MAX;
    void **min = &maxi;

    for(;!(start->ptr_vtable->is_end(start)); start->ptr_vtable->next(start))
    {
        if(*(start->ptr_vtable->element(start)) < *min)
        {
            min = (start->ptr_vtable->element(start));
        }
    }
    start->ptr_vtable->reset(start);
    return min;
}

int count(iterator* start, iterator* end, void *x)
{
    int cnt = 0;
    for(;!(start->ptr_vtable->is_end(start)); start->ptr_vtable->next(start))
    {
        if(*(start->ptr_vtable->element(start)) == x)
        {
            ++cnt;
        }
    }
    start->ptr_vtable->reset(start);
    return cnt;
}


void sort(iterator *start, iterator *end)
{
    int i=0;
    while(!(start->ptr_vtable->is_end(start)))
    {
        void **cur = (start->ptr_vtable->element(start));
        start->ptr_vtable->next(start);

        while (!(start->ptr_vtable->is_end(start)))
        {
            if(*(start->ptr_vtable->element(start)) < *cur)
            {
                void *temp = *cur;
                *cur = *(start->ptr_vtable->element(start));
                *(start->ptr_vtable->element(start)) = temp;
            }
            start->ptr_vtable->next(start);
        }
        start->ptr_vtable->reset(start);
        for(int j=0;j<=i;++j)
        {
            start->ptr_vtable->next(start);
        }
        ++i;
    }
    start->ptr_vtable->reset(start);
}

void **max_element(iterator *start, iterator *end)
{
    void **max = (start->ptr_vtable->element(start));

    for(;!(start->ptr_vtable->is_end(start)); start->ptr_vtable->next(start))
    {
        if(*(start->ptr_vtable->element(start)) > *max)
        {
            max = (start->ptr_vtable->element(start));
        }
    }
    start->ptr_vtable->reset(start);
    return max;
}

void print_container(iterator *start, iterator *end)
{
    for (; !(start->ptr_vtable->is_end(start)); start->ptr_vtable->next(start))
    {
        printf("%d", *(start->ptr_vtable->element(start)));
    }
    start->ptr_vtable->reset(start);
    printf("\n");
}

int accumulate(iterator *start, iterator *end, int initial_sum)
{
    int result = initial_sum;
    for (; !(start->ptr_vtable->is_end(start)); start->ptr_vtable->next(start))
    {
        result += *((int *)(start->ptr_vtable->element(start)));
    }
    start->ptr_vtable->reset(start);
    return result;
}

void replace(iterator *start, iterator *end, void *old_value, void *new_value)
{
    for (; !(start->ptr_vtable->is_end(start)); start->ptr_vtable->next(start))
    {
        if (*(start->ptr_vtable->element(start)) == old_value)
        {
            *(start->ptr_vtable->element(start)) = new_value;
        }
    }
    start->ptr_vtable->reset(start);
}

bool equal(iterator *start1, iterator *end1, iterator *start2)
{
    while (!start1->ptr_vtable->is_end(start1))
    {
        if (start2->ptr_vtable->is_end(start2))
            return false;
        if (*(start1->ptr_vtable->element(start1)) != *(start2->ptr_vtable->element(start2)))
            return false;
        start1->ptr_vtable->next(start1);
        start2->ptr_vtable->next(start2);
    }
    return true;
}