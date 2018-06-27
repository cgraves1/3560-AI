CC=g++
CFLAGS=-Wall -std=c++11
RM=rm -f
TESTFILE=iris.csv

lab7.out: lab7.o
	$(CC) $(CFLAGS) -o lab7.out lab7.o

lab7.o: lab7.cpp
	$(CC) $(CFLAGS) -c lab7.cpp

clean: 
	$(RM) *.o lab7

test: lab7(TESTFILE)
	./lab7.out $(TESTFILE)
