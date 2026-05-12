#ifndef HEAP_H
#define HEAP_H

#include "files.h"

typedef struct Heap {
	int size;
	int capacity;
	NodeFile** files;
} Heap;

Heap *createHeap(int capacity);

Heap *insertHeap(Heap *heap, NodeFile *file);

NodeFile *extractMax(Heap *heap);

Heap *freeHeap(Heap *heap);

#endif
