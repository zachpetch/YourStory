# Define the compiler
CC := gcc

# Define any compile-time flags
CFLAGS := -Wall -g

# Define the source directory
SRCDIR := src

# Define the target executable name
TARGET := chitchat

# Find the main.c file in the source directory
MAIN_SOURCE := $(SRCDIR)/main.c

# Default target
$(TARGET): $(MAIN_SOURCE)
	@$(CC) $(CFLAGS) $< -o $@
	@echo "Compiled $< successfully!"

# Clean target
clean:
	@rm -f $(TARGET)
	@echo "Cleanup complete!"

