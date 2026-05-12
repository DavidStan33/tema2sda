#include <stdlib.h>
#include <string.h>
#include "heap.h"

Heap *createHeap(int capacity) {
	Heap *heap = (Heap *) malloc(sizeof(Heap));
	heap->size = 0;
	heap->capacity = capacity;
	heap->files = (NodeFile **) malloc(sizeof(NodeFile *) * capacity);
	return heap;
}

static int compare(NodeFile *a, NodeFile *b) {
	if(a->score > b->score)
		return 1;
	if(a->score < b->score)
		return 0;
	if(strcmp(a->id, b->id) < 0)
		return 1;
	else
		return 0;
}

static Heap *siftUp(Heap *heap, int index) {
	while(index > 0 && compare(heap->files[(index - 1) / 2], heap->files[index]) == 0) {
		NodeFile *aux = heap->files[(index - 1) / 2];
		heap->files[(index - 1) / 2] = heap->files[index];
		heap->files[index] = aux;
		index = (index - 1) / 2;
	}
	return heap;
}

Heap *insertHeap(Heap *heap, NodeFile *file) {
	if(heap->size == heap->capacity) {
		heap->capacity *= 2;
		heap->files = realloc(heap->files, heap->capacity * sizeof(NodeFile *));
	}
	heap->files[heap->size] = file;
	heap = siftUp(heap, heap->size);
	heap->size++;
	return heap;
}

static Heap *siftDown(Heap *heap, int index) {
	int maxIndex = index;
	int l = index * 2 + 1;
	if(l < heap->size && compare(heap->files[l], heap->files[maxIndex]) == 1)
		maxIndex = l;
	int r = index * 2 + 2;
	if(r < heap->size && compare(heap->files[r], heap->files[maxIndex]) == 1)
		maxIndex = r;
	if(index != maxIndex) {
		NodeFile *aux = heap->files[index];
		heap->files[index] = heap->files[maxIndex];
		heap->files[maxIndex] = aux;
		heap = siftDown(heap, maxIndex);
	}
	return heap;
}

NodeFile *extractMax(Heap *heap) {
	NodeFile *max = NULL;
	if(heap && heap->size > 0) {
		max = heap->files[0];
		heap->files[0] = heap->files[heap->size - 1];
		heap->size--;
		heap = siftDown(heap, 0);
	}
	return max;
}

Heap *freeHeap(Heap *heap) {
	if (heap != NULL) {
		free(heap->files);
	}
	free(heap);
	return NULL;
}
