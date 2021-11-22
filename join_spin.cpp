#include <cstdio>

#include <unistd.h>

#include "pthread-wrappers.h"

volatile int done = 0;

void *child(void *) {
    printf("child\n");
    sleep(5);
    done = 1;
    return NULL;
}

int main() {
    Thread p;
    printf("parent: begin\n");
    p.create(child);
    while (done == 0) 
    ; // spin
    printf("parent: end\n");
    return 0;
}
