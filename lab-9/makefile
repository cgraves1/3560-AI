CC=g++
CFLAGS=-std=c++11

all: main.o main
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp
main: main.o
	$(CC) $(CFLAGS) -o main.out main.o
clean:
	rm main.o main.out