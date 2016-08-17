#ifndef __DBG_H__
#define __DBG_H__

#include <errno.h>
#include <stdio.h>
#include <string.h>

#ifdef DEBUG
#define debug(M, ...) \
    fprintf(stderr, "debug (%s:%d): " M "\n", \
	    __FILE__, __LINE__, ##__VA_ARGS__)

#else	/* DEBUG */
#define debug(M, ...)

#endif	/* DEBUG */

#define get_error() (errno == 0 ? "None" : strerror(errno))

#define log_err(M, ...) \
    fprintf(stderr, "error (%s:%d: errno: %s): " M "\n", \
	    __FILE__, __LINE__, get_error(), ##__VA_ARGS__)

#define log_warn(M, ...) \
    fprintf(stderr, "warning (%s:%d: errno: %s): " M "\n", \
	    __FILE__, __LINE__, get_error(), ##__VA_ARGS__)

#define log_info(M, ...) \
    fprintf(stderr, "info (%s:%d): " M "\n", \
	    __FILE__, __LINE__, ##__VA_ARGS__)

#define check(A, M, ...) \
    if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

#define sentinel(M, ...) \
    { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

#define check_debug(A, M, ...) \
    if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error; }



#endif	/* __DBG_H__ */
