#ifndef TREE_H
#define TREE_H

#include "list.h"

#define ALPHABET_SIZE 26

typedef struct Tree {
	char letter;
	int is_terminal;
	int nr_files;
	RefFileList *ref_list;
	struct Tree *kids[ALPHABET_SIZE];
} Tree;

Tree *createTreeNode(char letter);

Tree *insertWordInTree(Tree *tree, char *word);

int getCharIndex(char c);
#endif
