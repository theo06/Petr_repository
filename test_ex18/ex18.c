#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "dbg.h"

// a typedef creates a fake type, in this
// case for a function pointer
typedef int (*compare_cb)(int a, int b);

/**
 * A classic bubble sort function that uses the 
 * compare_cb to do the sorting. 
 */
int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
    int temp = 0;
    int i = 0;
    int j = 0;
    int *target = malloc(count * sizeof(int));

    check_mem(target);

    memcpy(target, numbers, count * sizeof(int));

    for(i = 0; i < count; i++) {
	for(j = 0; j < count - 1; j++) {
	    if(cmp(target[j], target[j+1]) > 0) {
		temp = target[j+1];
		target[j+1] = target[j];
		target[j] = temp;
	    }
	}
    }
    memcpy(numbers, target, count * sizeof(int));

    free(target);
    return numbers;

error:	
    /* No need to check, it's wasn't allocated. Give up */
    return NULL;
}

int sorted_order(int a, int b) {return a - b;}

int reverse_order(int a, int b) {return b - a;}

int strange_order(int a, int b) {return (a && b) ? a % b : 0;}

/** 
 * Used to test that we are sorting things correctly
 * by doing the sort and printing it out.
 */
int test_sorting(int *numbers, int count, compare_cb cmp)
{
    int i = 0;
    int *sorted = bubble_sort(numbers, count, cmp);
    check(sorted, "Failed to sort");

    for(i = 0; i < count; i++) {
	printf("%d ", sorted[i]);
    }
    printf("\n");

    return 0;

error:
    return 1;
}

int main(int argc, char *argv[])
{

    int count = argc - 1;
    int i = 0;
    char **inputs = argv + 1;
    int *numbers = NULL;
    int *result = NULL;

    check( argc >= 2, "USAGE: ex18 4 3 1 5 6");
    numbers = malloc(count * sizeof(int));
    check_mem(numbers);

    for(i = 0; i < count; i++) {
	numbers[i] = atoi(inputs[i]);
    }
    result = bubble_sort(numbers, count, sorted_order);
    check(result, "Failed to sort");

    check(test_sorting(numbers, count, sorted_order) == 0, "test_sorting sorted order failed");
    check(test_sorting(numbers, count, reverse_order) == 0, "test_sorting reverse order failed.");
    check(test_sorting(numbers, count, strange_order) == 0, "test_sorting strange order failed.");

    free(numbers);
    return 0;
error:
    if (numbers) free(numbers);
    return 1;
}
