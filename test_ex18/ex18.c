#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "dbg.h"

void die(const char *message)
{
    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}
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

    return target;

error:	
	if (target) free(target);
	return NULL;
}

int sorted_order(int a, int b) {return a - b;}

int reverse_order(int a, int b){return b - a;}

int strange_order(int a, int b){
  if(a == 0 || b == 0) {
    return 0;
  } else {
    return a % b;
  }
}


/** 
 * Used to test that we are sorting things correctly
 * by doing the sort and printing it out.
 */
int test_sorting(int *numbers, int count, compare_cb cmp)
{
    int i = 0;
    int *sorted = bubble_sort(numbers, count, cmp);

    //if(!sorted) die("Failed to sort as requested.");
	

    for(i = 0; i < count; i++) {
        printf("%d ", sorted[i]);
    }
    printf("\n");

    free(sorted);
	return 0;
error:
	if (sorted) free(sorted);
	return 1;
}


int main(int argc, char *argv[])
{
    //if(argc < 2) die("USAGE: ex18 4 3 1 5 6");
	check( argc >= 2, "USAGE: ex18 4 3 1 5 6");

    int count = argc - 1;
    int i = 0;
    char **inputs = argv + 1;

    int *numbers = malloc(count * sizeof(int));
	int *result = NULL;
	check_mem(numbers);	
	/*check_mem(result);*/

    for(i = 0; i < count; i++) {
        numbers[i] = atoi(inputs[i]);
    }
	result = bubble_sort(numbers, count, sorted_order);
	check_mem(result);
	
	check(test_sorting(numbers, count, sorted_order) == 0, "test_sorting sorted order failed");
	check(test_sorting(numbers, count, reverse_order) == 0, "test_sorting reverse order failed.");
	check(test_sorting(numbers, count, strange_order) == 0, "test_sorting strange order failed.");

    free(numbers);
	free(result);
    return 0;
error:
	if (result) free(result);
	return 1;
}
