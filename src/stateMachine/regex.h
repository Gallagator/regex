//
// Created by liam on 26/03/2020.
//

#ifndef REGEX_REGEX_H
#define REGEX_REGEX_H

#include "../main.h"
#include "stateMachineBuilder.h"

bool regex(char* regexp, char* text);

bool naiveTraverse(struct State* startNode, char* remaining);
#endif //REGEX_REGEX_H
