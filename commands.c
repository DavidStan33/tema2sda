// Stan David-Gabriel 313CD

#include <stdlib.h>
#include <string.h>
#include "commands.h"
#include "heap.h"
#include "utils.h"

int add(list_file *file_list, node_file *file, tree *root)
{
	if (find_file(file_list, file->id)) {
		free_file(file);
		return 0;
	}
	insert_file_at_tail(file_list, file);
	word_node *words = file->words;
	while (words) {
		tree *terminal_node = insert_word_in_tree(root, words->word);
		add_file_ref_to_tree_node(terminal_node, file);
		words = words->next;
	}
	return 1;
}

int del(list_file *file_list, char *id, tree *root)
{
	node_file *file = find_file(file_list, id);
	if (!file)
		return 0;
	word_node *words = file->words;
	while (words) {
		tree *node = find_word_in_tree(root, words->word);
		if (node) {
			remove_file_ref_from_tree_node(node, file);
			if (node->nr_files == 0)
				remove_word_from_tree(root, words->word);
		}
		words = words->next;
	}
	remove_file_from_list(file_list, file);
	free_file(file);
	return 1;
}

int add_kw(list_file *file_list, tree *root, char *id, char *word)
{
	node_file *file = find_file(file_list, id);
	if (!file)
		return 0;
	if (file_has_word(file, word))
		return 1;
	add_word_to_file(file, word);
	tree *node = insert_word_in_tree(root, word);
	add_file_ref_to_tree_node(node, file);
	return 1;
}

int del_kw(list_file *file_list, tree *root, char *id, char *word)
{
	node_file *file = find_file(file_list, id);
	if (!file)
		return 0;
	if (!file_has_word(file, word))
		return 1;
	tree *node = find_word_in_tree(root, word);
	if (node) {
		remove_file_ref_from_tree_node(node, file);
		if (node->nr_files == 0)
			remove_word_from_tree(root, word);
	}
	remove_word_from_file(file, word);
	if (!file->words) {
		remove_file_from_list(file_list, file);
		free_file(file);
	}
	return 1;
}

void find_c(tree *root, char *word, FILE *out)
{
	tree *node = find_word_in_tree(root, word);
	if (!node || node->nr_files == 0) {
		fprintf(out, "EMPTY\n");
		return;
	}
	node_file **files =
	    (node_file **)malloc(sizeof(node_file *) * node->nr_files);
	ref_file_list *ref_list = node->ref_list;
	int index = 0;
	while (ref_list) {
		files[index++] = ref_list->file;
		ref_list = ref_list->next;
	}
	for (int i = 0; i < index - 1; i++) {
		for (int j = i + 1; j < index; j++) {
			if (strcmp(files[i]->id, files[j]->id) > 0) {
				node_file *aux = files[i];
				files[i] = files[j];
				files[j] = aux;
			}
		}
	}
	fprintf(out, "%d", index);
	for (int i = 0; i < index; i++) {
		fprintf(out, " %s", files[i]->id);
	}
	fprintf(out, "\n");
	free(files);
}

void top_k(tree *root, char *word, int k, FILE *out)
{
	tree *node = find_word_in_tree(root, word);
	if (!node || node->nr_files == 0) {
		fprintf(out, "EMPTY\n");
		return;
	}
	heap *h = create_heap(node->nr_files);
	ref_file_list *ref_list = node->ref_list;
	while (ref_list) {
		insert_heap(h, ref_list->file);
		ref_list = ref_list->next;
	}
	int limit = minim(k, node->nr_files);
	fprintf(out, "%d", limit);
	for (int i = 0; i < limit; i++) {
		node_file *file = extract_max(h);
		fprintf(out, " %s", file->id);
	}
	fprintf(out, "\n");
	free_heap(h);
}

void print_tree(tree *root, char *word, int depth, int *printed, FILE *out)
{
	if (root->is_terminal == 1) {
		word[depth] = '\0';
		*printed = 1;
		fprintf(out, "%s %d", word, root->nr_files);
		node_file **files =
		    (node_file **)malloc(sizeof(node_file *) * root->nr_files);
		ref_file_list *ref_list = root->ref_list;
		int index = 0;
		while (ref_list) {
			files[index++] = ref_list->file;
			ref_list = ref_list->next;
		}
		for (int i = 0; i < index - 1; i++) {
			for (int j = i + 1; j < index; j++) {
				if (strcmp(files[i]->id, files[j]->id) > 0) {
					node_file *aux = files[i];
					files[i] = files[j];
					files[j] = aux;
				}
			}
		}
		for (int i = 0; i < index; i++) {
			fprintf(out, " %s", files[i]->id);
		}
		fprintf(out, "\n");
		free(files);
	}
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (root->kids[i]) {
			word[depth] = get_char_by_index(i);
			print_tree(root->kids[i], word, depth + 1, printed,
				   out);
		}
	}
}

void print_c(tree *root, FILE *out)
{
	char *word = malloc(sizeof(char) * MAX_WORD_LEN);
	int printed = 0;
	print_tree(root, word, 0, &printed, out);
	if (printed == 0)
		fprintf(out, "EMPTY\n");
	free(word);
}

int file_already_collected(node_file **files, node_file *file, int count)
{
	for (int i = 0; i < count; i++) {
		if (strcmp(files[i]->id, file->id) == 0)
			return 1;
	}
	return 0;
}

void add_collected_file(node_file ***files, node_file *file, int *count,
			int *capacity)
{
	if (file_already_collected(*files, file, *count) == 1)
		return;
	if (*count == *capacity) {
		*capacity *= 2;
		*files = realloc(*files, sizeof(node_file *) * (*capacity));
	}
	(*files)[*count] = file;
	(*count)++;
}

void collect_prefix_files(tree *node, node_file ***files, int *count,
			  int *capacity)
{
	if (!node)
		return;
	if (node->is_terminal == 1) {
		ref_file_list *ref_list = node->ref_list;
		while (ref_list) {
			add_collected_file(files, ref_list->file, count,
					   capacity);
			ref_list = ref_list->next;
		}
	}
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (node->kids[i])
			collect_prefix_files(node->kids[i], files, count,
					     capacity);
	}
}

void prefix(tree *root, char *prefix, FILE *out)
{
	tree *node = find_prefix_in_tree(root, prefix);
	if (!node) {
		fprintf(out, "EMPTY\n");
		return;
	}
	int count = 0, capacity = 1;
	node_file **files =
	    (node_file **)malloc(sizeof(node_file *) * capacity);
	collect_prefix_files(node, &files, &count, &capacity);
	if (count == 0)
		fprintf(out, "EMPTY\n");
	else {
		for (int i = 0; i < count - 1; i++) {
			for (int j = i + 1; j < count; j++) {
				if (strcmp(files[i]->id, files[j]->id) > 0) {
					node_file *aux = files[i];
					files[i] = files[j];
					files[j] = aux;
				}
			}
		}
		fprintf(out, "%d", count);
		for (int i = 0; i < count; i++) {
			fprintf(out, " %s", files[i]->id);
		}
		fprintf(out, "\n");
	}
	free(files);
}
