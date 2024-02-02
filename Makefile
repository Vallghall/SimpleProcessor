CC=gcc

libmyterm: lib myterm.o
	ar rcs lib/$@.a myterm.o

myterm.o: myterm.c 
	$(CC) -c $^

libmsc: lib simple_computer.o
	ar rcs lib/$@.a simple_computer.o

simple_computer.o: simple_computer.c
	$(CC) -c $^ 

lib:
	mkdir $@

bin:
	mkdir $@

test.myterm: bin libmyterm
	gcc -o bin/test_myterm test/test_myterm.c -I . -L lib -lmyterm

clean: *.o
	rm $^