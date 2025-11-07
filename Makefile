CC ?= gcc
NUM_RESOURCES ?= 4
BOARD_HEIGHT ?= 5
BOARD_WIDTH ?= 3
DEDALE_FLAGS = -D COLOR_PRINTING_ENABLED=1 -D NUM_RESOURCES=$(NUM_RESOURCES) -D BOARD_WIDTH=$(BOARD_WIDTH) -D BOARD_HEIGHT=$(BOARD_HEIGHT)
CFLAGS ?= -Wall -Wextra -g -I./src $(DEDALE_FLAGS)


all: compile

compile: project tester
	@echo "Compile the code and the tests"

project: src/main.o src/dir.o
	@echo "Compile code"
	@$(CC) $(CFLAGS) -o $@ $^	

tester: src/dir.o test/dir.o
	@echo "Compile test"
	@$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $$(find . -name \*~) $$(find . -name \*.o) 

.PHONY: all clean compile test
