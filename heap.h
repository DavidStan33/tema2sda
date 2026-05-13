// Stan David-Gabriel 313CD

#ifndef HEAP_H
#define HEAP_H

#include "files.h"

typedef struct heap {
	int size;
	int capacity;
	node_file **files;
} heap;

heap *create_heap(int capacity);

heap *insert_heap(heap *heap, node_file *file);

node_file *extract_max(heap *heap);

heap *free_heap(heap *heap);

#endif
