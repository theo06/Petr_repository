BIN_DIR = $(PWD)/bin

CC = gcc
CFLAGS = -g -ggdb3 -Wall

EXERCISES = ex0

.PHONY: all build clean

all: 
	@echo List of exercises: $(EXERCISES)

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
