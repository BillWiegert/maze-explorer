CC=clang++
CPPFLAGS= -Wall -g -fno-exceptions
# Adding -fno-exceptions to allow this to compile using clang under Cygwin64.
# (Otherwise the linker won't work in a Cygwin64 terminal window.)
CFLAGS=-c $(CPPFLAGS)

OBJECTS=maze.o vector2d.o

EXEC=exploremaze

all: $(EXEC)

# maze.o: maze.h maze.cpp
# 	$(CC) $(CFLAGS) -c maze.cpp -o maze.o
# 
# vector2d.o: vector2d.h vector2d.cpp
# 	$(CC) $(CFLAGS) -c vector2d.cpp -o vector2d.o
	
exploremaze: test_maze_type.cpp $(OBJECTS) 
	$(CC) $(CPPFLAGS) $(OBJECTS) $< -o $(EXEC)

%.o: %.cpp %.h
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXEC)
