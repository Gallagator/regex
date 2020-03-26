//
// Created by liam on 23/03/2020.
//

#ifndef REGEX_STACK_H
#define REGEX_STACK_H

#include "../../main.h"

struct stackNode{
    struct stackNode* next;
    void* data;
};

void delete(struct stackNode** head);

void push(struct stackNode** head, void* data);

void* pop(struct stackNode** head);

void* peek(struct stackNode** head);

bool isEmpty(struct stackNode** head);

#endif //REGEX_STACK_H
