CC=g++
CFLAGS=-Wall -std=c++11
RM=rm -f
TESTFILE=iris-binary-normalized.csv

lab6.out: lab6.o
	$(CC) $(CFLAGS) -o lab6.out lab6.o

lab6.o: lab6.cpp
	$(CC) $(CFLAGS) -c lab6.cpp

clean: 
	$(RM) *.o lab6

test: lab6.out $(TESTFILE)
	./lab6.out $(TESTFILE)
