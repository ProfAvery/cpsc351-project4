#include <cstdio>

#include <unistd.h>

#include "pthread-wrappers.h"

Cond c;
Mutex m;
int done = 0;

void *child(void *) {
    printf("child\n");
    sleep(1);
    m.lock();
    done = 1;
    c.signal();
    m.unlock();
    return NULL;
}
int main() {
    Thread p;
    printf("parent: begin\n");
    p.create(child);
    m.lock();
    while (done == 0) 
    c.wait(m); // releases lock when going to sleep
    m.unlock();
    printf("parent: end\n");
    return 0;
}

