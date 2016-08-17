#include <stdio.h>

#define print_s(obj) { \
    int i = 0; \
    printf("Function addr: %p\n", obj.func); \
    printf("char array: "); \
    for (i=0; i < 7; i++) \
	printf("%02X ", obj.c_arr[i]); \
    printf("\n"); }

#define print_ls(obj) \
    printf("Long structure:\n"); \
    printf("int: %02X\n", obj.i); \
    print_s(obj.s_obj);

int main(int argc, char **argv)
{
    /* Structures in memory
     *
     * You should remember from ex0 that array is just a contiguos
     * block of memory (int array[5] - simply 20 bytes of memory).
     *
     * But what's structure?
     * It's the same thing as array, but array allows you to
     * store variables of the same type, while in structure
     * you can store variables of different types.
     *
     * So, basically
     *
     * struct s {
     *     int *i_ptr;		>* 8 bytes *<
     *     int i;		>* 4 bytes *<
     *     char c_arr[8];	>* 8 bytes *<
     * };
     *
     * is the same thing as
     * int i_array[5];
     *
     * Here is our array in memory:
     *
     *       4 bytes    4 bytes    4 bytes    4 bytes    4 bytes
     * ----+----------+----------+----------+----------+----------+----
     *     |          |          |          |          |          |
     *     |    0     |     1    |     2    |     3    |     4    |
     *     |          |          |          |          |          |
     * ----+----------+----------+----------+----------+----------+----
     *     |			 |	    |			  |
     *     +------- i_ptr -------|---- i ---|----- c_arr[8] ------+
     *     |							  |
     *     +-------------------------  s  ------------------------+
     *     |							  |
     *     |--------------------- i_array[5] ---------------------|
     *     
     * That's why everything from ex0 can be applyed to structures
     *
     * But you may remember, that the C doesn't make you work with raw memory.
     * Instead you use types.
     * If you want to store 1 byte, use char; 4 bytes - int;
     * 8 bytes - long; etc.
     *
     * So, what's heppening, when you store int in char?
     * It 'cuts' int to char and store. What does it mean?
     */
    int i = 0xAABB;
    unsigned char c = '\0';
    c = i;
    printf("int: %X; char: %X\n", i, c);
    printf("\n");
    /*
     * Here the last byte from i will be stored in c.
     * Why?.. Because little endian.
     *
     *         byte       byte
     * ----+----------+----------+
     *     |          |          |
     *     |    BB    |    AA    | <= int
     *     |          |          |
     * ----+----------+----------+
     *     |			 |
     *     +--------- i ---------|
     *     |	      |
     *     +--- c ----|
     *
     * So, you can see, that it actually stores the FIRST byte, not the LAST.
     * But because of little endian, it's less significant.
     * So, when I say 'cut to smth', I mean, only first N bytes will be stored.
     * When you cut pointer to int, int will filled with first 4 bytes of
     * pointer.
     *
     * Now let's try your example
     */

    struct s {
	int (*func)(int argc, char **argv);
	unsigned char c_arr[7];
    };
    struct ls {
	struct s s_obj;
	int i;
    };
    struct ls_reverse {
	int i;
	struct s s_obj;
    };

    struct s s_obj = {.func=main, .c_arr = { 1, 2, 3, 4, 5, 6, 7 }};
    struct ls ls_obj = {0};
    struct ls_reverse ls_reverse_obj = {0};

    print_s(s_obj);
    printf("\n");

    print_ls(ls_obj); /* Filled with zeros */
    printf("\n");

    ls_obj = *((struct ls*)&s_obj); /* I expand s_obj to bigger size
				       sizeof(struct ls); expanded memory is
				       taken from stack (as all local
				       variables), so it filled with garbage.
				       Actually it's not garbage, but think of
				       it that way for now */
    print_ls(ls_obj); /* Compare with s_obj. int is filled with garbage. */
    printf("\n");

    ls_reverse_obj = *((struct ls_reverse*)&s_obj);
    print_ls(ls_reverse_obj); /* Compare with s_obj.
				 Now int contains first 4 bytes of function
				 address, address contains array of chars,
				 and array filled with garbage */
    printf("\n");
    return 0;
}
