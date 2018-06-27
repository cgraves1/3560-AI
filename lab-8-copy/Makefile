CC=g++
CFLAGS=-Wall -std=c++11
RM=rm -f

lab8.out: lab8.o
	$(CC) $(CFLAGS) -o lab8.out lab8.o

lab7.o: lab8.cpp
	$(CC) $(CFLAGS) -c lab8.cpp

clean: 
	$(RM) *.o lab8

