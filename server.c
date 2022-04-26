//
// Created by barak on 26/04/2022.
//

//
// Created by barak on 15/04/2022.
//

//
// Created by 97252 on 4/14/2022.
//

/*
** server.c -- a stream socket server demo
*/
#define EQUAL 0

#include <stdio.h>
#include "stack.h"
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include "stack.c"

#include "assert.h"
//#include "malloc.h"
//#include "malloc.c"

#define PORT "3490"  // the port users will be connecting to

#define BACKLOG 10     // how many pending connections queue will hold
Stack *shared_st;
Stack *test_st;
int server_running = 1;
int sockfd;
int new_fd;

/* Stack Thread safety handlers */


//int test() {
//
//    test_st = (Stack *) my_malloc(sizeof(Stack));
//
//    /* checking allocation correctness */
//    void *new_address = sbrk(0);
//    assert((int *) test_st != (int *) new_address);
//
//    printf("Passed Allocation tests\n");
//    /* push one string to stack.
//     * check if the top of the stack matches the last value pushed, expected --> "test1"*/
//    push(&test_st, "test1");
//    assert(strcmp(top(&test_st), "test1") == 0);
//    /* push another string to the stack.
//     * check if the top value updated, expected --> "test2".
//     * check if the size updated, expected --> 2.*/
//    push(&test_st, "test2");
//    assert(test_st->size == 2);
//    assert(strcmp(top(&test_st), "test2") == 0);
//
//
//    /* POP until stack is empty
//     * check size, expected --> 0
//     * check top on empty stack, expected --> ERROR message on empty stack*/
//    pop(&test_st);
//    pop(&test_st);
//    assert(test_st->size == 0);
//    assert(strcmp(top(&test_st), "ERROR: Stack is empty") == EQUAL);
//
//    /* check case when call pop on empty stack,
//     * expected --> no change on stack, return string with ERROR prefix*/
//    pop(&test_st);
//    assert(test_st->size == 0);
//    assert(strcmp(top(&test_st), "ERROR: Stack is empty") == EQUAL);
//
//    free_stack(&test_st);
//    printf("Passed all stack tests.\n");
//    printf("server initializing...\n");
//    return 1;
//}

void sig_handler(int signum) {
    free_stack(&shared_st);
    server_running = 0;
    close(new_fd);

    close(sockfd);
    exit(1);
}

void sigchld_handler(int s) {
    (void) s; // quiet unused variable warning

    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while (waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}


// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in *) sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *) sa)->sin6_addr);
}

void *send_hello(void *arg) {
    int *s = (int *) arg;
    if (send(*s, "Hello, world!", 13, 0) == -1) {
        perror("send");
    }
    return 0;
}

void *server_listener(void *arg) {
    int *s = (int *)arg;
    if (send(*s, "Hello, world!", 13, 0) == -1) {
        perror("send");
    }
    char client_msg[text_length] = {0}; // '\0'

    while (1) {
        memset(client_msg, 0, text_length);
        size_t r;
        if ((r = recv(*s, client_msg, sizeof(client_msg), 0)) == -1) {
            perror("recv");
            exit(1);
        }
        if (r != 0) {
            /** --------------------------------- STACK SECTION ---------------------------------*/

            /**------------ TOP ------------*/
            /* if the given command is TOP, the server will send the client the top value in the shared stack.*/
            if (strcmp("TOP", client_msg) == EQUAL) {


                /* ~START~ READ DATA CRITICAL SECTION */

                char *buff = top(&shared_st);
                if (send(*s, buff, strlen(buff), 0) == -1) {
                    perror("send");
                }
                /* ~END~ READ DATA CRITICAL SECTION */

            }
                /**------------ POP ------------*/
                /* if the given command is POP, the server will pop the top value in the shared stack */
            else if (strcmp("POP", client_msg) == EQUAL) {



                /* ~START~ Delete DATA CRITICAL SECTION */

                printf("POPING\n");
                pop(&shared_st);
                /* ~END~ Delete DATA CRITICAL SECTION */


            }
                /**------------ PUSH ------------*/
                /* if the given command is PUSH,
                 * the server will push the attached text after the command to the shared stack.*/
            else if (strncmp("PUSH", client_msg, 4) == EQUAL) {

                /* ~START~ Write DATA CRITICAL SECTION */

                printf("WRITING DATA\n");
                char text[text_length];
                strncpy(text, client_msg + 5, strlen(client_msg) - 4);
                push(&shared_st, text);
                /* ~END~ Write DATA CRITICAL SECTION */

            }
        } else {
            break;
        }
    }
}


int main(void) {
//    int test_status = test();
    /* INIT the server shared stack */
    shared_st = (Stack *) malloc(sizeof(Stack));
    shared_st->head = NULL;


    int status;

    /* Connection methods start here -> */
    // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    struct sigaction sa;
    int yes = 1;
    char s[INET6_ADDRSTRLEN];
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for (p = servinfo; p != NULL; p = p->ai_next) {
        printf(" hello from PID: %d\n", getpid());
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                       sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if (p == NULL) {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

//    signal(SIGINT, sig_handler);

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("server: waiting for connections...\n");

    /* initializing array of threads with size of 10(the max of concurrency clients).
     * also init unsigned long thread_num to be the index of each thread
     * that will serve the current connection with the client*/
    pthread_t client_h[BACKLOG];
    unsigned long thread_num = 1;

    while (server_running) {  // main accept() loop
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *) &their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }


        inet_ntop(their_addr.ss_family,
                  get_in_addr((struct sockaddr *) &their_addr),
                  s, sizeof s);
        printf("server: got connection from %s\n", s);


        if (!fork()) { // this is the child process
//        close(sockfd); // child doesn't need the listener
            server_listener(&new_fd);
            close(new_fd);
            exit(0);
        }
    }
    close(new_fd);  // parent doesn't need this

    return 0;
}



/*if (!fork()) { // this is the child process
            close(sockfd); // child doesn't need the listener
            if (send(new_fd, "Hello, world!", 13, 0) == -1)
                perror("send");
            close(new_fd);
            exit(0);
        }
        close(new_fd);  // parent doesn't need this*/
