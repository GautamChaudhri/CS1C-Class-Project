CC = g++
FLAGS = -std=c++14 -Wall -g
OBJS = main.o

# FOLDERS
V_DIR = ./vector

all: main

main: $(OBJS) $(V_DIR)/vector.h
	$(CC) $(FLAGS) -o main $(OBJS)

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp -o main.o

vector.o: $(V_DIR)/vector.cpp
	$(CC) $(FLAGS) -c $(V_DIR)/vector.cpp -o vector.o

run:
	./main

val:
	valgrind ./main

clean:
	rm -f *.o main

tar:
	tar cf graphics-modeler.tar hw*.scr Makefile *.cpp valgrind_main.rpt