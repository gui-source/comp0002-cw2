#include "header.h"
#include "qstack.c"

int identifyTag(char* tag);

//note div as ddiv here
enum tokens{html, c_html, body, c_body, head,
        c_head, title, c_title, h1, c_h1,
        h2, c_h2, h3, c_h3, p,
        c_p, ul, c_ul, li, c_li,
        a, c_a, ddiv, c_div, br,
        hr, str,invalid};

// adds all tokens in chars to toks
void addTokens(Queue * toks, char* chars){
    int tokenSize;
    char* current = chars;
    char* terminationChar = strchr(chars, '\0');
    int totalSize = terminationChar - current;

    // check first character
    while(*current != '\0') {
        // if <
        if (*current == '<'){
            // use strchrr look for >
            // start from current + 1
            char* stop = strchr(current + 1, '>');
            if (stop == NULL){
                enqueue(toks, invalid);
                break;
            }
            // size includes \0
            int size = stop - current;
            char* fullTag = (char*) malloc(size * sizeof(char));
            strncpy(fullTag, current + 1, size - 1);
            fullTag[size - 1] = '\0';
            // <...> split by space using strtok
            char* tag = strtok(fullTag, " ");
            // if need to verify attribute, can use strtok to get second part and verify
            // identifyToken
            // add to Tokens
            int token = identifyTag(tag);
            enqueue(toks, token);
            // update token size
            tokenSize = size + 1;
        }
        //if whitespace (\s\t\n)
        else if (isspace(*current)){
            // skip over
            tokenSize = 1;
        }
        // if anything else
        else{
            // look for <
            char* stop = strchr(current, '<');
            if (stop == NULL){
                stop = strchr(current, '\0');
            }
            tokenSize = stop - current;
            // add to Tokens as str
            enqueue(toks, str);
        }
        // move on to next one
        totalSize -= tokenSize;
        if (totalSize<0){
            enqueue(toks,invalid);
            break;
        }
        current += tokenSize;
    }
}

// tag is pointer to first char in "html\0" string type
int identifyTag(char* tag){
    int toReturn;
    int closing = 0;

    if (tag[0] == '/'){
        tag ++;
        closing = 1;
    }


    if (strcmp(tag, "html") == 0){
        toReturn = html;
    }
    else if (strcmp(tag, "head") == 0){
        toReturn = head;
    }
    else if (strcmp(tag, "body") == 0){
        toReturn = body;
    }
    else if (strcmp(tag, "title") == 0){
        toReturn = title;
    }
    else if (strcmp(tag, "h1") == 0){
        toReturn = h1;
    }
    else if (strcmp(tag, "h2") == 0){
        toReturn = h2;
    }
    else if (strcmp(tag, "h3") == 0){
        toReturn = h3;
    }
    else if (strcmp(tag, "p") == 0){
        toReturn = p;
    }
    else if (strcmp(tag, "ul") == 0){
        toReturn = ul;
    }
    else if (strcmp(tag, "li") == 0){
        toReturn = li;
    }
    else if (strcmp(tag, "a") == 0){
        toReturn = a;
    }
    else if (strcmp(tag, "div") == 0){
        toReturn = ddiv;
    }
    else if (strcmp(tag, "br") == 0){
        toReturn = br;
    }
    else if (strcmp(tag, "hr") == 0){
        toReturn = hr;
    }
    else{
        toReturn = invalid;
    }

    if (closing){
        if (toReturn < br){
            toReturn ++;
        }
        else{
            // change if /br, /hr allowed
            toReturn = invalid;
        }
    }

    return toReturn;
}