#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "vector_iterator.h"
#include "algorithms.h"

void print_vector(iterator_vector *it)
{
    for (; !it->ptr_vtable->is_end(it); it->ptr_vtable->next(it))
    {
        printf("%d ", *(it->ptr_vtable->element(it)));
    }
    printf("\n");
}

int main()
{
    vector v;
    init_vector(&v);

    //assigning a vector with 5 1's
    v.ptr_vtable->assign(&v, 5, 1);
    printf("The vector after assigning it with 5 1's - ");
    print_vector(v.ptr_vtable->begin(&v));

    //pushing elements 2 and 3 to the end of the vector using push_back.
    v.ptr_vtable->push_back(&v, 2);
    v.ptr_vtable->push_back(&v, 3);
    printf("The vector after pushing 2,3 - ");
    print_vector(v.ptr_vtable->begin(&v));

    //popping the last element from the vector
    printf("The vector after popping the last element - ");
    v.ptr_vtable->pop_back(&v);
    print_vector(v.ptr_vtable->begin(&v));

    //inserting 5 to the beginning of the vector
    printf("The vector after adding 5 to the beginning of the vector - ");
    v.ptr_vtable->insert(&v, *(v.ptr_vtable->begin(&v)), 5);
    print_vector(v.ptr_vtable->begin(&v));
    printf("\n");

    //clearing the vector
    printf("Now, clearing the vector\n");
    v.ptr_vtable->clear(&v);
    printf("The vector size = %d\n", v.ptr_vtable->size(&v));
    printf("\n");

    //pushing element 1 to the vector
    printf("The vector after pushing 1 to the vector - ");
    v.ptr_vtable->push_back(&v, 1);
    print_vector(v.ptr_vtable->begin(&v));

    //adding element 3 to the vector using emplace_back
    printf("The vector after adding 3 to the vector - ");
    v.ptr_vtable->emplace_back(&v, 3);
    print_vector(v.ptr_vtable->begin(&v));

    //adding element 2 in between 1 and 3 using insert
    printf("The vector after adding 2 to the vector in between 1 and 3 - ");
    iterator_vector *it1 = v.ptr_vtable->begin(&v);
    it1->ptr_vtable->next(it1);
    v.ptr_vtable->insert(&v, *it1, 2);
    print_vector(v.ptr_vtable->begin(&v));
    printf("\n");

    //getting address of the element at index 1 and also printing the element
    printf("Getting address of element at index 1 and also printing it\n");
    iterator_vector *it2 = v.ptr_vtable->begin(&v);
    it1->ptr_vtable->next(it2);
    printf("Address of 2nd element - %p\n", it2->ptr_vtable->element(it2));
    int *a = v.ptr_vtable->at(&v, 1);
    printf("Address - %p\n", a);
    printf("The element at index 1 - %d\n", *a);
    printf("\n");

    //getting address of the element at front
    printf("Getting address of element at front and also printing it\n");
    iterator_vector *it3 = v.ptr_vtable->begin(&v);
    printf("Address of 1st element - %p\n", it3->ptr_vtable->element(it3));
    int *b = v.ptr_vtable->front(&v);
    printf("Address - %p\n", b);
    printf("The element at front - %d\n", *b);
    printf("\n");

    //getting address of the element at back
    printf("Getting address of element at back and also printing it\n");
    iterator_vector *it4 = v.ptr_vtable->end(&v);
    printf("Address of last element - %p\n", it4->ptr_vtable->element(it4));
    int *c = v.ptr_vtable->back(&v);
    printf("Address - %p\n", c);
    printf("The element at back - %d\n", *c);
    printf("\n");

    //Reversing the vector
    printf("The vector after reversing it - ");
    reverse((iterator *)v.ptr_vtable->begin(&v), (iterator *)v.ptr_vtable->end(&v));
    print_vector(v.ptr_vtable->begin(&v));

    //Finding the sum of the vector
    printf("The sum of the vector - %d\n", accumulate((iterator *)v.ptr_vtable->begin(&v), (iterator *)v.ptr_vtable->end(&v), 0));

    //Finding the count of 2
    printf("The count of element 2 - %d\n", count((iterator *)v.ptr_vtable->begin(&v), (iterator *)v.ptr_vtable->end(&v), 2));

    //Sorting the vector
    printf("The vector after sorting it - ");
    sort((iterator *)v.ptr_vtable->begin(&v), (iterator *)v.ptr_vtable->end(&v));
    print_vector(v.ptr_vtable->begin(&v));

    //Replacing the element 3 with 5
    printf("The vector after replacing all occurences of 3 with 5 - ");
    replace((iterator *)v.ptr_vtable->begin(&v), (iterator *)v.ptr_vtable->end(&v), 3, 5);
    print_vector(v.ptr_vtable->begin(&v));

    //printing max element
    printf("The max element - %d\n", *(max_element((iterator *)v.ptr_vtable->begin(&v), (iterator *)v.ptr_vtable->end(&v))));

    //printing min element
    printf("The min element - %d\n", *(min_element((iterator *)v.ptr_vtable->begin(&v), (iterator *)v.ptr_vtable->end(&v))));

    //To check if 2 ranges of elements are the same
    vector v2;
    init_vector(&v2);
    v2.ptr_vtable->push_back(&v2, 100);
    printf("Elements in v==v2 ? - %d\n", equal((iterator *)v.ptr_vtable->begin(&v), (iterator *)v.ptr_vtable->end(&v), (iterator *)v2.ptr_vtable->begin(&v2)));
    printf("Elements in v==v ? - %d\n", equal((iterator *)v.ptr_vtable->begin(&v), (iterator *)v.ptr_vtable->end(&v), (iterator *)v.ptr_vtable->begin(&v)));
}