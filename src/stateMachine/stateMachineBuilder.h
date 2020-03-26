//
// Created by liam on 23/03/2020.
//

#ifndef REGEX_STATEMACHINEBUILDER_H
#define REGEX_STATEMACHINEBUILDER_H

#include "state/state.h"
#include "stack/stack.h"
#include "../main.h"


//builds a finite state machine for a regex expression
struct StateMachine* build(char* regex);

//frees all memory allocated by build
void demolish(struct StateMachine* regexStateMachine);

//all nodes must be allocated this way!
struct State* createBlankNode(struct StateMachine* regexStateMachine);

struct State* createUnconditionalBlankNode(struct StateMachine* regexStateMachine);

//pushes a joining stackNode for a bracketed expression
void pushJoinNode(struct stackNode** endExpressionStack, struct StateMachine* regexStateMachine);


struct StateMachine* initStateMachine();

/************************************************************/

//each handles the case for their respective regex character
void questionMark(struct State* prev, struct State** curr, struct StateMachine* regexStateMachine);

void asterisk(struct State* prev, struct State** curr, struct StateMachine* regexStateMachine);

void plus(struct State* prev, struct State** curr, struct StateMachine* regexStateMachine);

void character(struct State** prev, struct State** curr, char c, struct StateMachine* regexStateMachine);

void openBracket(struct State** prev, struct State** curr, struct stackNode** currExpressionStack,
                 struct stackNode** endExpressionStack, struct StateMachine* regexStateMachine);

void closeBracket(struct State** prev, struct State** curr, struct stackNode** currExpressionStack,
                  struct stackNode** endExpressionStack);

void strikeDown(struct State** prev, struct State** curr, struct stackNode** currExpressionStack,
                struct stackNode** endExpressionStack, struct StateMachine* regexStateMachine);

#endif //REGEX_STATEMACHINEBUILDER_H
