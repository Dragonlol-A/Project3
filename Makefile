# Compiler
CC = gcc

CFLAGS = $(shell pkg-config --cflags gtk+-2.0 gdk-pixbuf-2.0)
LDFLAGS = $(shell pkg-config --libs gtk+-2.0 gdk-pixbuf-2.0)

TARGET = tresor

SRCS = tresor.c tresor_functions.c

OBJDIR = build

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)



all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)


$(OBJDIR)/%.o: %.c
	mkdir -p $(OBJDIR)
	$(CC) -c $< -o $@ $(CFLAGS)


$(OBJDIR)/tresor.o: tresor.c tresor_functions.h
$(OBJDIR)/tresor_functions.o: tresor_functions.c tresor_functions.h

doc:
	@doxygen Doxyfile

.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(TARGET)
