#include <cstdio>

#include <unistd.h>

#include "pthread-wrappers.h"

Cond c;
Mutex m;

void *child(void *) {
    printf("child: begin\n");
    m.lock();
    printf("child: signal\n");
    c.signal();
    m.unlock();
    return NULL;
}
int main() {
    Thread p;
    printf("parent: begin\n");
    p.create(child);
    sleep(2);
    printf("parent: wait to be signalled...\n");
    m.lock();
    c.wait(m); 
    m.unlock();
    printf("parent: end\n");
    return 0;
}

