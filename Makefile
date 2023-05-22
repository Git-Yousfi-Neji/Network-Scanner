CC = gcc
CFLAGS = -Wall -Wextra

SRCDIR = src
INCDIR = include

TARGET = scanner

$(TARGET): $(SRCDIR)/main.c $(SRCDIR)/scanner/scanner.c $(SRCDIR)/utils/ip_range.c
	$(CC) $(CFLAGS) -I$(INCDIR) -o $@ $^

.PHONY: clean
clean:
	rm -f $(TARGET)

