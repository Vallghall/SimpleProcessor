CC=gcc

# Static library extension
ifeq ($(OS), Windows_NT)
	SL_EXT=.lib
else
	SL_EXT=.a
endif

libmsc: lib simple_computer.o
	ar rcs lib/$@$(SL_EXT) simple_computer.o

simple_computer.o: simple_computer.c
	$(CC) -c $^ 

lib:
	mkdir $@
