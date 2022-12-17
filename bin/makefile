CC := gcc
EXECNAME := exe
DIRECTORIES := $(sort $(dir $(wildcard ../src/c/)))
SRC := $(foreach dir, $(DIRECTORIES), $(dir)*.c)

BUILD:
	$(CC) -Wall $(SRC) -o $(EXECNAME)