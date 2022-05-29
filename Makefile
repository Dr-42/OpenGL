CC=g++
CFLAGS=-Wall -pedantic

LIBS=-lm -lGLEW -lglfw -lGL 

run: main
	./main
main: main.cpp
	$(CC) -o main main.cpp $(CFLAGS) $(LIBS)
clean:
	rm -f main *.o
