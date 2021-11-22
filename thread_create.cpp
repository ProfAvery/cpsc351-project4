#include <cstdio>

#include "pthread-wrappers.h"

typedef struct {
    int a;
    int b;
} myarg_t;

void *mythread(void *arg) {
    myarg_t *args = (myarg_t *) arg;
    printf("%d %d\n", args->a, args->b);
    return NULL;
}

int main() {
    Thread p;
    myarg_t args = { 10, 20 };

    p.create(mythread, &args);
    p.join();
    printf("done\n");
    return 0;
}
