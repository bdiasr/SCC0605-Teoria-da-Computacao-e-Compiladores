CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = programa

SRCDIR = src
OBJDIR = obj

SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -f $(OBJDIR)/*.o $(TARGET)
