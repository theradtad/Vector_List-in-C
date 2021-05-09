#include<stdio.h>
#include <stdlib.h>
#include "list.h"
#include "list_iterator.h"
#include "algorithms.h"

// client program for list implementation, its iterators and algorithms.
void display_list(list *ptr_list)
{
    for(iterator_list *it = ptr_list->ptr_vtable->begin(ptr_list); !(it->ptr_vtable->is_end(it));it->ptr_vtable->next(it))
    {
        printf("%d ",*(it->ptr_vtable->element(it)));
    }
    printf("\n");
}

int main()
{
    list l1;
    init_list(&l1);

    if(l1.ptr_vtable->empty(&l1))
    {
        printf("The list is empty \n");
    }

    for(int i=0;i<5;++i)
    {
        l1.ptr_vtable->push_back(&l1,i);
    }

    printf("Element at the front of the list is: %d \n",l1.ptr_vtable->front(&l1));
    printf("Element at the back of the list is: %d \n",l1.ptr_vtable->back(&l1));
    printf("The size of the list is: %d\n\n",l1.ptr_vtable->size(&l1));

    l1.ptr_vtable->insert(&l1,*(l1.ptr_vtable->begin(&l1)),3,6);

    printf("The contents of the list are: ");
    display_list(&l1);

    sort((iterator *)l1.ptr_vtable->begin(&l1),(iterator *)l1.ptr_vtable->end(&l1));

    printf("The contents of the list after sorting are: ");
    display_list(&l1);

    iterator *it1 = (iterator *)l1.ptr_vtable->begin(&l1);
    iterator *it2 = (iterator *)l1.ptr_vtable->end(&l1);

    reverse(it1,it2);
    
    printf("The contents of the list after reversing are: ");
    for(; !(it1->ptr_vtable->is_end(it1));it1->ptr_vtable->next(it1))
    {
        printf("%d ",*(it1->ptr_vtable->element(it1)));
    }
    printf("\n");

    printf("Number of occurences of 6 in the list: %d \n",count((iterator *)l1.ptr_vtable->begin(&l1),(iterator *)l1.ptr_vtable->end(&l1),6));
    printf("The minimum element in the list is: %d \n",*min_element((iterator *)l1.ptr_vtable->begin(&l1),(iterator *)l1.ptr_vtable->end(&l1)));

    l1.ptr_vtable->remove(&l1,6);

    printf("The contents of the list after removing all occurences of 6 are: ");
    display_list(&l1);

    l1.ptr_vtable->clear(&l1);
    printf("The size of the list after clearing is: %d\n\n",l1.ptr_vtable->size(&l1));
}