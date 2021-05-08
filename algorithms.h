#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "iterator.h"

void reverse(iterator *start, iterator *end);

int *min_element(iterator *start, iterator *end);

int *max_element(iterator *start, iterator *end);

int count(iterator *start, iterator *end, int x);

void sort(iterator *start, iterator *end);

void print_container(iterator *start, iterator *end);

int accumulate(iterator *start, iterator *end, int initial_sum);

void replace(iterator *start, iterator *end, int old_value, int new_value);

bool equal(iterator *start1, iterator *end1, iterator *start2);

#endif