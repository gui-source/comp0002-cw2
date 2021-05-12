#include "header.h"
#include "lexer.c"
int main (){
    Queue* q = getTokens("<html> </html>");
    showQueue(q);
}
