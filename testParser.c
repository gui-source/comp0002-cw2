#include "header.h"
#include "parser.c"

void testReadHtml();

int main (){
//    testReadHtml();
    parse();
}

void testReadHtml(){
    readHtml("html.txt");
    Queue* test = createQueue();
    enqueue(test, html);
    enqueue(test, head);
    enqueue(test, title);
    enqueue(test, str);
    enqueue(test, c_title);
    enqueue(test, c_head);
    enqueue(test, body);
    enqueue(test,h1);
    enqueue(test,str);
    enqueue(test,c_h1);
    enqueue(test,ddiv);
    enqueue(test, p);
    enqueue(test,str);
    enqueue(test,c_p);
    enqueue(test,br);
    enqueue(test,h2);
    enqueue(test,str);
    enqueue(test,c_h2);
    enqueue(test,p);
    enqueue(test,str);
    enqueue(test,a);
    enqueue(test,str);
    enqueue(test,c_a);
    enqueue(test,c_p);
    enqueue(test,hr);
    enqueue(test,ul);
    enqueue(test,li);
    enqueue(test,p);
    enqueue(test,str);
    enqueue(test,c_p);
    enqueue(test,c_li);
    enqueue(test,li);
    enqueue(test,p);
    enqueue(test,str);
    enqueue(test,c_p);
    enqueue(test,c_li);
    enqueue(test,c_ul);
    enqueue(test,ddiv);
    enqueue(test,p);
    enqueue(test,str);
    enqueue(test,c_p);
    enqueue(test,c_div);
    enqueue(test,c_div);
    enqueue(test,c_body);
    enqueue(test,c_html);
    showQueue(test);



}