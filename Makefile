CC = gcc
CFLAGS = -Wall -Wextra

SRCDIR = src
INCDIR = include

TARGET = scanner

$(TARGET): $(SRCDIR)/main.c $(SRCDIR)/scanner/scanner.c $(SRCDIR)/utils/ip_range.c $(SRCDIR)/scanner/read_config.c | config.cfg
	$(CC) $(CFLAGS) -I$(INCDIR) -o $@ $^

config.cfg:
	touch config.cfg

.PHONY: clean
clean:
	rm -f $(TARGET)
