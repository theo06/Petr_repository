 a char is 1 byte long
[10:17:13] jose dim1: and an int is 4 byte long
[10:17:20] Peter Nechaev: yes
[10:17:42] Peter Nechaev: first of all, char, int, long, float, etc are types

You know, code written in C should be compiled. If you just give your processor instruction like "for", he'll think you're drunk.
So when you declare a variable, you telling the COMPILER "I need a space for this variable". And the size can be declared by type. char is 1 byte, int is 4 (not all the time. It can be 2,4,8), long is 8 et

What I'm trying to say, is that all types are actually telling how big the variable is and nothing more. And that's important. Because in other languages (let's say Python) declaring a string means you have a string. you can't work with it like with plane memory. In C you can. And you should understand it.

 jose dim1: a pointer is a variable which contains the adress of another variable.
[10:26:04] Peter Nechaev: right. It's just another 8 bytes variable, containing the address. Nothing more. It's not a super-duper interesting C type. It's just variable type of long, with the address.
[10:26:18] Peter Nechaev: it means, it also has an address. Like other variables

[10:27:17] Peter Nechaev: When you do *ptr you telling the compiler, that you need a data from this ptr address.
[10:28:00] Peter Nechaev: and **ptr means data from address from data from ptr address

but ptr only contains the address, not the size of the variable.
Like if you have int *ptr = something_something, can you do char var=*ptr?
[10:30:08] Peter Nechaev: that's a question for you
[10:30:23] jose dim1: * ptr is an int
[10:30:42] jose dim1: so i think an int cannot be stored in a char.
[10:30:51] jose dim1: or maybe there is an implicit cast
[10:31:39] Peter Nechaev: modern compilers will raise a warning, but you actualy can.
[10:32:03] Peter Nechaev: you can even trick it doing implicit cast to int->void->char

and what will you see if you'll do char c=*i_ptr?
[10:32:52] Peter Nechaev: what value will be stored in c?
[10:33:17] jose dim1: if i_ptr is a pointer to an int?
[10:33:25] Peter Nechaev: yes
[10:34:05] jose dim1: what will be stored in c is the character which have an ascii value equals to *i_ptr
[10:35:50] Peter Nechaev: I doesn't have to have an ascii value. You know, you can stor negative values in char, right?
[10:36:12] Peter Nechaev: and here is an ascii table: http://www.asciitable.com/index/asciifull.gif
it's from 0 to 127

and *i_ptr may equal to 30000. Which ascii variable is it?
[10:37:28] Peter Nechaev: so you don't know, right?

As you said int is 4 bytes, and char is only 1 byte.
The *i_ptr will contain the address of the first byte in memory. And when you do this:
int i = *i_ptr; The machine will read 4 bytes from the address i_ptr. But when you do this:
char c = *i_ptr; The machine will read only 1 byte, thinking that here's nothing more.
[10:40:52] Peter Nechaev: I made you a small funny example, that may help you understand:
[10:41:04] Peter Nechaev: Title: 0_basics.tar.gz Description: 0_basics.tar.gz https://login.skype.com/login/sso?go=webclient.xmm&docid=0-neu-d1-13aac98f7248492d87adf7dbb5056710

ell, hex value is 0-F (16 states), which is 4 bits.
then 1 byte (8 bits) can be represented by two hex like FF

[11:08:13] Peter Nechaev: well. The thing is that negative values stores with first bit being 1, and positive with first bit being 0.

tha'ts why hex 7F is 127 and 80 is -128
[11:09:26] Peter Nechaev: then it grows and FF means -1
[11:09:54] Peter Nechaev: so it's 0,1....127,-128,-127,...,-1
 https://en.wikipedia.org/wiki/Two%27s_complement

 dont understand why     printf("First 4 bytes %X\n", *piarr); /* Why it's 3020100, not 10203? */
[11:26:21] Peter Nechaev: tha
[11:27:43] jose dim1: why 10203?
[11:28:45] Peter Nechaev: sorry kernel crush
[11:28:56] Peter Nechaev: give me a second
[11:28:59] jose dim1: ok
[11:30:40] Peter Nechaev: ok, I'm here.
[11:30:43] Peter Nechaev: so
[11:31:32] Peter Nechaev: that's because of you processor representation
[11:31:34] Peter Nechaev: https://en.wikipedia.org/wiki/Endianness
[11:33:04] Peter Nechaev: so in big-endian it will be 0123 and in little-endiad it's 3210
[11:33:29] Peter Nechaev: every x86/x86_64 processor is little-endian
[11:37:35] jose dim1: how does  3020100 represent the first 4 bytes?


Peter Nechaev: it actually 03020100. or 03 - first byte, 02 - second byte, 01 - third byte, 00 - 4th.
It just don't show you the first 0
[11:46:00] Peter Nechaev: because in human readable way 03 is 3, 04 is 4 etc

0100 is 100\
[11:48:30] jose dim1: and why not  00010203 ?
[11:48:36] jose dim1: because of big little endian thing?
[11:48:44] Peter Nechaev: because of the little endian
[11:49:24] Peter Nechaev: in memory it's still 00 01 02 03, but processor starts reading from the lest significant byte (03)
[11:49:32] Peter Nechaev: that's why it's reversed
[11:50:28] jose dim1: but for me 03 is the most heaviest byte. i dont understand why you say 03 is the the lest significant byte
[11:50:54] jose dim1: 03 in hex is 0000 0111 in bits
[11:51:05] Peter Nechaev: nonono.
least significant means the last in memory
[11:51:33] Peter Nechaev: you can do FF BB CC AA, it will still be reversed

http://0.30000000000000004.com/

---------------------session 2
Peter Nechaev: the least significant is first - little endian
[10:20:50] Peter Nechaev: Big-endian and little-endian are terms that describe the order in which a sequence of bytes are stored in computer memory. Big-endian is an order in which the "big end" (most significant value in the sequence) is stored first (at the lowest storage address). Little-endian is an order in which the "little end" (least significant value in the sequence) is stored first. For example, in a big-endian computer, the two bytes required for the hexadecimal number 4F52 would be stored as 4F52 in storage (if 4F is stored at storage address 1000, for example, 52 will be at address 1001). In a little-endian system, it would be stored as 524F (52 at address 1000, 4F at 1001).

look
[10:22:38] Peter Nechaev: i is AABB;
AA - first byte, BB - last byte, right?
[10:22:47] jose dim1: ok
[10:22:48] Peter Nechaev: AABB is value!
[10:23:21] Peter Nechaev: then, if it is a value, how AABB will be stored in memory?
[10:23:43] Peter Nechaev: first goes least significant (or the last byte) BB
[10:23:47] Peter Nechaev: then AA
[10:24:00] Peter Nechaev: so value AABB in memory will be stored as BBAA

 ok. and AABBCCDD will be stored as DDCCBBAA?
[10:24:57] Peter Nechaev: yes
[10:25:25] Peter Nechaev: and AADD00BB will be BB00DDAA
[10:25:28] Peter Nechaev: reverse order
[10:25:46] Peter Nechaev: that's what little endian means

so if int i = 0xAABBCC;
[10:28:31] jose dim1: char c = i;
[10:28:41] jose dim1: it is CC who will be stored in c?
[10:28:51] Peter Nechaev: correct

 and the picture I made should explain, why not AA
[10:29:57] jose dim1: i think i got it
[10:30:22] Peter Nechaev: think of it, as, I don't know, boxes
[10:30:45] Peter Nechaev: you have 4 boxes, but you can only carry 2 at the same time
[10:30:50] Peter Nechaev: so you take first two
[10:30:53] Peter Nechaev: right?
[10:30:57] jose dim1: yes
[10:31:06] Peter Nechaev: same thing with variables
[10:31:43] Peter Nechaev: int is 4 bytes, but char can contain only 1 byte.
So it takes only the first byte from memory
[10:32:01] jose dim1: ok but the value AABB is two bytes right?
[10:32:15] Peter Nechaev: yes
[10:32:35] jose dim1: so you can store less than 4 bytes into an int.
[10:32:43] Peter Nechaev: no
[10:32:48] Peter Nechaev: it's still four
[10:32:52] Peter Nechaev: just 0000AABB
[10:32:57] jose dim1: aah ok
[10:33:01] Peter Nechaev: in reverse order: BBAA0000

 for example with
[10:36:20] jose dim1:  struct ls {
	struct s s_obj;
	int i;
    };
[10:36:53] jose dim1: does it mean that the s_obj field of ls will be field with {NULL, NULL} ?
[10:37:22] jose dim1: because s_obj is a struct which contains a pointer to a function and an array?
[10:37:26] Peter Nechaev: not NULL, NULL, but NULL, 0 0 0 0 0
[10:37:28] Peter Nechaev: look
[10:37:41] Peter Nechaev: think of a stucture, as a contiguous block in memory
[10:37:49] Peter Nechaev: long block of bytes
[10:37:56] Peter Nechaev: now fill every byte with 0
[10:38:04] Peter Nechaev: like
[10:38:05] Peter Nechaev: int


int is four bytes. Doing int = 0 you fill 4 bytes with zeros
[10:38:37] Peter Nechaev: now struct is, let's say, 20 bytes long
[10:38:44] Peter Nechaev: you fill them with zeros
[10:38:53] Peter Nechaev: that's initialization
[10:39:25] jose dim1: and if we put 0 inside a pointer it is the same as putting NULL inside it I guess.
[10:39:25] Peter Nechaev: *ptr = NULL means 0000000000000000 ( 8 bytes )
[10:39:34] Peter Nechaev: yes
[10:39:44] Peter Nechaev: NULL is a code word
[10:39:50] Peter Nechaev: which means NULL pointer

: in other words
struct s s_obj = {0};
is just an easier way to do:
struct s s_obj = {.func=NULL, .c_arr = { 0,0,0,0,0 }};

 Peter Nechaev: well, kinda
[10:51:29] Peter Nechaev: you see
when you do *(&s_obj) the compiler will take sizeof(struct s) bytes from address &s_obj. right?
[10:52:47] jose dim1: *(&s_obj) does nothing i think?
[10:53:29] Peter Nechaev: now.
when you cast &s_obj to (struct ls *) the compiler will think, that at the given address he can read sizeof(struct ls) bytes
[10:54:42] Peter Nechaev: so it will read sizeof(struct s) bytes and additional (sizeof(struct ls) - sizeof(struct s)) bytes from the right


 (line 42) you have variable i (4 bytes). You see?
[11:02:09] jose dim1: yes
[11:02:09] Peter Nechaev: to the right of it there is c_arr[8]
[11:02:14] jose dim1: yes i see
[11:02:40] Peter Nechaev: so. If you try to read 8 bytes from i (4 bytes) what will you have?
[11:03:03] Peter Nechaev: you will have 4 bytes of i and left 4 bytes of c_arr[8]
[11:03:10] jose dim1: yes

i am talking about ls_obj
[11:06:42] Peter Nechaev: well, yes. Because size of struct ls is : sizeof(struct s) + sizeof(int)
[11:07:26] Peter Nechaev: and you have sizeof(struct s) bytes declared. That's mean int will be garbage

Peter Nechaev: b = i;
[11:15:25] Peter Nechaev: here i isn't a value. It s a block of memory
[11:15:59] Peter Nechaev: so, the block of memory i will be copied to the block of memory b
[11:16:26] Peter Nechaev: when you store a VALUE, it will be stored in reverse order
[11:16:32] jose dim1: ok
[11:16:42] Peter Nechaev: when you copy a block of memory it will be copied exactly
[11:17:48] Peter Nechaev: when the value will be printed, it will be read in reverse order again
[11:18:02] Peter Nechaev: in human readable way
[11:18:46] jose dim1: ok if I well understood when you do .c_arr = { 1, 2, 3, 4, 5 } in the computer it is stored 0504030201
[11:18:46] Peter Nechaev: so, when you store AABB, it will be store as BBAA,
when you'll try to print it, you'll still see AABB
[11:19:07] Peter Nechaev: no
[11:19:11] Peter Nechaev: that s the idea
[11:19:18] Peter Nechaev: it's an array of CHARS
[11:19:22] Peter Nechaev: char is 1 byte
[11:19:27] Peter Nechaev: there is nothing to reverse
[11:19:36] Peter Nechaev: so it's stored as 01 02 03 04 05
[11:19:37] Peter Nechaev: but
[11:19:48] Peter Nechaev: when you print 8 bytes as one variable
[11:19:59] Peter Nechaev: it will be printed in reverse order.
[11:20:10] Peter Nechaev: as 0504030201
[11:20:23] Peter Nechaev: remember ex0?
[11:20:26] Peter Nechaev: same thing
[11:20:51] Peter Nechaev: if you store an array of chars, it will store them in line one by one
[11:21:10] Peter Nechaev: if you store int, the least significant byte goes first
[11:21:48] Peter Nechaev: when you store an array of int, you store them one by one. But each value itself will be reversed

char arr[2] = {0xaa, 0xbb} - 2 values. will be stored as AABB
int = 0xaabb - 1 value. will be stored as BBAA0000
int arr[2] = {0xaabb, 0xccdd} - 2 values. will be stored BBAA0000DDCC0000

eter Nechaev: yeah
[11:28:14] Peter Nechaev: machine doesn't do it to piss you off.
It just works with numbers this way. You work with numbers as AABB, the computer as BBAA.
[11:28:51] Peter Nechaev: so when you store AABB, you store AABB, not BBAA, but the computer works with them in reverse order.
[11:29:54] Peter Nechaev: so when you mess with the raw memory, you should do it in a way the machine can understand - in reverse order

: shall I forgot the *el = proto in Monster{int hit_points; Object proto}; It takes too much time to see what is going on.
[11:32:46] Peter Nechaev: you didn't understand?
[11:33:42] Peter Nechaev: the last example (ls_reverse_obj) should expain what will happen
[11:33:43] jose dim1: no, i didnt really understand the reverse monster
[11:36:41] Peter Nechaev: I don't know, man. It's literally the same example.
Okay. Try to replase ls_reverse_obj with Monster{int hit_points; Object proto}; s_obj with Object and see what will happen.
[11:37:27] jose dim1: ok so when we do c_arr[] = {1, 2, 3, 4, 5} it will store as 0102030405 because it is a char array
[11:37:59] jose dim1: but what happens to the .func pointer inside s_obj inside ls_reverse?
[11:38:30] Peter Nechaev: it contains 0102030405
[11:38:46] Peter Nechaev: which may be printed as 0504030201 (reverse order)
[11:38:50] jose dim1: ok understood
[11:39:08] jose dim1: no wait.
[11:39:27] jose dim1: why does the .func will contain 0102030405 and not the adress of the array?

… it does contains the address, stored in c_arr
[11:47:22] Peter Nechaev: c_arr in memory is 0102030405
[11:47:53] Peter Nechaev: when you read the whole c_arr at once (not as array of chars), you get it in reverse order
[11:47:59] Peter Nechaev: as one long variable

 If you still don't get it, you should return to this example later
[11:50:38] jose dim1: when you say read, you mean print?
[11:51:00] Peter Nechaev: yes

