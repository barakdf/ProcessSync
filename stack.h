//
// Created by 97252 on 4/19/2022.
//

#ifndef THREADS_STACK_H
#define THREADS_STACK_H

#define text_length 1024


    typedef struct node {
        char data[text_length];
        struct node *next;
    } node;


    typedef struct stack{
        node* head;
        int size;
    } Stack;

    void printStack(Stack** stack);

    char*top(Stack** stack);

    void push(Stack** top ,char* text);

    void pop(Stack** stack);

    void free_stack(Stack** stack);
#endif //THREADS_STACK_H
