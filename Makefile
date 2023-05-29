CC = gcc
CFLAGS = -Wall -Wextra -pthread

SRCDIR = src
SRCSCDIR = $(SRCDIR)/scanner
SRCUTLDIR = $(SRCDIR)/utils
INCDIR = include

TARGET = scanner

$(TARGET): $(SRCDIR)/*.c $(SRCSCDIR)/*.c $(SRCUTLDIR)/*.c | config.cfg
	$(CC) $(CFLAGS) -I$(INCDIR) -o $@ $^

config.cfg:
	touch config.cfg

.PHONY: clean
clean:
	rm -f $(TARGET)
