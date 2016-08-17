#include <stdio.h>

#include "hello.h"

int main(int argc, char *argv[])
{
    printf("Hello program\n");

    hello();
    warn_hello();
    fail_hello();
    debug_hello();

    return 0;
}
