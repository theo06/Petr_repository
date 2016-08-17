BIN_DIR = $(PWD)/bin
BUILD_DIR = $(PWD)/build
SRC_DIR = $(PWD)/src

CC = gcc
CFLAGS = -g -O2 -Wall -Werror -I$(SRC_DIR) $(OPTFLAGS)
LDFLAGS = $(OPTLIBS)

export CC CFLAGS LDFLAGS
export BIN_DIR BUILD_DIR SRC_DIR

MODULES = hello
#list darray hashmap hashmap_algos bstree stack queue tstree argparser
TESTS = hello_tests
#list_tests darray_tests hashmap_tests hashmap_algos_tests \
	bstree_tests stack_tests queue_tests tstree_tests

.PHONY: all build clean clobber tags test

all: $(MODULES) $(TESTS)

$(MODULES): build
	cd src/$@ && $(MAKE) $(COMMAND)

$(TESTS): MODULES = $(patsubst %_tests,%,$@)
$(TESTS): CFLAGS+=-DDEBUG
$(TESTS): build
	$(MAKE) $(MODULES) COMMAND=test
	$(MAKE) tests/$@ CFLAGS+=-Isrc/$(MODULES) LDLIBS+=$(BUILD_DIR)/lib$(MODULES).a

build:
	@mkdir -p bin
	@mkdir -p build

clean clobber:
	@$(MAKE) $(MODULES) COMMAND=$@
	rm -f tests/*.o tests/*_tests
	rm -rf bin build
	rm -r bin build

tags:
	rm -f ./tags
	ctags -R ./tests/minunit.h ./src/

test:
	./tests/runtests.sh
