# @author: David Kelly
# @date:   29/11/2017

Exe = wator
Cc = g++
Flags = -std=c++11 -pthread -pg
Cfiles = main.cpp
Hfiles =
RM = rm

all: $(Cfiles) $(Hfiles)
	$(Cc) $(Flags) *.cpp -o $(Exe) $(DEBUGFLAGS)

DEBUG: DEBUGFLAGS = -g -O0
DEBUG: ALL

clean:
	$(RM) *.o *~