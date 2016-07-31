CFLAGS=-g -Wall -Werror

OBJS=ex18.o
APP=ex18

all : $(APP)

$(APP) : $(OBJS)
	gcc $(CFLAGS) $(OBJS) -o $@

.PHONY: all test valgrind clean tags

test: $(APP)
	./ex18 4 3 1 2 5 9 6

tags:
	ctags -R ./*

valgrind: $(APP)
	valgrind ./ex18 4 3 1 2 5 9 6

clean:
	rm -f $(APP) $(OBJS)
