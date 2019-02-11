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
psa: psa.o process.o commons.o priority.o screen.o alg.o pool.o pcb.o
	$(CC) $(CPPFLAGS) -o psa.app psa.o process.o commons.o priority.o screen.o alg.o pool.o pcb.o

# Provide source files:
psa.o: psa.cpp
	$(CC) -c psa.cpp

process.o: process.cpp
	$(CC) -c process.cpp

commons.o: commons.cpp
	$(CC) -c commons.cpp

priority.o: priority.cpp
	$(CC) -c priority.cpp

screen.o: screen.cpp
	$(CC) -c screen.cpp

alg.o: alg.cpp
	$(CC) -c alg.cpp

pool.o: pool.cpp
	$(CC) -c pool.cpp

pcb.o: pcb.cpp
	$(CC) -c pcb.cpp

# Remove executable files, as well as old .o object
# files and *~ backup files:
clean:
	$(RM) psa *.o *~
