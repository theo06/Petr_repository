BIN_DIR = $(PWD)/bin

CC = gcc
CFLAGS = -g -ggdb3 -Wall

EXERCISES = ex0 ex1

all: 
	@echo List of exercises: $(EXERCISES) ex2

ex2 : SRC = $(patsubst %,%.c,$@)
ex2 : build
	$(CC) $(CFLAGS) -DTEST1 $(SRC) -o $(BIN_DIR)/ex2.1
	$(CC) $(CFLAGS) -DTEST2 $(SRC) -o $(BIN_DIR)/ex2.2
	$(CC) $(CFLAGS) -DTEST3 $(SRC) -o $(BIN_DIR)/ex2.3
	$(CC) $(CFLAGS) -DTEST4 $(SRC) -o $(BIN_DIR)/ex2.4
	$(CC) $(CFLAGS) -DTEST5 $(SRC) -o $(BIN_DIR)/ex2.5
	$(CC) $(CFLAGS) -DTEST6 $(SRC) -o $(BIN_DIR)/ex2.6

$(EXERCISES): SRC = $(patsubst %,%.c,$@)
$(EXERCISES): build
	$(CC) $(CFLAGS) $(SRC) -o $(BIN_DIR)/$@
	@echo
	@$(BIN_DIR)/$@

build:
	@mkdir -p bin

clean:
	rm -f *.o *.s
	rm -rf bin

.PHONY: all build clean
