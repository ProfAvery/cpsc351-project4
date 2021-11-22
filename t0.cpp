#include <cstdio>
#include <cstdlib>

#include "pthread-wrappers.h"

void *mythread(void *arg) {
    printf("%s\n", (char *) arg);
    return NULL;
}

int main(int argc, char *[]) {                    
    if (argc != 1) {
    fprintf(stderr, "usage: main\n");
    exit(1);
    }

    Thread p1, p2;
    printf("main: begin\n");
    p1.create(mythread, const_cast<char *>("A")); 
    p2.create(mythread, const_cast<char *>("B"));
    // join waits for the threads to finish
    p1.join();
    p2.join();
    printf("main: end\n");
    return 0;
}

