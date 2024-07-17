TP=entropy
CC=gcc
MAKE=make
CFLAGS=-Wall -g -I lib/
SRC=$(wildcard lib/*.c)
OBJ=$(SRC:.c=.o)
LDFLAGS=-lm
ARCHIVE_FILES=$(wildcard lib/*.c lib/*.h tests/*.h tests/*.c *.c) lib/Makefile tests/Makefile Makefile AUTHORS
MAIN=filentropy

all: library $(MAIN)

$(MAIN): $(MAIN).o $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<
library:
	$(MAKE) -C lib
clean:
	rm -f $(OBJ) $(MAIN) $(MAIN).o
cleanall: clean
	rm -rf doc/
doc: $(SRC)
	doxygen .doxyfile
archive: tp-$(TP).zip
tp-$(TP).zip: $(ARCHIVE_FILES)
	zip $@ $(ARCHIVE_FILES)
.PHONY: clean archive library cleanall all
