#ifndef TREE_H
#define TREE_H

#include "files.h"

#define ALPHABET_SIZE 26

typedef struct RefFileList {
	NodeFile* file;
	struct RefFileList* next;
} RefFileList;

typedef struct Tree {
	char letter;
	int is_terminal;
	int nr_files;
	RefFileList *ref_list;
	struct Tree *kids[ALPHABET_SIZE];
} Tree;

Tree *createTreeNode(char letter);

Tree *insertWordInTree(Tree *tree, char *word);

int getCharByIndex(int i);

void addFileRefToTreeNode(Tree *node, NodeFile *file);

Tree *findWordInTree(Tree *tree, char *word);

void removeFileRefFromTreeNode(Tree *node, NodeFile *file);

void removeWordFromTree(Tree *root, char *word);

void freeTree(Tree *root);

#endif
