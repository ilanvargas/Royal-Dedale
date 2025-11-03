CC ?= gcc
NUM_RESOURCES ?= 4
BOARD_HEIGHT ?= 5
BOARD_WIDTH ?= 3
DEDALE_FLAGS = -D COLOR_PRINTING_ENABLED=1 -D NUM_RESOURCES=$(NUM_RESOURCES) -D BOARD_WIDTH=$(BOARD_WIDTH) -D BOARD_HEIGHT=$(BOARD_HEIGHT)
CFLAGS ?= -Wall -Wextra -g -I./src $(DEDALE_FLAGS)


all: compile

compile: 
	@echo "Compile the code and the tests"

%.o:
	$(CC) $(CFLAGS) -c $< -o $@

test: 
	@echo "Run the tests"

clean:
	rm -f $$(find . -name \*~) $$(find . -name \*.o) 

.PHONY: all clean compile test
