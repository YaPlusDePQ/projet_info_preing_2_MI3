CC := gcc
EXECNAME := exe
DIRECTORIES := $(sort $(dir $(wildcard ../src/*/)))
SRC := $(foreach dir, $(DIRECTORIES), $(dir)*.c)

BUILD:
	$(CC) -Wall $(SRC) -o $(EXECNAME)