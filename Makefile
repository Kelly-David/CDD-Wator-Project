# David Kelly 
# 29/11/2017
# Wator Makefile
# Commands to  compile source code. 
# Usage: Type 'make' in project directory

EXE = wator
CC=g++
CFLAGS= -std=c++11 -pthread
HFILES=
CPPFILES=main.cpp

# All .o files depend on .cpp file with same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

ALL: $(HFILES) $(CFILES)
	$(CC) -o $(EXE) $(CFLAGS) $(CPPFILES) $(DEBUGFLAGS) 

DEBUG: DEBUGFLAGS = -g -O0 -Wall
DEBUG: ALL

# Generate documentation
docs: 
	doxygen doxyfile

# Remove the object files
CLEAN:
	rm *.o
