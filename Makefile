# Makefile for Loan Management System

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g -std=c99  # Ensure code compiles with C99 standard

# Executable name
EXECUTABLE = loan_manager

# Source files
SOURCES = main.c queue.c priority_queue.c

# Object files
OBJECTS = $(SOURCES:.c=.o)

# Default target
all: $(EXECUTABLE)

# Link the program
$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $^

# Compile each source file to an object file
main.o: main.c loans.h
	$(CC) $(CFLAGS) -c main.c

queue.o: queue.c loans.h
	$(CC) $(CFLAGS) -c queue.c

priority_queue.o: priority_queue.c loans.h
	$(CC) $(CFLAGS) -c priority_queue.c

