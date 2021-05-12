#include "header.h"
#include "lexer.c"

Queue* readHtml(const char* filename);

void checkTag(Stack* st, int currentTag, int* tokenNum){
    // invalid => immediate error
    if (currentTag == invalid){
        printf("ERROR 2: INVALID TAG\n");
        printf("token %d\n", *tokenNum);
        exit(1);
    }
    // str, br, hr
    else if (currentTag >= 24 && currentTag <= 26){
        // do nothing
    }
    // opening tag
    else if (currentTag%2 == 0){
        // div cannot inside p
        // p cannot inside p
        if (currentTag == ddiv || currentTag == p){
            int notP = stackPop(st);
            if (notP == p){
                // div/p nested in p
                printf("ERROR 3: <div> or <p> nested within <p>\n");
                printf("token %d\n", *tokenNum);
                exit(1);
            }
            else{
                stackPush(st, notP);
            }
        }
        stackPush(st, currentTag);
    }
    // closing tag
    else if (currentTag%2 == 1){
        int openingTag = stackPop(st);
        if (currentTag != (openingTag + 1)){
            // non matching tag
            printf("ERROR 4: UNMATCHED TAG\n");
            printf("token %d\n", *tokenNum);
            exit(1);
        }
    }
}

// divide this up into functions?
int parse(const char* filename){
    Queue* tokens = readHtml(filename);
    Stack* st = createStack();
    int currentTag = dequeue(tokens);
    int tokenNum = 0;

    // check opening is html
    if(currentTag != html){
        // opening not html
        printf("ERROR 0: STARTING TAG NOT <HTML>\n");
        printf("token %d\n", tokenNum);
        exit(1);
    }
    else{
        stackPush(st, html);
    }

    // start head
    currentTag = dequeue(tokens);
    tokenNum ++;
    if (currentTag != head){
        // no head
        printf("ERROR 1: NO HEAD SECTION\n");
        printf("token %d\n", tokenNum);
        exit(1);
    }
    else{
        stackPush(st, currentTag);
    }

    // inside head
    currentTag = dequeue(tokens);
    tokenNum ++;
    while(currentTag != c_head){
        checkTag(st, currentTag, &tokenNum);
        currentTag = dequeue(tokens);
        tokenNum ++;
    }

    // close head
    int openingTag = stackPop(st);
    if (openingTag != head){
        printf("ERROR 4:UNMATCHED TAG\n");
        printf("token %d\n", tokenNum);
        exit(1);
    }

    // start body
    currentTag = dequeue(tokens);
    tokenNum ++;
    if (currentTag != body){
        printf("ERROR 5: NO BODY TAG\n");
        printf("token %d\n", tokenNum);
        exit(1);
    }
    else{
        stackPush(st, currentTag);
    }

    // inside body
    currentTag = dequeue(tokens);
    tokenNum ++;
    while(currentTag != c_body){
        if (currentTag == title){
            printf("ERROR 6: <title> TAG PRESENT IN BODY\n");
            printf("token %d\n", tokenNum);
            exit(1);
        }
        else {
            checkTag(st, currentTag, &tokenNum);
        }
        currentTag = dequeue(tokens);
        tokenNum ++;
    }

    // close body
    openingTag = stackPop(st);
    if (openingTag != body){
        printf("ERROR 4: UNMATCHED TAG\n");
        printf("token %d\n", tokenNum);
        exit(1);
    }

    // pop html off
    openingTag = stackPop(st);
    dequeue(tokens);
    tokenNum ++;
    if (openingTag != html){
        printf("ERROR 7: NO CLOSING HTML\n");
        printf("token %d\n", tokenNum);
        exit(1);
    }

    //clean up
    deleteQueue(tokens);
    deleteStack(st);
    printf("valid html file\n");
    return 0;
}

Queue* readHtml(const char* filename){
    FILE* file;
    file = fopen(filename, "r");
    char s[MAXCHAR];
    Queue* tokens = createQueue();

    if (file == NULL){
        printf("ERROR -1: %s DOES NOT EXIST\n", filename);
        exit(1);
    }

    // for every line
    while(fgets(s, MAXCHAR, file) != NULL){
        addTokens(tokens, s);
    }
    fclose(file);
    return tokens;
}

