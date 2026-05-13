// Stan David-Gabriel 313CD

#include <stdlib.h>
#include <string.h>
#include "tree.h"

tree *create_tree_node(char letter)
{
	tree *node = (tree *)malloc(sizeof(tree));
	if (!node)
		return NULL;
	node->is_terminal = 0;
	node->nr_files = 0;
	node->ref_list = NULL;
	node->letter = letter;
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		node->kids[i] = NULL;
	}
	return node;
}

ref_file_list *create_ref_file_node(node_file *file)
{
	ref_file_list *node = (ref_file_list *)malloc(sizeof(ref_file_list));
	node->file = file;
	node->next = NULL;
	return node;
}

void add_file_ref_to_tree_node(tree *node, node_file *file)
{
	ref_file_list *new_ref = create_ref_file_node(file);
	new_ref->next = node->ref_list;
	node->ref_list = new_ref;
	node->nr_files++;
}

int get_char_index(char c)
{
	return c - 'a';
}

int get_char_by_index(int i)
{
	return 'a' + i;
}

tree *insert_word_in_tree(tree *root, char *word)
{
	int len = strlen(word);
	tree *curr = root;
	for (int i = 0; i < len; i++) {
		int index = get_char_index(word[i]);
		if (!curr->kids[index]) {
			curr->kids[index] = create_tree_node(word[i]);
		}
		curr = curr->kids[index];
	}
	curr->is_terminal = 1;
	return curr;
}

tree *find_word_in_tree(tree *root, char *word)
{
	int len = strlen(word);
	tree *curr = root;
	for (int i = 0; i < len; i++) {
		int index = get_char_index(word[i]);
		if (!curr->kids[index])
			return NULL;
		curr = curr->kids[index];
	}
	if (curr->is_terminal == 1)
		return curr;
	else
		return NULL;
}

tree *find_prefix_in_tree(tree *root, char *prefix)
{
	int len = strlen(prefix);
	tree *curr = root;
	for (int i = 0; i < len; i++) {
		int index = get_char_index(prefix[i]);
		if (!curr->kids[index])
			return NULL;
		curr = curr->kids[index];
	}
	return curr;
}

void remove_file_ref_from_tree_node(tree *node, node_file *file)
{
	ref_file_list *prev = NULL;
	ref_file_list *curr = node->ref_list;
	while (curr) {
		if (curr->file == file) {
			if (!prev)
				node->ref_list = curr->next;
			else
				prev->next = curr->next;

			free(curr);
			node->nr_files--;
			return;
		}
		prev = curr;
		curr = curr->next;
	}
}

int has_children(tree *node)
{
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (node->kids[i])
			return 1;
	}
	return 0;
}

int remove_word_from_tree_helper(tree *root, char *word, size_t depth)
{
	if (!root)
		return 0;
	if (depth == strlen(word)) {
		root->is_terminal = 0;
		return depth > 0 && !has_children(root);
	}
	int index = get_char_index(word[depth]);
	if (remove_word_from_tree_helper(root->kids[index], word, depth + 1)) {
		free(root->kids[index]);
		root->kids[index] = NULL;
	}
	return depth > 0 && root->is_terminal == 0 && !has_children(root);
}

void remove_word_from_tree(tree *root, char *word)
{
	remove_word_from_tree_helper(root, word, 0);
}

void free_ref_file_list(ref_file_list *ref_list)
{
	while (ref_list) {
		ref_file_list *curr = ref_list;
		ref_list = ref_list->next;
		free(curr);
	}
}

void free_tree(tree *root)
{
	if (!root)
		return;
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		free_tree(root->kids[i]);
	}
	free_ref_file_list(root->ref_list);
	free(root);
}
