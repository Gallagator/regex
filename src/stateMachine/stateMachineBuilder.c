//
// Created by liam on 23/03/2020.
//

#include "stateMachineBuilder.h"

//returns NULL on failure
struct StateMachine* build(char* regex){
    struct stackNode* currExpressionStack = NULL;
    struct stackNode* endExpressionStack = NULL;;

    struct StateMachine *regexStateMachine = initStateMachine();
    /*dummyNode needed*/
    struct State* regexHead = createUnconditionalBlankNode(regexStateMachine);
    struct State* prev = NULL;
    struct State* curr = regexHead;

    regexStateMachine->startState = regexHead;

    push(&currExpressionStack, regexHead);
    pushJoinNode(&endExpressionStack, regexStateMachine);

    char* c = regex;
    while(*c != '\0'){
        switch(*c){
            case '?':
                questionMark(prev, &curr, regexStateMachine);
                break;
            case '*':
                asterisk(prev, &curr, regexStateMachine);
                break;
            case '+':
                plus(prev, &curr, regexStateMachine);
                break;
            case '|':
                strikeDown(&prev, &curr, &currExpressionStack, &endExpressionStack, regexStateMachine);
                break;
            case '(':
                openBracket(&prev, &curr, &currExpressionStack, &endExpressionStack, regexStateMachine);
                break;
            case ')':
                closeBracket(&prev, &curr, &currExpressionStack, &endExpressionStack);
                break;
            case '\\'://note: fallthrough is intentional
                c++;
                if(*c == '\0'){
                    c--;
                    break;
                }
            default:
                character(&prev, &curr, *c, regexStateMachine);
                break;
        }
        c++;
    }
    delete(&currExpressionStack);
    delete(&endExpressionStack);

    return regexStateMachine;
}

void demolish(struct StateMachine* regexStateMachine){
    struct stackNode* allNodes = regexStateMachine->allNodes;
    while (!isEmpty(&allNodes)){
        #if DEBUG
            int id = ((struct State*)allNodes->data)->id;
            printf("node with id: %d freed\n", id);
        #endif
        free(pop(&allNodes));
    }
    free(regexStateMachine);
    #if DEBUG
        puts("regexStateMachine freed");
    #endif
}

struct StateMachine* initStateMachine() {
    struct StateMachine *regexStateMachine = malloc(sizeof(struct StateMachine));
    #if DEBUG
        puts("regexStateMachine allocated");
    #endif
    regexStateMachine->allNodes = NULL;
    return regexStateMachine;
}

void questionMark(struct State* prev, struct State** curr, struct StateMachine* regexStateMachine) {
    struct State* joinNode = createUnconditionalBlankNode(regexStateMachine);
    struct State* splitNode = createUnconditionalBlankNode(regexStateMachine);
    splitNode->out = prev->out;
    splitNode->out1 = joinNode;
    prev->out = splitNode;
    (*curr)->out = joinNode;
    *curr = joinNode;
    //TODO error if curr is UNCONDITIONAL
}


void asterisk(struct State* prev, struct State** curr, struct StateMachine* regexStateMachine){
    struct State* splitNode = createUnconditionalBlankNode(regexStateMachine);
    splitNode->out1 = prev->out;
    prev->out = splitNode;
    (*curr)->out = splitNode;
    *curr = splitNode;
    //TODO error if curr is UNCONDITIONAL
}

void plus(struct State* prev, struct State** curr, struct StateMachine* regexStateMachine){
    struct State* splitNode = createUnconditionalBlankNode(regexStateMachine);
    (*curr)->out = splitNode;
    splitNode->out1 = prev->out;
    *curr = splitNode;
    //TODO error if curr is UNCONDITIONAL
}

void character(struct State** prev, struct State** curr, char c, struct StateMachine* regexStateMachine){
    struct State* characterNode = createBlankNode(regexStateMachine);
    characterNode->c = (unsigned int) c;
    (*curr)->out = characterNode;
    *prev = *curr;
    *curr = characterNode;
}

void openBracket(struct State** prev, struct State** curr, struct stackNode** currExpressionStack,
                 struct stackNode** endExpressionStack, struct StateMachine* regexStateMachine){
    //push(prevExpressionStack, *curr);
    struct State* bracketNode = createUnconditionalBlankNode(regexStateMachine);
    (*curr)->out = bracketNode;
    *curr = bracketNode;
    push(currExpressionStack, bracketNode);
    pushJoinNode(endExpressionStack, regexStateMachine);
}

void closeBracket(struct State** prev, struct State** curr, struct stackNode** currExpressionStack,
        struct stackNode** endExpressionStack){
    struct State* bracketNode = pop(endExpressionStack);
    (*curr)->out = bracketNode;
    *curr = bracketNode;
    *prev = pop(currExpressionStack);
}

void strikeDown(struct State** prev, struct State** curr, struct stackNode** currExpressionStack,
                struct stackNode** endExpressionStack, struct StateMachine* regexStateMachine){
    struct State* bracketNode = peek(currExpressionStack);
    struct State* joinNode = peek(endExpressionStack);
    (*curr)->out = joinNode;
    struct State* splitNode = createUnconditionalBlankNode(regexStateMachine);
    splitNode->out1 = bracketNode->out;
    bracketNode->out = splitNode;
    *curr = splitNode;
    *prev = bracketNode;
}

void pushJoinNode(struct stackNode** endExpressionStack, struct StateMachine* regexStateMachine) {
    struct State* joinNode = createUnconditionalBlankNode(regexStateMachine);
    push(endExpressionStack, joinNode);
}



struct State* createBlankNode(struct StateMachine* regexStateMachine){
    struct State* blanknode = malloc(sizeof(struct State));
    blanknode->out = NULL;
    blanknode->out1 = NULL;
    push(&(regexStateMachine->allNodes), blanknode);
    #if DEBUG
        static int id = 0;
        blanknode->id = id;
        printf("node with id: %d allocated\n", id);
        id++;
    #endif
    return blanknode;
}

struct State* createUnconditionalBlankNode(struct StateMachine* regexStateMachine){
    struct State* blankNode = createBlankNode(regexStateMachine);
    blankNode->c = UNCONDITIONAL;
    return blankNode;
}
