CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -g
TARGET = search_index
SOURCES = main.c list.c tree.c commands.c

.PHONY: build clean

build: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)
