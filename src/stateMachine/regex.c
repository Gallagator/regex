//
// Created by liam on 26/03/2020.
//

#include "regex.h"

bool regex(char* regexp, char* text){
    struct StateMachine* regex = build(regexp);
    bool result = naiveTraverse(regex->startState, text);
    demolish(regex);
    return result;
}

bool naiveTraverse(struct State* startNode, char* remaining){
    if(startNode == NULL){
        return false;
    }
    if(startNode->out == NULL && *remaining == '\0'){
        return true;
    }
    if(startNode->c == UNCONDITIONAL){
        return naiveTraverse(startNode->out, remaining) || naiveTraverse(startNode->out1, remaining);
    }
    if(*remaining == (char)startNode->c){
        return naiveTraverse(startNode->out, remaining + 1);
    }
    return false;
}