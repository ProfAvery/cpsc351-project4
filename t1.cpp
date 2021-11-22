#include <cstdio>
#include <cstdlib>

#include "pthread-wrappers.h"


int max;
volatile int counter = 0; // shared global variable

void *mythread(void *arg) {
    char *letter = reinterpret_cast<char *>(arg);
    int i; // stack (private per thread) 
    printf("%s: begin [addr of i: %p]\n", letter,
            reinterpret_cast<void *>(&i));
    for (i = 0; i < max; i++) {
    counter = counter + 1; // shared: only one
    }
    printf("%s: done\n", letter);
    return NULL;
}
                                                                             
int main(int argc, char *argv[]) {                    
    if (argc != 2) {
    fprintf(stderr, "usage: main-first <loopcount>\n");
    exit(1);
    }
    max = atoi(argv[1]);

    Thread p1, p2;
    printf("main: begin [counter = %d] [%lx]\n", counter, 
       (unsigned long int) &counter);
    p1.create(mythread, const_cast<char *>("A")); 
    p2.create(mythread, const_cast<char *>("B"));
    // join waits for the threads to finish
    p1.join();
    p2.join();
    printf("main: done\n [counter: %d]\n [should: %d]\n", 
       counter, max*2);
    return 0;
}

