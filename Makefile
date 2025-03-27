# Compiler
CC = gcc

# Compiler flags
CFLAGS = $(shell pkg-config --cflags gtk+-2.0 gdk-pixbuf-2.0)
LDFLAGS = $(shell pkg-config --libs gtk+-2.0 gdk-pixbuf-2.0)

# Target executable
TARGET = tresor

# Source files
SRCS = tresor.c tresor_functions.c

# Object directory
OBJDIR = build

# Object files (generate object file paths in OBJDIR)
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Rule to compile source files into object files
$(OBJDIR)/%.o: %.c
	mkdir -p $(OBJDIR)
	$(CC) -c $< -o $@ $(CFLAGS)

# Clean up generated files
clean:
	rm -rf $(OBJDIR) $(TARGET)
