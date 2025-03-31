CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -Werror
OBJDIR = obj
SRCDIR = src
BINDIR = .
TARGET = snake

# Source and Object Files
SRC = $(SRCDIR)/main.c $(SRCDIR)/main_menu.c $(SRCDIR)/game.c $(SRCDIR)/scores.c
OBJ = $(OBJDIR)/main.o $(OBJDIR)/main_menu.o $(OBJDIR)/game.o $(OBJDIR)/scores.o

# Create obj directory if not exists
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Compile object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link the final executable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) -lncurses

# Build target for make snake
snake: $(TARGET)

# Clean compiled files
clean:
	rm -rf $(OBJDIR)/*.o $(TARGET)

# Rebuild everything
all: clean snake
