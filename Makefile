CC=gcc
CFLAGS=-Wall -g 
#-fsanitize=address -static-libasan

libmyterm: lib myterm.o
	ar rcs lib/$@.a myterm.o

myterm.o: myterm.c 
	$(CC) $(CFLAGS) -c $^

libmsc: lib simple_computer.o
	ar rcs lib/$@.a simple_computer.o

libmybigchar: lib mybigchar.o
	ar rcs lib/$@.a mybigchar.o

mybigchar.o: mybigchar.c
	$(CC) $(CFLAGS) -c $^

simple_computer.o: simple_computer.c
	$(CC) $(CFLAGS) -c $^ 

lib:
	mkdir $@

bin:
	mkdir $@

test.myterm: bin libmyterm
	gcc -o bin/test_myterm test/test_myterm.c -I . -L lib -lmyterm

test.mybigchar: bin libmybigchar libmyterm
	gcc -o bin/test_mybigchar test/mybigchar.c -I . -L lib -lmybigchar -lmyterm

clean:
	rm *.o 2> /dev/null