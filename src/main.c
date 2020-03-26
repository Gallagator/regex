#include "stateMachine/regex.h"

int main() {
    //regex to check if it is a number
    if(regex("(\\+|-)?(0|(1|2|3|4|5|6|7|8|9)(0|1|2|3|4|5|6|7|8|9)*)", "-56873468756438324654")){
        puts("success\n");
    }else{
        puts("failure\n");
    }
    return 0;
}
