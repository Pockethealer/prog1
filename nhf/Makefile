# Variables
CC = gcc                  # Compiler
CFLAGS = -Wall -Werror         # Compilation flags
LDFLAGS =                  # Linker flags
TARGET = ReceptWizard          # Name of the final executable

# Collect all .c files and .res file in the directory
SRCS = $(wildcard *.c)
RES = $(wildcard *.res)      # The .res file

# Default target: compile and link everything directly into the executable
all:
	$(CC) $(CFLAGS) $(SRCS) $(RES) -o $(TARGET) $(LDFLAGS)

# Clean up the executable
clean:
	rm -f $(TARGET)

# Run the program after building
run: all
	./$(TARGET)

# Phony targets
.PHONY: all clean run