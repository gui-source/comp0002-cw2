#include "header.h"
#include "node.c"

//size is an integer, head is a pointer to a Node
typedef struct Stack{
    int size;
    Node* head;
} Stack;

//size is an integer, head and tail pointers to Node
//push to tail, pop from head
typedef struct Queue{
    int size;
    Node* head;
    Node* tail;
}Queue;

void showQueue(Queue* q);

Stack* createStack(){
    Stack* st = (Stack*)malloc(sizeof(Stack));
    st->size = 0;
    st->head = NULL;
    return st;
}

Node* createNode(int n){
    Node* node = (Node*)malloc(sizeof(Node));
    node->next = NULL;
    node->prev = NULL;
    node->value = n;
    return node;
}

// 1 true, 0 false
int stackIsEmpty(Stack* st){
    if (st->size == 0){
        return 1;
    }
    else{
        return 0;
    }
}

void stackPush(Stack* st, int n){
    Node* node = createNode(n);
    st->size ++;
    node->next = st->head;
    st->head = node;
}

int stackPop(Stack* st){
    int toReturn;
    if (stackIsEmpty(st)){
        // may need to do something other than return -1 - this is popping emtpy stack
        return -1;
    }
    else{
        st->size --;
        Node* toFree = st->head;
        toReturn = toFree->value;
        st->head = toFree->next;
        free(toFree);
    }
    return toReturn;
}

void showStack(Stack* st){
    printf("Stack start:[");
    Node* current;
    current = st->head;
    while(current != NULL){
        printf("%i, ", current->value);
        current = current->next;
    }
    printf("]\n");
}

void deleteStack(Stack* st){
    while(stackIsEmpty(st) == 0){
        stackPop(st);
    }
    free(st);
}

Queue* createQueue(){
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->size = 0;
    q->head = NULL;
    q->tail = NULL;
    return q;
}

// 1 true, 0 false
int queueIsEmpty(Queue* q){
    if (q->size == 0){
        return 1;
    }
    else{
        return 0;
    }
}

void enqueue(Queue* q, int n){
    Node* node = createNode(n);
    if (queueIsEmpty(q)){
        q->size = 1;
        q->head = node;
        q->tail = node;
    }
    else{
        q->size ++;
        node->next = q->tail;
        q->tail->prev = node;
        q->tail = node;
    }
}

int dequeue(Queue* q){
    int toReturn;
    if (queueIsEmpty(q)){
        // may need to do something other than return -1 - this is popping emtpy stack
        return -1;
    }
    else{
        q->size --;
        Node* toFree = q->head;
        toReturn = toFree->value;
        q->head = toFree->prev;
        if (q->size == 0){
            q->tail = NULL;
        }
        else {
            q->head->next = NULL;
        }
        free(toFree);
    }
    return toReturn;
}

void showQueue(Queue* q){
    printf("Queue start: tail[");
    Node* current;
    current = q->tail;
    while(current != NULL){
        printf("%i, ", current->value);
        current = current->next;
    }
    printf("]head \n");
}

void deleteQueue(Queue* q){
    while(queueIsEmpty(q) == 0){
        dequeue(q);
    }
    free(q);
}
