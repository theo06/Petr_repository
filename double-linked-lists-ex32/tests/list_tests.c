#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
//#include "CUnit/Automated.h"
//#include "CUnit/Console.h"

#include "list.h"
#include <stdio.h>

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

static List *list = NULL;
char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";


void test_create(void)
{
	/*
	 *int* all=NULL; 
	 **all=5; free(all); 
	 *printf("%d\n", *all);
	 */
	list = List_create();
	CU_ASSERT(list != NULL);
}

void test_destroy(void)
{
    List_destroy(list);
	if(!list) puts("List *list is null");
	else	
		puts("List *list != null");
	List_destroy(list);
}

void test_push_pop(void)
{
    List_push(list, test1);
    CU_ASSERT(List_last(list) == test1);

    List_push(list, test2);
    CU_ASSERT(List_last(list) == test2);

    List_push(list, test3);
    CU_ASSERT(List_last(list) == test3);
    CU_ASSERT(List_count(list) == 3);

    char *val = List_pop(list);
    CU_ASSERT(val == test3);

    val = List_pop(list);
    CU_ASSERT(val == test2);

    val = List_pop(list);
    CU_ASSERT(val == test1);
    CU_ASSERT(List_count(list) == 0);
}

void test_unshift(void)
{
    List_unshift(list, test1);
    CU_ASSERT(List_first(list) == test1);

    List_unshift(list, test2);
    CU_ASSERT(List_first(list) == test2);

    List_unshift(list, test3);
    CU_ASSERT(List_first(list) == test3);
    CU_ASSERT(List_count(list) == 3);
} 
void test_remove(void)
{
    // we only need to test the middle remove case since push/shift 
    // already tests the other cases

    char *val = List_remove(list, list->first->next);
    CU_ASSERT(val == test2);
    CU_ASSERT(List_count(list) == 2);
    CU_ASSERT(List_first(list) == test3);
    CU_ASSERT(List_last(list) == test1);
}
void test_shift(void)
{
    CU_ASSERT(List_count(list) != 0);

    char *val = List_shift(list);
    CU_ASSERT(val == test3);

    val = List_shift(list);
    CU_ASSERT(val == test1);
    CU_ASSERT(List_count(list) == 0);
}
/************* Test Runner Code goes here **************/

int main ( void )
{
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if ( CUE_SUCCESS != CU_initialize_registry() )
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite( "list_test_suite", init_suite, clean_suite );
   if ( NULL == pSuite ) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   if ( (NULL == CU_add_test(pSuite, "test_create", test_create)) ||
        (NULL == CU_add_test(pSuite, "test_push_pop", test_push_pop)) ||
        (NULL == CU_add_test(pSuite, "test_unshift", test_unshift)) ||
		(NULL == CU_add_test(pSuite, "test_remove", test_remove)) ||
		(NULL == CU_add_test(pSuite, "test_shift", test_shift)) ||
		(NULL == CU_add_test(pSuite, "test_destroy", test_destroy))
      )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // Run all tests using the basic interface
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   printf("\n");
   CU_basic_show_failures(CU_get_failure_list());
   printf("\n\n");
/*
   // Run all tests using the automated interface
   CU_automated_run_tests();
   CU_list_tests_to_file();

   // Run all tests using the console interface
   CU_console_run_tests();
*/
   /* Clean up registry and return */
   CU_cleanup_registry();
   return CU_get_error();
}
