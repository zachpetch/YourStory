CC := gcc
CFLAGS := -Wall -g `pkg-config --cflags gtk4`
LIBS := `pkg-config --libs gtk4`
SRCDIR := src
TARGET := YourStory
MAIN_SOURCE := $(SRCDIR)/main.c

# Default target
$(TARGET): $(MAIN_SOURCE)
	@$(CC) $(CFLAGS) $< -o $@ $(LIBS)
	@echo "Compiled $< successfully!"

clean:
	@rm -f $(TARGET)
	@echo "Cleanup complete!"
