# Compiler:
CC = clang++

# Compiler flags:
#  -g    	adds debugging information to the executable file
#  -std=c++11	use c++ 11 standard
#  -Wall 	turns on most, but not all, compiler warnings
#  -lncurses  	adds the ncurses library
CPPFLAGS = -g -std=c++11 -Wall -lncurses

# Invoke the first target entry:
default: psa

# To create the executable file:
psa: psa.o process.o commons.o
	$(CC) $(CPPFLAGS) -o psa.app psa.o process.o commons.o

# Provide source files:
psa.o: psa.cpp
process.o: process.cpp process.h priority.h commons.h
commons.o: commons.cpp commons.h

# Remove executable files, as well as old .o object
# files and *~ backup files:
clean:
	$(RM) psa *.o *~
