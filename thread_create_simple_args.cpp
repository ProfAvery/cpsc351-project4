#include <cstdio>

#include "pthread-wrappers.h"

void *mythread(void *arg) {
    long long int value = (long long int) arg;
    printf("%lld\n", value);
    return (void *) (value + 1);
}

int main() {
    Thread p;
    long long int rvalue;
    p.create(mythread, (void *) 100);
    rvalue = reinterpret_cast<long long int>(p.join());
    printf("returned %lld\n", rvalue);
    return 0;
}

