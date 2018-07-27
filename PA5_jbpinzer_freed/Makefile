
CFLAGS= -g -Wall

all: PA5

PA5: main.o Simulation.o Grid.o Ant.o DoodleBug.o
	g++ $(CFLAGS) main.o Simulation.o Grid.o Ant.o DoodleBug.o -o main

main.o: main.cpp
	g++ $(CFLAGS) -c main.cpp
	
Simulation.o: Simulation.cpp Simulation.h
	g++ $(CFLAGS) -c Simulation.cpp
	
Grid.o: Grid.cpp Grid.h
	g++ $(CFLAGS) -c Grid.cpp
	

Ant.o: Ant.cpp Ant.h Organism.h
	g++ $(CFLAGS) -c Ant.cpp
	
DoodleBug.o: DoodleBug.cpp DoodleBug.h Organism.h
	g++ $(CFLAGS) -c DoodleBug.cpp

clean:
	rm -f *.o main
	rm -f -r html latex
	
docs:
	doxygen -g Doxyfile