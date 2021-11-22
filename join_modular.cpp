#include <cstdio>

#include <unistd.h>

#include "pthread-wrappers.h"

//
// Simple sync "object"
//

struct synchronizer_t {
    Cond c;
    Mutex m;
    int done;

    synchronizer_t(): done(0) { };
    void signal();
    void wait();
};

synchronizer_t s;

void synchronizer_t::signal() {
    m.lock();
    done = 1;
    c.signal();
    m.unlock();
}

void synchronizer_t::wait() {
    m.lock();
    while (done == 0) 
    c.wait(m); 
    done = 0; // reset for next use
    m.unlock();
}


//
// Main threads
//

void *child(void *) {
    printf("child\n");
    sleep(1);
    s.signal();
    return NULL;
}
int main() {
    Thread p;
    printf("parent: begin\n");
    p.create(child);
    s.wait();
    printf("parent: end\n");
    p.join();
    return 0;
}

