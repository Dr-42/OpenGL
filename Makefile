CC=g++
CFLAGS=-Wall -pedantic -g -O2 -std=c++11

LIBS=-lm -lassimp -lGLEW -lglfw -lGL 

all: main

run: main
	./main
main: main.cpp utils/shader.cpp
	$(CC) -o main main.cpp utils/shader.cpp $(CFLAGS) $(LIBS)
clean:
	rm -f main *.o
