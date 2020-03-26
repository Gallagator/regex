//
// Created by liam on 19/03/2020.
//

#ifndef REGEX_STATE_H
#define REGEX_STATE_H

#include "../../main.h"
#include "../stack/stack.h"

//constant to signify if out is an unconditional moves
#define UNCONDITIONAL 256

struct State{
    struct State* out;
    struct State* out1;
    unsigned int c;
    #if DEBUG
        int id;
    #endif
};

struct StateMachine{
    struct State* startState;
    struct stackNode* allNodes;
};

#endif //REGEX_STATE_H
