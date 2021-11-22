#include <cstdio>

#include <unistd.h>

#include "pthread-wrappers.h"

Cond c;
Mutex m;
int done = 0;

void *child(void *) {
    printf("child: begin\n");
    sleep(1);
    done = 1;
    printf("child: signal\n");
    c.signal();
    return NULL;
}
int main() {
    Thread p;
    printf("parent: begin\n");
    p.create(child);
    m.lock();
    printf("parent: check condition\n");
    while (done == 0) {
    sleep(2);
    printf("parent: wait to be signalled...\n");
    c.wait(m);
    }
    m.unlock();
    printf("parent: end\n");
    return 0;
}

