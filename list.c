#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// Returns the element stored at the head - the first element in the list.
static int front(const list *ptr_list)
{
    if(ptr_list->head != NULL)
    {
        return ptr_list->head->val;
    }
    else
    {
        fprintf(stderr, "Error: Access to Empty list \n");
        exit(-1);
    }
}

// Returns the element stored at the tail - the last element in the list.
static int back(const list *ptr_list)
{
    if(ptr_list->tail != NULL)
    {
        return ptr_list->tail->val;
    }
    else
    {
        fprintf(stderr, "Error: Access to Empty list \n");
        exit(-1);
    }
}

// Adds an element to the front of the list.
static void push_front(list *ptr_list,int g)
{
    node *temp = (node*)malloc(sizeof(struct node));
    
    temp->val = g;
    temp->prev = NULL;
    temp->next = NULL;

    ++ptr_list->sz;

    if(ptr_list->head == NULL)
    {
        ptr_list->head = temp;
        ptr_list->tail = temp;
    }
    else
    {
        temp->next = ptr_list->head;
        ptr_list->head->prev = temp;
        ptr_list->head = temp;
    }
}

// Adds an element to the end of the list.
static void push_back(list *ptr_list,int g)
{
    node *temp = (node*)malloc(sizeof(struct node));

    temp->val = g;
    temp->prev = NULL;
    temp->next = NULL;

    ++ptr_list->sz;

    if(ptr_list->head == NULL)
    {
        ptr_list->head = temp;
        ptr_list->tail = temp;
    }
    else
    {
        temp->prev = ptr_list->tail;
        ptr_list->tail->next = temp;
        ptr_list->tail = temp;
    }
}

// Deletes the first element of the list.
static void pop_front(list *ptr_list)
{
    if(ptr_list->head == NULL)
    {
        return;
    }
    else if(ptr_list->head == ptr_list->tail)
    {
        node* temp = ptr_list->head;
        ptr_list->head = NULL;
        ptr_list->tail = NULL;
        free(temp);
    }
    else
    {
        node *temp=ptr_list->head;
        ptr_list->head = ptr_list->head->next;
        ptr_list->head->prev=NULL;
        temp->next = NULL;
        free(temp);
    }

    --ptr_list->sz;

}

// Deletes the last element of the list.
static void pop_back(list *ptr_list)
{
    if(ptr_list->tail == NULL)
    {
        return;
    }
    else if(ptr_list->head == ptr_list->tail)
    {
        node* temp = ptr_list->head;
        ptr_list->head = NULL;
        ptr_list->tail = NULL;
        free(temp);
    }
    else
    {
        node *temp=ptr_list->tail;
        ptr_list->tail = ptr_list->tail->prev;
        ptr_list->tail->next = NULL;
        temp->prev = NULL;
        free(temp);
    }

    --ptr_list->sz;

}

// Returns True if the list is empty, False if the list contains elements.
static bool empty(const list *ptr_list)
{
    if(ptr_list->sz == 0)
        return 1;
    else
        return 0;
}

// Called on an iterator, if it's called on begin() add before element, if called on end() add after element.
void insert(list *ptr_list, iterator_list iter_ptr,int num_ele, int ele)
{
    if(iter_ptr.base_iterator.type != 'F')
    {
        fprintf(stderr,"Error: Incompatible Iterator for Insert\n");
        exit(-1);
    }
    int i=0;
    node* prev = iter_ptr.index;
    if(prev == NULL)
    {
        node *temp = (node*)malloc(sizeof(struct node));
        temp->val = ele;
        temp->prev = NULL;
        temp->next = NULL;
        ptr_list->head = temp;
        ptr_list->tail = temp;
        prev = temp;
        ++i;
        ++ptr_list->sz;
    }

    if(iter_ptr.base_iterator.type_of_movement == 'H')
    {
        node* prev_ele = prev->prev;
        while(i < num_ele)
        {
            node* temp = (node*)malloc(sizeof(struct node));
            temp->val = ele;
            temp->prev = NULL;
            temp->next = prev;
            prev->prev = temp;
            prev = temp;
            ++i;
            ++ptr_list->sz;
        }
        if(prev_ele != NULL)
        {
            prev_ele->next = prev;
            prev->prev = prev_ele;
        }
        else
        {
            ptr_list->head = prev;
        }
    }
    else
    {
        node* next_ele = prev->next;
        while(i < num_ele)
        {
            node* temp = (node*)malloc(sizeof(struct node));
            temp->val = ele;
            temp->prev = prev;
            temp->next = NULL;
            prev->next = temp;
            prev = temp;
            ++i;
            ++ptr_list->sz;
        }
        if(next_ele != NULL)
        {
            next_ele->prev = prev;
            prev->next = next_ele;
        }
        else
        {
            ptr_list->tail = prev;
        }
    }
}

// Erases all the elements that occur after the current position of the iterator, 
// including the element to which the iterator points to.
void erase(list *ptr_list, iterator_list iter_ptr)
{
    node *cur = iter_ptr.index;
    if(cur == NULL)
        return ;
    
    if(iter_ptr.base_iterator.type == 'F')
    {
        if(iter_ptr.base_iterator.type_of_movement == 'T')
        {
            fprintf(stderr, "Error: End Iterator passed to erase\n");
            exit(-1);
        }
        if(cur->prev == NULL)
        {
            ptr_list->head = NULL;
            ptr_list->tail = NULL;
        }
        else
        {
            ptr_list->tail = cur->prev;
            cur->prev->next = NULL;
        }
        
        while(cur != NULL)
        {
            node *temp = cur;
            cur = cur->next;
            temp->next = NULL;
            temp->prev = NULL;
            free(temp);
            --ptr_list->sz;
        }
    }

    else
    {
        fprintf(stderr, "Error: Reverse Iterator passed to erase\n");
        exit(-1);
    }
}

// On calling this function, this list would contain count number of elements,
// with the value that is passed as argument to the function.
static void assign(list *ptr_list, int count, int value)
{
    if(count == 0)
    {
        ptr_list->ptr_vtable->clear(ptr_list);
        return;
    }
    node* cur = ptr_list->head;
    node* prev = NULL;
    int i=0;

    while(cur != NULL && i<count)
    {
        cur->val = value;
        prev = cur;
        cur = cur->next;
        ++i;
    }

    if(cur == NULL && i<count)
    {
        if(prev == NULL)
        {
            node* temp = (node*)malloc(sizeof(struct node));
            temp->val = value;
            temp->prev = NULL;
            temp->next = NULL;
            ++i;
            prev = temp;
            ptr_list->head = temp;
        }
        while(i<count)
        {
            node* temp = (node*)malloc(sizeof(struct node));
            temp->val = value;
            temp->prev = prev;
            temp->next=NULL;
            prev->next=temp;
            prev=temp;
            ++i;
        }

        ptr_list->tail = prev;
    }

    else if(cur != NULL && i == count)
    {
        prev->next = NULL;
        ptr_list->tail = prev;

        while(cur != NULL)
        {
            node* temp = cur;
            cur = cur->next;
            temp->prev = NULL;
            temp->next = NULL;
            free(temp);    
        }
    }

    ptr_list->sz = count;
}

// Deletes all the elements in the list that have value equal to the argument passed.
static void remove_lst(list *ptr_list,int value)
{
    node* cur = ptr_list->head;
    node* prev = NULL;

    while(cur != NULL)
    {
        if(cur->val == value)
        {
            if(prev == NULL)
            {
                node* temp = cur;
                cur = cur->next;
                temp->next = NULL;

                if(cur != NULL)
                    cur->prev = prev;
                else
                    ptr_list->tail = prev;
                
                ptr_list->head = cur;
                free(temp);
            }
            else
            {
                node *temp = cur;
                cur = cur->next;
                prev->next = cur;

                if(cur != NULL)
                    cur->prev = prev;
                else
                    ptr_list->tail = prev;
                
                temp->prev = NULL;
                temp->next = NULL;
                free(temp);
            }
            --ptr_list->sz;
        }
        else
        {
            prev=cur;
            cur=cur->next;
        }
    }
}

// Deletes all elements in the list, which, when passed to the function specified in the argument returns true.
static void remove_if(list *ptr_list, bool (*fn)(int value))
{
    node* cur = ptr_list->head;
    node* prev = NULL;

    while(cur != NULL)
    {
        if(fn(cur->val))
        {
            if(prev == NULL)
            {
                node* temp = cur;
                cur = cur->next;
                temp->next = NULL;

                if(cur != NULL)
                    cur->prev = prev;
                else
                    ptr_list->tail = prev;
                
                ptr_list->head = cur;
                free(temp);
            }
            else
            {
                node *temp = cur;
                cur = cur->next;
                prev->next = cur;

                if(cur != NULL)
                    cur->prev = prev;
                else
                    ptr_list->tail = prev;
                
                temp->prev = NULL;
                temp->next = NULL;
                free(temp);
            }
            --ptr_list->sz;
        }
        else
        {
            prev=cur;
            cur=cur->next;
        }
    }
}

// Reverse the linked list and hence reverses the elements present in the linked list.
static void reverse(list *ptr_list)
{
    node* cur = ptr_list->head;
    node* prev = NULL;
    node* temp = NULL;
    
    ptr_list->tail = cur;

    while(cur != NULL)
    {
        temp = cur;
        cur = cur->next;
        
        temp->next = prev;
        temp->prev = cur;
        prev = temp;
    }

    ptr_list->head = prev;
}

// Returns the size of the linked list, which represents the number of elements present in the list.
static int size(const list *ptr_list)
{
    return ptr_list->sz;
}

// Resizes the list to contain exactly count number of elements with all of them having the value passed the argument.
static void resize(list *ptr_list, int count, int value)
{
    if(count == 0)
    {
        ptr_list->ptr_vtable->clear(ptr_list);
        return;
    }

    node* cur = ptr_list->head;
    node* prev = NULL;
    int i=0;

    while(cur != NULL && i<count)
    {
        cur->val = value;
        prev = cur;
        cur = cur->next;
        ++i;
    }

    if(cur == NULL && i<count)
    {
        if(prev == NULL)
        {
            node* temp = (node*)malloc(sizeof(struct node));
            temp->val = value;
            temp->prev = NULL;
            temp->next = NULL;
            ++i;
            prev = temp;
            ptr_list->head = temp;
        }
        while(i<count)
        {
            node* temp = (node*)malloc(sizeof(struct node));
            temp->val = value;
            temp->prev = prev;
            temp->next=NULL;
            prev->next=temp;
            prev=temp;
            ++i;
        }

        ptr_list->tail = prev;
    }

    else if(cur != NULL && i == count)
    {
        prev->next = NULL;
        ptr_list->tail = prev;

        while(cur != NULL)
        {
            node* temp = cur;
            cur = cur->next;
            temp->prev = NULL;
            temp->next = NULL;
            free(temp);    
        }
    }

    ptr_list->sz = count;
}

// Clears the list so that it contains no elements.
static void clear(list *ptr_list)
{
    node* cur = ptr_list->head;
    
    while(cur != NULL)
    {
        node* temp = cur;
        cur = cur->next;
        temp->prev = NULL;
        temp->next = NULL;
        free(temp);
    }

    ptr_list->head = NULL;
    ptr_list->tail = NULL;
    ptr_list->sz = 0;
}

// Sorts the list with the time complexity O(n*n).
static void sort(list *ptr_list)
{
    if(ptr_list->head == NULL)
        return;

    node* i = ptr_list->head;
    node *j = NULL;
    node *min = NULL;

    while (i->next != NULL)
    {
        j = i->next;
        min = i;
        while (j != NULL)
        {
            if(j->val < min->val)
                min = j;
            j=j->next;
        }
        int temp = i->val;
        i->val = min->val;
        min->val = temp;
        i=i->next;
    }
    
}

// Swaps the content of two lists of the same size.
static void swap(list *ptr_list,list *ptr_list2)
{
    //check if same base_iterator.type
    if(ptr_list->sz != ptr_list2->sz)
    {
        fprintf(stderr, "Error: List of different sizes \n");
        exit(-1);
    }
    else
    {
        node* temp;
        temp = ptr_list->head;
        ptr_list->head = ptr_list2->head;
        ptr_list2->head = temp;

        temp = ptr_list->tail;
        ptr_list->tail = ptr_list2->tail;
        ptr_list2->tail = temp;
    }
}

// Deletes all duplicate elements in a sorted list.
static void unique(list *ptr_list)
{
    if(ptr_list->head == NULL)
    {
        return;
    }

    node* prev = ptr_list->head;
    node* cur = prev->next;
    
    while(cur != NULL)
    {
        if(prev->val == cur->val)
        {
            node *temp = cur;
            cur=cur->next;
            prev->next = cur;
            if(cur != NULL)
            {
                cur->prev = prev;
            }
            else
            {
                ptr_list->tail = temp;
            }
            temp->prev = NULL;
            temp->next = NULL;
            free(temp);
            --ptr_list->sz;
        }
        else
        {
            prev=cur;
            cur=cur->next;
        }
    }
}

// Adds an element to the front of the list.
static void emplace_front(list *ptr_list,int g)
{
    node *temp = (node*)malloc(sizeof(struct node));
    
    temp->val = g;
    temp->prev = NULL;
    temp->next = NULL;

    ++ptr_list->sz;

    if(ptr_list->head == NULL)
    {
        ptr_list->head = temp;
        ptr_list->tail = temp;
    }
    else
    {
        temp->next = ptr_list->head;
        ptr_list->head->prev = temp;
        ptr_list->head = temp;
    }
}

// Adds an element to the end of the list.
static void emplace_back(list *ptr_list,int g)
{
    node *temp = (node*)malloc(sizeof(struct node));

    temp->val = g;
    temp->prev = NULL;
    temp->next = NULL;

    ++ptr_list->sz;

    if(ptr_list->head == NULL)
    {
        ptr_list->head = temp;
        ptr_list->tail = temp;
    }
    else
    {
        temp->prev = ptr_list->tail;
        ptr_list->tail->next = temp;
        ptr_list->tail = temp;
    }
}

// Merges contents of two sorted lists into the list calling the function and the other list is empty.
static void merge(list *ptr_list,list *ptr_list2)
{
    list l3;
    init_list(&l3);
    node* cur1 = ptr_list->head;
    node* cur2 = ptr_list2->head;

    while(cur1 != NULL && cur2 != NULL)
    {
        if(cur1->val < cur2->val)
        {
            l3.ptr_vtable->push_back(&l3,cur1->val);
            cur1 = cur1->next;  
        }
        else
        {
            l3.ptr_vtable->push_back(&l3,cur2->val);
            cur2 = cur2->next; 
        }
    }
    while(cur1 != NULL)
    {
        l3.ptr_vtable->push_back(&l3,cur1->val);
        cur1 = cur1->next;   
    }
    while (cur2 != NULL)
    {
        l3.ptr_vtable->push_back(&l3,cur2->val);
        cur2 = cur2->next;
    }
    ptr_list2->ptr_vtable->clear(ptr_list2);

    node* temp;
    temp = ptr_list->head;
    ptr_list->head = l3.head;
    l3.head = temp;
    temp = ptr_list->tail;
    ptr_list->tail = l3.tail;
    l3.tail = temp;

    l3.ptr_vtable->clear(&l3);
}

// Transfers all elements of the second list to the first after the position pointed to by the iterator_list object.
static void splice(list *ptr_list, iterator_list iter_ptr, list *ptr_list2)
{
    if(iter_ptr.base_iterator.type != 'F')
    {
        fprintf(stderr,"Error: Incompatible Iterator for Splice\n");
        exit(-1);
    }
    if(ptr_list2->head == NULL)
    {
        return;
    }

    if(iter_ptr.base_iterator.type_of_movement == 'H')
    {
        if(ptr_list->head != NULL)
        {
            ptr_list->head->prev = ptr_list2->tail;
        }
        else
        {
            ptr_list->tail = ptr_list2->tail;
        }
        ptr_list2->tail->next = ptr_list->head;
        ptr_list->head = ptr_list2->head;
        ptr_list->sz += ptr_list2->sz;
        ptr_list2->head = NULL;
        ptr_list2->tail = NULL;
        ptr_list2->sz = 0;
    }
    else
    {
        if(ptr_list->tail != NULL)
        {
            ptr_list->tail->next = ptr_list2->head;
        }
        else
        {
            ptr_list->head = ptr_list2->head;
        }

        ptr_list2->head->prev = ptr_list->tail;
        ptr_list->tail = ptr_list2->tail;
        ptr_list->sz += ptr_list2->sz;
        ptr_list2->head = NULL;
        ptr_list2->tail = NULL;
        ptr_list2->sz = 0;
    }
}

// Inserts a new element at the position pointed to by the iterator_list object.
static iterator_list* emplace(list *ptr_list, iterator_list iter_ptr, int ele)
{
    if(iter_ptr.base_iterator.type != 'F')
    {
        fprintf(stderr,"Error: Incompatible Iterator for Emplace\n");
        exit(-1);
    }
    node* prev = iter_ptr.index;
    if(prev == NULL)
    {
        node *temp = (node*)malloc(sizeof(struct node));
        temp->val = ele;
        temp->prev = NULL;
        temp->next = NULL;
        ptr_list->head = temp;
        ptr_list->tail = temp;
        ++ptr_list->sz;

        iterator_list *it = (iterator_list*)malloc(sizeof(iterator_list));
        init_iterator_list_fwd(it, ptr_list, 'H');
        return it;
    }

    if(iter_ptr.base_iterator.type_of_movement == 'H')
    {
        node *temp = (node*)malloc(sizeof(struct node));
        temp->val = ele;
        temp->prev = prev->prev;
        if(temp->prev != NULL)
            temp->prev->next = temp;
        else
            ptr_list->head = temp;
        temp->next = prev;
        prev->prev = temp;
        ++ptr_list->sz;

        iterator_list *it = (iterator_list*)malloc(sizeof(iterator_list));
        init_iterator_list_fwd(it, ptr_list, 'H');
        it->index = temp;
        return it;
    }
    else
    {
        node *temp = (node*)malloc(sizeof(struct node));
        temp->val = ele;
        temp->next = prev->next;
        if(temp->next != NULL)
            temp->next->prev = temp;
        else
            ptr_list->tail = temp;
        temp->prev = prev;
        prev->next = temp;
        ++ptr_list->sz;

        iterator_list *it = (iterator_list*)malloc(sizeof(iterator_list));
        init_iterator_list_fwd(it, ptr_list, 'H');
        it->index = temp;
        return it;
    }
}

// Returns a forward pointer, pointing to the first element of the list.
static iterator_list* begin(list *ptr_list)
{
    iterator_list *temp = (iterator_list*)malloc(sizeof(iterator_list));
    init_iterator_list_fwd(temp, ptr_list, 'H');
    return temp;
}

// Returns a forward pointer, pointing to the last element of the list.
static iterator_list* end(list *ptr_list)
{
    iterator_list *temp = (iterator_list*)malloc(sizeof(iterator_list));
    init_iterator_list_fwd(temp, ptr_list, 'T');
    return temp;
}

// Returns a reverse pointer, pointing to the first element of the list.
static iterator_list* rbegin(list *ptr_list)
{
    iterator_list *temp = (iterator_list*)malloc(sizeof(iterator_list));
    init_iterator_list_rev(temp, ptr_list, 'T');
    return temp;
}

// Returns a reverse pointer, pointing to the last element of the list.
static iterator_list* rend(list *ptr_list)
{
    iterator_list *temp = (iterator_list*)malloc(sizeof(iterator_list));
    init_iterator_list_rev(temp, ptr_list, 'H');
    return temp;
}

// static object to initialize the vtable pointer.
static list_vtable ptr_vtbl_list =
{
    front,
    back,
    push_front,
    push_back,
    pop_front,
    pop_back,
    empty,
    insert,
    erase,
    assign, 
    remove_lst,
    remove_if,
    reverse,
    size,
    resize,
    sort,
    clear,
    unique,
    swap,
    emplace_front,
    emplace_back,
    merge,
    splice,
    emplace,
    begin,
    end,
    rbegin,
    rend
};

// Function to initialize the list.
void init_list(list *ptr_list)
{
    ptr_list->head = NULL;
    ptr_list->tail = NULL;
    ptr_list->sz = 0;
    ptr_list->ptr_vtable = &ptr_vtbl_list;
}