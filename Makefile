#makefile for
OBJS = Utilities.o FinalProject.o TravelTracker.o Graph.o
CC = g++
CPPFLAGS = -Wall -std=c++11
PROG = FinalProject

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CPPFLAGS) $(OBJS) -o $(PROG)

FinalProject.o:
	$(CC) $(CPPFLAGS) -c FinalProject.cpp

Utilities.o: Utilities.h
	$(CC) $(CPPFLAGS) -c Utilities.cpp

TravelTracker.o: TravelTracker.h
	$(CC) $(CPPFLAGS) -c TravelTracker.cpp

Graph.o: Graph.h
	$(CC) $(CPPFLAGS) -c Graph.cpp

clean:
	$(RM)  $(PROG) $(OBJS)
