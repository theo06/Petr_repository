#include "hello.h"
#include "minunit.h"

void test_1_success()
{
    mu_assert(hello() == 0);
    mu_assert(warn_hello() == 0);
    mu_assert(debug_hello() == 0);
}

void test_2_fail()
{
    mu_assert(hello() == 0);
    mu_assert(fail_hello() == 0);
    mu_assert(hello() == 40);
}

void test_3_success()
{
    mu_assert(hello() == 0);
}

int main()
{
    mu_init();

    if	(
	    MU_ADD_TEST(test_1_success) != MUE_SUCCESS ||
	    MU_ADD_TEST(test_2_fail) != MUE_SUCCESS ||
	    mu_add_test("Successful hello test", test_3_success) != MUE_SUCCESS
	)
	goto error;

    mu_run_tests();

error:
    mu_cleanup();
    return MU_ERROR;
}
