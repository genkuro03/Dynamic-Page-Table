#*Ethan Fox
#*CS 480 - Operating Systems
# *Ben Shen
# *9/9/2024
# *REDID = 826136708

# Compiler and flags
CC = g++

CFLAGS = -g3 -x c++ -c
CCFLAGS = -std=c++11 -g3 -Wall -c

# Source files
C_SRC = log.c tracereader.c
CPP_SRC = pagetable.cpp pagetabledefinition.cpp pagelevel.cpp argparser.cpp 

PROGRAM_MAIN = pagetrace.cpp

# Object files (derived from source files)
C_OBJ = $(C_SRC:.c=.o)
CPP_OBJ = $(CPP_SRC:.cpp=.o)

PROGRAM_OBJ = $(PROGRAM_MAIN:.cpp=.o)

# Output binaries
PROGRAM = pagetrace

# Default target builds both executables
all: $(PROGRAM)

# Rule to build the pagetrace executable
$(PROGRAM): $(PROGRAM_OBJ) $(C_OBJ) $(CPP_OBJ)
	$(CC) -o $(PROGRAM) $(PROGRAM_OBJ) $(C_OBJ) $(CPP_OBJ)

# Rule to compile C source files into object files
%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

# Rule to compile C++ source files into object files
%.o: %.cpp
	$(CC) $(CCFLAGS) $< -o $@

# Clean target to remove the binary and object files
clean:
	rm -f  $(PROGRAM) $(PROGRAM_OBJ) $(C_OBJ) $(CPP_OBJ)
