#include "hello.h"
#include "dbg.h"

#include <stdio.h>

int hello()
{
    log_info("Hello, World!");

    return 0;
}

int fail_hello()
{
    log_err("I failed you");

    return 1;
}

int warn_hello()
{
    log_warn("I warned you");

    return 0;
}

int debug_hello()
{
    debug("I'm debugging stuff: %d", 1000);

    return 0;
}
