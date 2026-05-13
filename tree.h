// Stan David-Gabriel 313CD

#ifndef TREE_H
#define TREE_H

#include "files.h"

#define ALPHABET_SIZE 26

typedef struct ref_file_list {
	node_file *file;
	struct ref_file_list *next;
} ref_file_list;

typedef struct tree {
	char letter;
	int is_terminal;
	int nr_files;
	ref_file_list *ref_list;
	struct tree *kids[ALPHABET_SIZE];
} tree;

tree *create_tree_node(char letter);

tree *insert_word_in_tree(tree *tree, char *word);

int get_char_by_index(int i);

void add_file_ref_to_tree_node(tree *node, node_file *file);

tree *find_word_in_tree(tree *tree, char *word);

tree *find_prefix_in_tree(tree *tree, char *prefix);

void remove_file_ref_from_tree_node(tree *node, node_file *file);

void remove_word_from_tree(tree *root, char *word);

void free_tree(tree *root);

#endif
