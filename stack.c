//
// Created by 97252 on 4/19/2022.
//

#include "stack.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>


struct flock lock;
int dummy_fd;
/* O_WRONLY ->
 * O_CREAT -> */

int dummy_file() {
    dummy_fd = open("dummy_df.txt", O_WRONLY | O_CREAT);
    if (dummy_fd == -1) {
        perror("Error at opening the dummy_file\n");
    }
    memset(&lock, 0, sizeof(lock));
    return dummy_fd;
}

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
    /* set the lock on this function */
    lock.l_type = F_WRLCK;
    fcntl(dummy_fd, F_SETLKW, &lock);

    printf(" init lock \n");


    /* CRITICAL SECTION */
    sleep(4);
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
    /* END OF CRITICAL SECTION */

    /* Free the lock */
    lock.l_type = F_UNLCK;
    fcntl(dummy_fd, F_SETLK, &lock);

    printf("unlock \n ");


}


void pop(Stack **stack) {

    /* set the lock on this function */
    lock.l_type = F_WRLCK;
    fcntl(dummy_fd, F_SETLKW, &lock);

    printf(" init lock \n");


    /* CRITICAL SECTION */
    sleep(4);
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
    /* END OF CRITICAL SECTION */

    /* Free the lock */
    lock.l_type = F_UNLCK;
    fcntl(dummy_fd, F_SETLK, &lock);

    printf("unlock \n ");

}

char *top(Stack **stack) {

    /* set the lock on this function */
    lock.l_type = F_WRLCK;
    fcntl(dummy_fd, F_SETLKW, &lock);

    printf(" init lock \n");


    /* CRITICAL SECTION */
    sleep(4);
    printf("Finish_sleep\n");
    if ((*stack)->size == 0) {
//        perror("ERROR: Stack is empty");
        /* Free the lock */
        lock.l_type = F_UNLCK;
        fcntl(dummy_fd, F_SETLK, &lock);

        printf("unlock \n ");
        return "ERROR: Stack is empty";
    }
    /* END OF CRITICAL SECTION */

    /* Free the lock */
    lock.l_type = F_UNLCK;
    fcntl(dummy_fd, F_SETLK, &lock);
    printf("unlock \n ");


    return (*stack)->head->data;
}

void free_stack(Stack **stack) {

    /* set the lock on this function */
    lock.l_type = F_WRLCK;
    fcntl(dummy_fd, F_SETLKW, &lock);


    /* CRITICAL SECTION */

//    while ((*stack)->size != 0) {
//        pop(stack);
//    }
//    /*old free*/
////    free((*stack));
//    /*new free*/
//    free((*stack));

    munmap((*stack)->init_addr, sizeof(node) * 10);

}

void printStack(Stack **stack) {
    for (node *i = (*stack)->head; i != NULL; i = i->next) {
        printf("%s --> ", i->data);
    }
    printf("\n");
}


