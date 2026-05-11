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

RefFileList *createRefFileNode(NodeFile *file) {
	RefFileList *node = (RefFileList *) malloc(sizeof(RefFileList));
	node->file = file;
	node->next = NULL;
	return node;
}

void addFileRefToTreeNode(Tree *node, NodeFile *file) {
	RefFileList *newRef = createRefFileNode(file);
	newRef->next = node->ref_list;
	node->ref_list = newRef;
	node->nr_files++;
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

Tree *findWordInTree(Tree *tree, char *word) {
	int len = strlen(word);
	Tree *curr = tree;
	for(int i = 0; i < len; i++) {
		int index = getCharIndex(word[i]);
		if(curr->kids[index] == NULL)
			return NULL;
		curr = curr->kids[index];
	}
	if(curr->is_terminal == 1)
		return curr;
	else
		return NULL;
}

void removeFileRefFromTreeNode(Tree *node, NodeFile *file) {
	RefFileList *prev = NULL;
	RefFileList *curr = node->ref_list;
	while(curr != NULL) {
		if(curr->file == file) {
			if(prev == NULL)
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
