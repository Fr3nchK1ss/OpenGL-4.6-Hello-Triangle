# Hellor Colorful Triangle Makefile
# ludo456 @github
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#

CC = g++
CFLAGS  = -g -Wall
LIBS = -lGL -lglfw -ldl
INCL = ./include
DEPS =  gl_utils.cpp glad.c
EXE = hello_colorful_triangle

.PHONY: run

# typing 'make' will invoke the first target entry in the file
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
all: $(EXE) run

# To create the executable file count we need the object files
# countwords.o, counter.o, and scanner.o:
#
$(EXE): $(EXE).cpp $(DEPS)
	$(CC) $(CFLAGS) $^ $(LIBS) -I$(INCL) -o bin/$(EXE)

run:
	./bin/$(EXE)
