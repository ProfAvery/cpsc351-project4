#include <cstdio>
#include <cstdlib>
#include <cassert>

#include "pthread-wrappers.h"

typedef struct {
    int a;
    int b;
} myarg_t;

typedef struct {
    int x;
    int y;
} myret_t;

void *mythread(void *arg) {
    myarg_t *args = (myarg_t *) arg;
    printf("args %d %d\n", args->a, args->b);
    myret_t *rvals = new myret_t;
    assert(rvals != NULL);
    rvals->x = 1;
    rvals->y = 2;
    return (void *) rvals;
}

int main() {
    Thread p;
    myret_t *rvals;
    myarg_t args = { 10, 20 };
    p.create(mythread, &args);
    rvals = reinterpret_cast<myret_t *>(p.join());
    printf("returned %d %d\n", rvals->x, rvals->y);
    delete rvals;
    return 0;
}

