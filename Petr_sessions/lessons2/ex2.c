#include <stdio.h>
#include <string.h>

/* This exercise covers stack and heap.
 * If we can declare local variables, why even allocate memory, right?
 * So, let's see.
 *
 *
 * When you declare variables inside the function block, they are
 * places in stack.
 *
 * What's stack?
 * Stack is LIFO data structure (Last In First Out). Basically it's
 * an array, in which you put and remove elements from the top.
 * Like a pack of biscuits or pile of plates, I dunno..
 * Stack exists for a process, so you can't reach other programm's stack.
 * Every function on start puts its variables in stack and remove
 * them on return.
 *
 * Simple example:
 *
 * int get_increment() {
 *    int increment = 1;
 *    return increment;
 * }
 *
 * int func(int a) {
 *    int i;
 *    i = get_increment();
 *    a += i;
 *    return arg;
 * }
 *
 * int main(int argc, char **argv) {
 *     int arg = 15;
 *     int ret = 0;
 *
 *     ret = func(arg);
 *     return ret;
 * }
 *
 * Here's how it looks:
 *
 *            							    Stack
 *
 * |                    |  |                    |  |                    |  |                    |  |                    |  |                    |
 * |                    |  |                    |  |                    |  |                    |  |                    |  |                    |
 * |                    |  |                    |  |                    |  |                    |  |                    |  |                    |
 * |                    |  |                    |  |                    |  |                    |  |                    |  |                    |
 * |                    |  |                    |  |                    |  |                    |  |                    |  |                    |
 * |                    |  |                    |  |       increment=1  |  |                    |  |                    |  |                    |
 * |                    |  |                    |  |<get_increment vars>|  |                    |  |                    |  |                    |
 * |                    |  |       i            |  |       i            |  |       i=1          |  |                    |  |                    |
 * |                    |  |       a=15         |  |       a=15         |  |       a=16         |  |                    |  |                    |
 * |                    |  | <func special vars>|  | <func special vars>|  | <func special vars>|  |                    |  |                    |
 * |       ret=0        |  |       ret=0        |  |       ret=0        |  |       ret=0        |  |       ret=16       |  |                    |
 * |       arg=15       |  |       arg=15       |  |       arg=15       |  |       arg=15       |  |       arg=15       |  |                    |
 * |       argv         |  |       argv         |  |       argv         |  |       argv         |  |       argv         |  |                    |
 * |       argc         |  |       argc         |  |       argc         |  |       argc         |  |       argc         |  |                    |
 * | <main special vars>|  | <main special vars>|  | <main special vars>|  | <main special vars>|  | <main special vars>|  |                    |
 * +--- your program ---+  +--- your program ---+  +--- your program ---+  +--- your program ---+  +--- your program ---+  +--- your program ---+
 * |        ....        |  |        ....        |  |        ....        |  |        ....        |  |        ....        |  |        ....        |
 * | <some system vars> |  | <some system vars> |  | <some system vars> |  | <some system vars> |  | <some system vars> |  | <some system vars> |
 * |        ....        |  |        ....        |  |        ....        |  |        ....        |  |        ....        |  |        ....        |
 * +-------bottom-------+  +-------bottom-------+  +-------bottom-------+  +-------bottom-------+  +-------bottom-------+  +-------bottom-------+
 *
 *        in main		      in func		  in get_increment       after get_increment     after func in main          after main
 *        									      in func
 *
 * So, as you can see, function puts local variables on top of the stack,
 * and remove them on return. But not only local variables. There's more.
 * Instances, I called special, contains function location is stack,
 * return value and return address. By return address I mean the address
 * of the line in code, from where this function was called. So the
 * program can continue.
 *
 * First thing that you should know about stack - it's really small.
 * 4Mb or something like this.
 * That's why you can't store too much data in it.
 * The following example will crash with segfault
 */
typedef struct some_data {
    int count;
    char array[100][100];
} some_data;

void test1()
{
    some_data data_array[4000]; /* Will crash with segfault */
    printf("Success\n");

    return;
}

/* That's exactly why you see warnings from gcc about unused variables.
 * The stack is small and you should put there only the data you really need.
 * So, you should declare all the large data in heap or bss/data.
 *
 * Heap.
 * You're already know about heap. It's a big pile of unused memory, which can
 * be allocated by malloc family functions. The system will give you enough or
 * nothing, if no space left on RAM (always check the return value).
 *
 * bss/data.
 * I'm not going to dig too deep in this.
 * All you need to know, that it's a section in memory, where all the
 * global/static variables are take place, and it's always initiialized.
 * It's almost impossible to overflow this section, so the next example
 * will execute correctly
 */

void test2()
{
    static some_data data_array[4000]; /* Will work */
    printf("Success\n");

    return;
}

/* You should always keep in mind, that local variables are being removed
 * from stack after the execution. Static variables, on the other hand, are not
 */

int* test3()
{
    int i = 200;
    return &i; /* Return the address of the variable, declared in stack */
}

int* test4()
{
    static int i = 200;
    return &i; /* Return the address of the variable, declared in bss/data */
}

/* Also, you should remember, that variables in stack data is not initialized,
 * and bss is. That's because stack is being reused over and over and
 * initialization would decrease the efficiency.
 */
void test5()
{
    static int b;
    int a = 10;
    int a1; /* It filled with garbage, but the garbage might be 0 */
    printf("local: %d, static: %d\n", a1, b);
    return;
}

/* In this example I'll print local variables from test6_declare in
 * test6_print function.
 * It's no magic. Functions declare the same amount of memory in stack,
 * and because the stack is being reused without initialization, we can
 * do shit like this.
 */

void test6_declare()
{
    int i = 0;
    unsigned long arr[10];
    for (i=0; i < 10; i++) {
	arr[i] = 77777777;
    }
    return;
}

void test6_print()
{
    int i = 0;
    unsigned long arr[10];
    for (i=0; i < 10; i++) {
	printf("%lu\n", arr[i]);
    }
    return;
}

int main(int argc, char **argv)
{
    int i = 16;
    printf("Exercise 2\n");

#ifdef TEST1
    printf("Try to declare too much data in stack\n");
    test1();
#endif

#ifdef TEST2
    printf("Try to declare the same thing static\n");
    test2();
#endif

#ifdef TEST3
    printf("Try to access removed data\n");
    int *i_ptr = test3();
    printf("i is %d\n", *i_ptr); /* i was removed from stack,
				  * so the address points nowhere, and
				  * the following will crash with segfault
				  */
#endif

#ifdef TEST4
    printf("Try to access static data\n");
    int *i_ptr = test4();
    printf("i is %d\n", *i_ptr); /* will work */
#endif

#ifdef TEST5
    test5();
#endif

#ifdef TEST6
    test6_declare();
    test6_print();
#endif

    return 0;
}
