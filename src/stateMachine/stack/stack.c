//
// Created by liam on 23/03/2020.
//

#include "stack.h"

void push(struct stackNode** head, void* data){
    struct stackNode* newHead = malloc(sizeof(struct stackNode));
    #if DEBUG
        static int numberOfNodesAllocated = 1;
        printf("stack node number %d allocated\n", numberOfNodesAllocated);
        numberOfNodesAllocated++;
    #endif
    newHead->data = data;
    newHead->next = *head;
    *head = newHead;
}

void* pop(struct stackNode** head){
    void* data = (*head)->data;
    struct stackNode* oldHead = *head;
    *head = oldHead->next;
    free(oldHead);
    #if DEBUG
        static int numberOfNodesfreed = 1;
        printf("stack node number %d freed\n", numberOfNodesfreed);
        numberOfNodesfreed++;
    #endif
    return data;
}

void delete(struct stackNode** head){
    while(!isEmpty(head)){
        pop(head);
    }
}

void* peek(struct stackNode** head){
    return (*head)->data;
}

bool isEmpty(struct stackNode** head){
    return *head == NULL;
}