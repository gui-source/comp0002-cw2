

//value is an integer, next is a pointer to a Node
typedef struct Node{
    int value;
    struct Node* next;
    struct Node* prev;
}Node;