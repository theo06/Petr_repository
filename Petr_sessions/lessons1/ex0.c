#include <stdio.h>

int main(int argc, char **argv)
{
    /* Machiene representation:
     *  bit:
     *   1 bit stores 1 or 0, so may have 2 states (1^2)
     *        0		= 0
     *        1		= 1
     *        max value is 1 (2^1 - 1)
     *   2 bits may have 4 states (2^2):
     *       00		= 0
     *       01		= 1
     *       10		= 2
     *       11		= 3
     *        max value is 3 (2^2 - 1)
     *  byte:
     *   1 byte contains 8 bits, may have 256 states (2^8):
     * 00000000		= 0
     * 00000001		= 1
     * 00000010		= 2
     * 00000011		= 3
     * 11111111		= 255 (2^8 - 1)
     *   2 bytes - 16 bits etc.
     *
     * sizeof(char) = 1 byte
     * size of int  = 4 (may be 2, 4, 8 depends on your system)
     *
     * HEX representation: 0-F: 0123...89ABCDEF - 16 values, 4 bits
     *     1000		= 8
     * 10001110		= 8E
     */
    printf("size of char is %lu bytes\n", sizeof(char));
    printf("size of int is %lu bytes\n", sizeof(int));
    printf("size of long is %lu bytes\n", sizeof(long));

    /* Let's start with char
     * char can have 256 different states: -128..127
     */
    char c = '\0';
    c = 'd';
    printf("c is %d:%X\n", c, c);
    /* Can char store only letters? No */
    c = 0;
    printf("c is %d:%X\n", c, c);
    c = -128; /* min */
    printf("c is %d:%X\n", c, c);
    c = 127; /* max */
    printf("c is %d:%X\n", c, c);
    printf("\n");

    /* But what if I'm a moron? */
    c = 1000000810; /* Will store only last byte */
    printf("c is %d:%X\n", c, c);
    printf("original value: %X\n", 1000000810);
    printf("\n");
    c = 128; /* Will store -128. Why? */
    printf("c is %d:%X\n", c, c);
    /* What will happen here: c = 255? */
    printf("\n");

    /* Let's try unsigned char
     * it can have the same 256 states, but: 0..255
     */
    unsigned char uc = '\0';
    uc = 255; /* max */
    printf("uc is %d:%X\n", uc, uc);
    uc = -128; /* will store 128. Why? */
    printf("uc is %d:%X\n", uc, uc);
    printf("\n");

    /* Same with other types */

    /* But let's try pointers */
    printf("size of char* is %lu bytes\n", sizeof(char*));
    printf("size of int* is %lu bytes\n", sizeof(int*));
    printf("size of long* is %lu bytes\n", sizeof(long*));
    /* 8 bytes, which means it's a simple long int variable, nothing more */
    printf("\n");

    /* Let's try pointers to pointers*/
    printf("size of char** is %lu bytes\n", sizeof(char**));
    printf("size of int** is %lu bytes\n", sizeof(int**));
    printf("size of long** is %lu bytes\n", sizeof(long**));
    /* Same thing */
    printf("\n");

    /* Let's play with arrays */
    char arr[] = {0, 1, 2, 3, 4};
    printf("size of array is %lu bytes\n", sizeof(arr));
    /* arr is contiguous 5 bytes of memory */
    int i = 0;
    for (i=0; i < 5; i++) {
	printf("%d ", arr[i]);
    }
    printf("\n");

    char *pcarr = arr; /* Points to first first element (1 byte) */
    printf("First element: %X\n", *pcarr);
    printf("pointer value: %X\n", pcarr); /* First element's address */

    int *piarr = (int*)arr; /* Points to first 4! bytes */
    printf("First 4 bytes %X\n", *piarr); /* Why it's 3020100, not 10203? */
    printf("pointer value: %X\n", piarr); /* Address is still the same! */
    printf("\n");

    /* Now let's try to increment pointers */
    printf("char pointer +1: %X\n", pcarr+1); /* Will add 1 byte */
    printf("int pointer +1: %X\n", piarr+1); /* Will add 4 bytes */
    printf("\n");

    /* Let's change it */
    *piarr = 2000000009;
    /* Now let's see, what's happend with array */
    for (i=0; i < 5; i++) {
	printf("%d ", arr[i]);
    }
    printf("\n");
    /* First 4 elements (4 bytes) have changed
     * 5th element wasn't touched */

    *piarr = 0; /* Better example */
    for (i=0; i < 5; i++) {
	printf("%d ", arr[i]);
    }
    printf("\n");
    
    /* What I'm trying to say here
     *
     * The only difference between types is the size they require to store
     * the value.
     * Pointer always have the same saze of 8 bytes which is enough to cover
     * all your RAM addresses.
     *
     * By declaring int* you tell compiler that at this particular address
     * it can read 4 bytes of memory. And char* means that there is only 1 byte.
     *
     * Here is our array in memory:
     *
     *         byte       byte       byte       byte       byte
     * ----+----------+----------+----------+----------+----------+----
     *     |          |          |          |          |          |
     *     |    0     |     1    |     2    |     3    |     4    |
     *     |          |          |          |          |          |
     * ----+----------+----------+----------+----------+----------+----
     *     |          |                                |
     *     |- *pcarr -|                                |
     *     |          |<- pcarr + 1                    |
     *     |                                           |
     *     |                                           |
     *     |----------------- *piarr ------------------|
     *     |                                           |<- piarr +1
     *     |<- pcarr
     *     |<- piarr
     *
     *
     */

    return 0;
}
