# @author: David Kelly
# @date:   09/01/2018

Exe = wator
Cc = g++
Flags = -std=c++11 -pthread
Cfiles = main.cpp
Hfiles =
RM = rm

all: $(Cfiles) $(Hfiles)
	$(Cc) $(Flags) *.cpp -o $(Exe) $(DEBUGFLAGS)

DEBUG: DEBUGFLAGS = -g -O0
DEBUG: ALL

clean:
	$(RM) *.o *~