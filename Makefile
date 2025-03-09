# Compiler and flags
CC = clang
CFLAGS = -Wall -Wextra -g

# Files and targets
TARGET = program
SRC = main.c
OBJ = $(SRC:.c=.o)

# Default target
all: $(TARGET)

# Compile the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean up
clean:
	rm -f $(TARGET) $(OBJ)
	rm -f *~ \#*\#

.PHONY: all run clean

