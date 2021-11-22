#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <vector>

#include <unistd.h>

#include "pthread-wrappers.h"

using std::vector;

int max;
int loops;
int *buffer; 

int use_ptr  = 0;
int fill_ptr = 0;
int num_full = 0;

Cond empty;
Cond fill;
Mutex m;

int consumers = 1;
int verbose = 1;


void do_fill(int value) {
    buffer[fill_ptr] = value;
    fill_ptr = (fill_ptr + 1) % max;
    num_full++;
}

int do_get() {
    int tmp = buffer[use_ptr];
    use_ptr = (use_ptr + 1) % max;
    num_full--;
    return tmp;
}

void *producer(void *) {
    int i;
    for (i = 0; i < loops; i++) {
    m.lock();                  // p1
    while (num_full == max)    // p2
        empty.wait(m);         // p3
    do_fill(i);                // p4
    fill.signal();             // p5
    m.unlock();                // p6
    }

    // end case: put an end-of-production marker (-1) 
    // into shared buffer, one per consumer
    for (i = 0; i < consumers; i++) {
    m.lock();
    while (num_full == max) 
        empty.wait(m);
    do_fill(-1);
    fill.signal();
    m.unlock();
    }

    return NULL;
}
                                                                               
void *consumer(void *) {
    int tmp = 0;
    // consumer: keep pulling data out of shared buffer
    // until you receive a -1 (end-of-production marker)
    while (tmp != -1) { 
    m.lock();                 // c1
    while (num_full == 0)     // c2 
        fill.wait(m);         // c3
    tmp = do_get();           // c4
    empty.signal();           // c5
    m.unlock();               // c6
    }
    return NULL;
}

int
main(int argc, char *argv[])
{
    if (argc != 4) {
    fprintf(stderr, "usage: %s <buffersize> <loops> <consumers>\n", argv[0]);
    exit(1);
    }
    max = atoi(argv[1]);
    loops = atoi(argv[2]);
    consumers = atoi(argv[3]);

    buffer = (int *) malloc(max * sizeof(int));
    assert(buffer != NULL);

    int i;
    for (i = 0; i < max; i++) {
    buffer[i] = 0;
    }

    Thread pid;
    vector<Thread> cid(consumers);
    pid.create(producer); 
    for (i = 0; i < consumers; i++) {
    cid[i].create(consumer, (void *) (long long int) i); 
    }
    pid.join(); 
    for (i = 0; i < consumers; i++) {
    cid[i].join(); 
    }
    return 0;
}

