CC=g++
CFLAGS=-Wall -pedantic -g -O2 -std=c++11

LIBS=-lm -lGLEW -lglfw -lGL 

all: main

run: main
	./main
main: main.cpp shader.cpp
	$(CC) -o main main.cpp shader.cpp $(CFLAGS) $(LIBS)
clean:
	rm -f main *.o
