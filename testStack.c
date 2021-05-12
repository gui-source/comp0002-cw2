//
// Created by guich on 5/10/2021.
//
#include "header.h"
#include "qstack.c"

int main(){
//    Stack* st = createStack();
//    stackPush(st,3);
//    showStack(st);
//    printf("popped %d\n", stackPop(st));
//    showStack(st);

    Queue* q = createQueue();
    enqueue(q, 14);
    printf("pushed %d\n", 14);
    showQueue(q);
    printf("pushed %d\n", 18);
    enqueue(q, 18);
    showQueue(q);
    printf("pushed %d\n", 0);
    enqueue(q, 0);
    showQueue(q);
    printf("popped %d\n", dequeue(q));
    showQueue(q);
    printf("popped %d\n", dequeue(q));
    showQueue(q);
    printf("popped %d\n", dequeue(q));
    showQueue(q);

}