#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

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

static bool empty(const list *ptr_list)
{
    if(ptr_list->sz == 0)
        return 1;
    else
        return 0;
}

static void assign(list *ptr_list, int count, int value)
{
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

static void remove(list *ptr_list,int value)
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

static int size(const list *ptr_list)
{
    return ptr_list->sz;
}
    
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

static void sort(list *ptr_list)
{
    return;    
}

void swap(list *ptr_list,list *ptr_list2)
{
    //check if same type
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
    }
}

void init(list *ptr_list)
{
    ptr_list->head = NULL;
    ptr_list->tail = NULL;
    ptr_list->sz = 0;
    ptr_list->front = front;
    ptr_list->back = back;
    ptr_list->push_front = push_front;
    ptr_list->push_back = push_back;
    ptr_list->pop_front = pop_front;
    ptr_list->pop_back = pop_back;
    ptr_list->empty = empty;
    ptr_list->assign = assign; 
    ptr_list->remove = remove;
    ptr_list->reverse = reverse;
    ptr_list->size = size;
    ptr_list->sort = sort;
    ptr_list->clear = clear;
    ptr_list->swap = swap;
}

// need to implement sort
// need to implement iterator related functions
// need to implement template type