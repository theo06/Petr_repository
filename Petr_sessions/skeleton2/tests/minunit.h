#ifndef __MINUNIT_H__
#define __MINUNIT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Initialization
 */
#define mu_init() MU_ERROR = MUE_SUCCESS

/*
 * Assertion
 */
#define mu_assert(A) do { __test_suite.running->asserts_ran++; \
    if (!(A)) { \
	__mu_add_failure(__LINE__, __FILE__, #A); \
	return; \
    } \
} while(0)

/*
 * Add scenario to suite
 */
typedef void (*mu_test_func) ();
#define mu_add_test(name, test) __mu_add_test(name, (mu_test_func)test)
#define MU_ADD_TEST(test) __mu_add_test(#test, (mu_test_func)test)

/*
 * Run all tests
 */
#define mu_run_tests() printf("%s: start\n", __FILE__); \
    __mu_run_tests(); \
    __mu_print_result()

/*
 * Cleanup
 */
#define mu_cleanup() do { __mu_test *cur, *test = __test_suite.first; \
    __mu_failure *fail; \
    while(test) { \
	cur = test; test=test->next; fail=cur->failure; \
	if (fail) { \
	    free(fail->file); \
	    free(fail->condition); \
	    free(fail); \
	} \
	free(cur); \
    } \
} while(0)

/*
 * Error codes
 */
enum {
    MUE_SUCCESS = 0,
    MUE_OUT_OF_MEMORY = 1,
    MUE_INTERNAL_ERROR = 2,
    MUE_NULL_ARGUMENT = 3,
} MU_ERROR;


/* ---- Internal ---- */

/*
 * Failure condition
 */
typedef struct __mu_failure {
    int assert_number;
    unsigned int line;
    char *file;
    char *condition;
} __mu_failure;

/*
 * Test structure
 */
typedef struct __mu_test {
    /* params */
    const char *name;
    mu_test_func func;
    /* status */
    int asserts_ran;
    __mu_failure *failure;
    /* list */
    struct __mu_test *next;
} __mu_test;

/*
 * Suite structure
 */
typedef struct __mu_suite {
    /* list */
    __mu_test *first;
    __mu_test *last;
    /* current test */
    __mu_test *running;
    /* status */
    int tests_run;
    int tests_failed;
    int tests;
} __mu_suite;

/*
 * MU global
 */
__mu_suite __test_suite;

inline void __mu_add_failure(unsigned int line, const char *strfile,
			     const char *strcond)
{
    __mu_failure *fail = NULL;

    fail = calloc(1, sizeof(__mu_failure));
    if (!fail) {
	MU_ERROR = MUE_INTERNAL_ERROR;
	return;
    }

    fail->file = calloc(strlen(strfile) + 1, 1);
    if (!fail->file) {
	MU_ERROR = MUE_INTERNAL_ERROR;
	free(fail);
	return;
    }
    fail->condition = calloc(strlen(strcond) + 1, 1);
    if (!fail->condition) {
	free(fail->file);
	free(fail);
	MU_ERROR = MUE_INTERNAL_ERROR;
	return;
    }

    memcpy(fail->file, strfile, strlen(strfile));
    memcpy(fail->condition, strcond, strlen(strcond));
    fail->line = line;
    fail->assert_number = __test_suite.running->asserts_ran;

    __test_suite.running->failure = fail;
    return;
}

inline int __mu_add_test(const char *name, mu_test_func func)
{
    __mu_test *test = NULL;

    if (!name || !func) {
	MU_ERROR = MUE_NULL_ARGUMENT;
	return MU_ERROR;
    }

    test = calloc(1, sizeof(__mu_test));
    if (!test) {
	MU_ERROR = MUE_OUT_OF_MEMORY;
	return MU_ERROR;
    }

    test->name = name;
    test->func = func;

    if (!__test_suite.first && !__test_suite.last) {
	__test_suite.first = test;
	__test_suite.last = test;
    } else if (__test_suite.first && __test_suite.last) {
	__test_suite.last->next = test;
	__test_suite.last = test;
    } else {
	MU_ERROR = MUE_INTERNAL_ERROR;
	free(test);
	return MU_ERROR;
    }
    __test_suite.tests++;

    return MU_ERROR;
}

inline void __mu_run_tests()
{
    __mu_test *test = __test_suite.first;
    while (test) {
	__test_suite.running = test;
	printf("  Test: %s ... ", test->name);
	test->func();
	if (MU_ERROR) {
	    return;
	}
	if (test->failure) {
	    __test_suite.tests_failed++;
	    printf("FAILED\n");
	    printf("    %d. %s:%d: mu_assert( %s )\n",
		    test->failure->assert_number,
		    test->failure->file,
		    test->failure->line,
		    test->failure->condition);
	} else {
	    printf("passed\n");
	}
	test = test->next;
	__test_suite.tests_run++;
    }

    return;
}

inline void __mu_print_result()
{
    printf("\n");
    printf("Summary:\tTotal\tRan\tPassed\tFailed\n");
    printf("  Tests\t\t%d\t%d\t%d\t%d\n", __test_suite.tests,
	    __test_suite.tests_run,
	    __test_suite.tests_run - __test_suite.tests_failed,
	    __test_suite.tests_failed);
    printf("\n");

    return;
}



#endif /* __MINUNIT_H__ */
