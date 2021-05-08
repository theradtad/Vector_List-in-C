#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "algorithms.h"

//takes in iterators pointing to start and end of container and reverses the container elements.
void reverse(iterator *start, iterator *end)
{
    int sz = 0;
    for (; !(start->ptr_vtable->is_end(start)); start->ptr_vtable->next(start))
    {
        ++sz;
    }

    start->ptr_vtable->reset(start);
    for (int i = 0; i < (sz / 2); ++i)
    {
        int temp = *(start->ptr_vtable->element(start));
        *(start->ptr_vtable->element(start)) = *(end->ptr_vtable->element(end));
        *(end->ptr_vtable->element(end)) = temp;
    }

    end->ptr_vtable->reset(end);
    start->ptr_vtable->reset(start);
}

//returns the address of the minimum element of the container
int *min_element(iterator *start, iterator *end)
{
    int maxi = INT_MAX;
    int *min = &maxi;

    for (; !(start->ptr_vtable->is_end(start)); start->ptr_vtable->next(start))
    {
        if (*(start->ptr_vtable->element(start)) < *min)
        {
            min = (start->ptr_vtable->element(start));
        }
    }
    start->ptr_vtable->reset(start);
    return min;
}

//returns the count of an element in the container
int count(iterator *start, iterator *end, int x)
{
    int cnt = 0;
    for (; !(start->ptr_vtable->is_end(start)); start->ptr_vtable->next(start))
    {
        if (*(start->ptr_vtable->element(start)) == x)
        {
            ++cnt;
        }
    }
    start->ptr_vtable->reset(start);
    return cnt;
}

//sorts the container elements in ascending order
void sort(iterator *start, iterator *end)
{
    int i = 0;
    while (!(start->ptr_vtable->is_end(start)))
    {
        int *cur = (start->ptr_vtable->element(start));
        start->ptr_vtable->next(start);

        while (!(start->ptr_vtable->is_end(start)))
        {
            if (*(start->ptr_vtable->element(start)) < *cur)
            {
                int temp = *cur;
                *cur = *(start->ptr_vtable->element(start));
                *(start->ptr_vtable->element(start)) = temp;
            }
            start->ptr_vtable->next(start);
        }
        start->ptr_vtable->reset(start);
        for (int j = 0; j <= i; ++j)
        {
            start->ptr_vtable->next(start);
        }
        ++i;
    }
    start->ptr_vtable->reset(start);
}

//retunrs the address of the max element in the container
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

//prints the container elements
void print_container(iterator *start, iterator *end)
{
    for (; !(start->ptr_vtable->is_end(start)); start->ptr_vtable->next(start))
    {
        printf("%d", *(start->ptr_vtable->element(start)));
    }
    start->ptr_vtable->reset(start);
    printf("\n");
}

//returns the sum of elements of the container added to the inital_sum passed to this function
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

//replaces every occurence of a certain element by another element
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

//to check if 2 ranges of elements are same
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