CC = g++
FLAGS = -std=c++14 -Wall -g
OBJS = main.o

all: main

main: $(OBJS)
	$(CC) $(FLAGS) -o main $(OBJS)

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp -o main.o

clean:
	rm -f *.o main

tar:
	tar cf graphics-modeler.tar hw*.scr Makefile *.cpp valgrind_main.rpt