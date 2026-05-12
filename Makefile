CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -g
TARGET = search_index
SOURCES = main.c files.c read.c tree.c commands.c heap.c utils.c
HEADERS = commands.h files.h heap.h read.h tree.h utils.h
ARCHIVE = tema2.zip

.PHONY: build run clean pack

build: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

run: build
	./$(TARGET)

clean:
	rm -f $(TARGET) *.o

pack: clean
	rm -f $(ARCHIVE)
	zip $(ARCHIVE) $(SOURCES) $(HEADERS) README Makefile
