#include <stdio.h>
#include <stdlib.h>
#include "iterator.h"
#include <limits.h>

int *max_element(iterator *start, iterator *end)
{
    int max_ele = INT_MIN;
    int *result;

    // iterator *it;
    // start->ptr_vtable->copy(start, it);
    // printf("%d\n", *(it->ptr_vtable->element(it)));

    for (; !(start->ptr_vtable->is_end(start)); start->ptr_vtable->next(start))
    {
        if (*(start->ptr_vtable->element(start)) > max_ele)
        {
            result = start->ptr_vtable->element(start);
            max_ele = *(start->ptr_vtable->element(start));
        }
    }
    start->ptr_vtable->reset(start);
    return result;
}

void sort(iterator *start, iterator *end)
{
    for (; !(start->ptr_vtable->is_end(start)); start->ptr_vtable->next(start))
    {
        for (; !(start->ptr_vtable->is_end(start)); start->ptr_vtable->next(start))
        {
            if ((*(start->ptr_vtable->element(start))) < (*(start->ptr_vtable->element(start))))
            {
                int temp;
                temp = *(start->ptr_vtable->element(start));
                *(start->ptr_vtable->element(start)) = *(start->ptr_vtable->element(start));
                *(start->ptr_vtable->element(start)) = temp;
            }
        }
    }
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
        result += *(start->ptr_vtable->element(start));
    }
    start->ptr_vtable->reset(start);
    return result;
}

void replace(iterator *start, iterator *end, int old_value, int new_value)
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