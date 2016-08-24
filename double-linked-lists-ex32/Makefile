BIN_DIR = $(PWD)/bin
BUILD_DIR = $(PWD)/build
SRC_DIR = $(PWD)/src

CC = gcc
CFLAGS = -g -O2 -Wall -Werror -I$(SRC_DIR) $(OPTFLAGS)
CFLAGS += -I/usr/include -L/usr/lib 
LDFLAGS = $(OPTLIBS)
LDLIBS += -lcunit
# Export variables to anoter makefiles
export CC CFLAGS LDFLAGS LDLIBS
export BIN_DIR BUILD_DIR SRC_DIR

# List of modules
MODULES = list list_algo
# List of test suites
TESTS = list_tests list_algo_tests

.PHONY: all build clean clobber tags test

all: $(MODULES) $(TESTS)

# How to build target from the list of modules
$(MODULES): build
ifeq ($(COMMAND),mu_tests)
# If COMMAND=mu_tests
# run 'make module_name_tests' (appropriate target from the list of test suites)
	@$(MAKE) $(patsubst %,%_tests,$@)
else
# Otherwise go to src/module_name and run 'make command' there
	cd src/$@ && $(MAKE) $(COMMAND)
# Here $@ == module_name
# Available commands are: dev, lib, mu_tests (from .zshrc)
# COMMAND can be empty
# So if COMMAND is "dev", do 'make dev', etc.
# Go look at src/hello/Makefile to see how it works with every command
endif

# How to build target from the list of test suites
# First get module name from test suit name by removing the _tests ending
$(TESTS): MODULE = $(patsubst %_tests,%,$@)
# Then add DDEBUG flag
$(TESTS): CFLAGS+=-DDEBUG
$(TESTS): build
	# Run 'make module_name COMMAND=test'
	@$(MAKE) $(MODULE) COMMAND=test
	# Run 'make tests/test_name CFLAGS+=... LDLIBS+=...'
	# Here we let make decide what to do. It should find test_name.c file
	# in test/ directory and build a binary tests/test_name, using flags
	# we passed to it.
	@echo "cflags: $(CFLAGS)"
	@$(MAKE) tests/$@ CFLAGS+=-Isrc/$(MODULE) CFLAGS+=-Isrc/list LDLIBS+=$(BUILD_DIR)/lib$(MODULE).a LDLIBS+=$(BUILD_DIR)/liblist.a
#added ldlibs at the end
#added CFLAGS+=-Isrc/list_algo
#removed CFLAGS+=-Isrc/list
build:
	@mkdir -p bin
	@mkdir -p build

# How to clean everything
clean clobber:
	# Go to every module and run 'make clean'
	@$(MAKE) $(MODULES) COMMAND=$@
	# Clean tests
	rm -f tests/*.o tests/*_tests
	rm -rf bin build

tags:
	rm -f ./tags
	ctags -R ./tests/minunit.h ./src/

test:
#	./tests/runtests.sh
	./tests/list_algo_tests
print:
	@echo dollar make: $(MAKE)
