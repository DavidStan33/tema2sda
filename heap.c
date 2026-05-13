// Stan David-Gabriel 313CD

#include <stdlib.h>
#include <string.h>
#include "heap.h"

heap *create_heap(int capacity)
{
	heap *h = (heap *)malloc(sizeof(heap));
	h->size = 0;
	h->capacity = capacity;
	h->files = (node_file **)malloc(sizeof(node_file *) * capacity);
	return h;
}

static int compare(node_file *a, node_file *b)
{
	if (a->score > b->score)
		return 1;
	if (a->score < b->score)
		return 0;
	if (strcmp(a->id, b->id) < 0)
		return 1;
	else
		return 0;
}

static heap *sift_up(heap *h, int index)
{
	while (index > 0 &&
	       compare(h->files[(index - 1) / 2], h->files[index]) == 0) {
		node_file *aux = h->files[(index - 1) / 2];
		h->files[(index - 1) / 2] = h->files[index];
		h->files[index] = aux;
		index = (index - 1) / 2;
	}
	return h;
}

heap *insert_heap(heap *h, node_file *file)
{
	if (h->size == h->capacity) {
		h->capacity *= 2;
		h->files = realloc(h->files, h->capacity * sizeof(node_file *));
	}
	h->files[h->size] = file;
	h = sift_up(h, h->size);
	h->size++;
	return h;
}

static heap *sift_down(heap *h, int index)
{
	int max_index = index;
	int l = index * 2 + 1;
	if (l < h->size && compare(h->files[l], h->files[max_index]) == 1)
		max_index = l;
	int r = index * 2 + 2;
	if (r < h->size && compare(h->files[r], h->files[max_index]) == 1)
		max_index = r;
	if (index != max_index) {
		node_file *aux = h->files[index];
		h->files[index] = h->files[max_index];
		h->files[max_index] = aux;
		h = sift_down(h, max_index);
	}
	return h;
}

node_file *extract_max(heap *h)
{
	node_file *max = NULL;
	if (h && h->size > 0) {
		max = h->files[0];
		h->files[0] = h->files[h->size - 1];
		h->size--;
		h = sift_down(h, 0);
	}
	return max;
}

heap *free_heap(heap *h)
{
	if (h) {
		free(h->files);
	}
	free(h);
	return NULL;
}
