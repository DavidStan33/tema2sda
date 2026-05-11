#include <stdlib.h>
#include <string.h>
#include "tree.h"

Tree *createTreeNode(char letter) {
	Tree *node = (Tree *) malloc(sizeof(Tree));
	if(node == NULL)
		return NULL;
	node->is_terminal = 0;
	node->nr_files = 0;
	node->ref_list = NULL;
	node->letter = letter;
	for(int i = 0; i < ALPHABET_SIZE; i++) {
		node->kids[i] = NULL;
	}
	return node;
}

int getCharIndex(char c) {
	return c - 'a';
}

Tree *insertWordInTree(Tree *tree, char *word) {
	int len = strlen(word);
	Tree *curr = tree;
	for(int i = 0; i < len; i++) {
		int index = getCharIndex(word[i]);
		if(curr->kids[index] == NULL) {
			curr->kids[index] = createTreeNode(word[i]);
		}
		curr = curr->kids[index];
	}
	curr->is_terminal = 1;
	return curr;
}
