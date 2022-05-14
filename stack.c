//
// Created by 97252 on 4/19/2022.
//

#include "stack.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <unistd.h>
#include <sys/types.h>
#include <assert.h>
#include <sys/mman.h>


void stack_Init(Stack **pStack) {
    char *memory_ptr = (char *) mmap(NULL, sizeof(node) * 10, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1,
                                     0);
    if (MAP_FAILED == memory_ptr) {
        perror("Error On MAP\n");
        exit(0);
    }
    (*pStack)->st_addr = memory_ptr;
    (*pStack)->init_addr = memory_ptr;
}

void *stack_malloc(Stack **pStack) {
    (*pStack)->st_addr += sizeof(node);
    return (*pStack)->st_addr;
}

void stack_free(Stack **pStack) {
    (*pStack)->st_addr -= sizeof(node);
}

void push(Stack **stack, char *text) {

    node *new_node = (node *) stack_malloc(stack);
    strcpy(new_node->data, text);

    if ((*stack)->head == NULL) {
        (*stack)->head = new_node;
        new_node->next = NULL;

    } else {
        new_node->next = (*stack)->head;
        (*stack)->head = new_node;
    }
    (*stack)->size++;

}


void pop(Stack **stack) {
    if ((*stack)->head == NULL) {
//        printf("Empty stack \n");
        return;
    }


    if ((*stack)->head->next == NULL) {
        /*old free*/
//        free((*stack)->head);
        /*new free*/
        stack_free(stack);
        (*stack)->head = NULL;
    } else {
      //  node *top = (*stack)->head;
        (*stack)->head = (*stack)->head->next;
        /*old free*/
//        free(top);
        /*new free*/
        stack_free(stack);
    }
    (*stack)->size--;
}

char *top(Stack **stack) {
    if ((*stack)->size == 0) {
//        perror("ERROR: Stack is empty");
        return "ERROR: Stack is empty";
    }
    return (*stack)->head->data;
}

void free_stack(Stack **stack) {

//    while ((*stack)->size != 0) {
//        pop(stack);
//    }
//    /*old free*/
////    free((*stack));
//    /*new free*/
//    free((*stack));

    munmap((*stack)->init_addr,sizeof (node)*10);

}

void printStack(Stack **stack) {
    for (node *i = (*stack)->head; i != NULL; i = i->next) {
        printf("%s --> ", i->data);
    }
    printf("\n");
}


