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

static RefFileList *createRefFileNode(NodeFile *file) {
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

static int getCharIndex(char c) {
	return c - 'a';
}

int getCharByIndex(int i) {
	return 'a' + i;
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

int hasChildren(Tree *node) {
	for(int i = 0; i < ALPHABET_SIZE; i++) {
		if(node->kids[i] != NULL)
			return 1;
	}
	return 0;
}

int removeWordFromTreeHelper(Tree *root, char *word, size_t depth) {
	if(root == NULL)
		return 0;
	if(depth == strlen(word)) {
		root->is_terminal = 0;
		return depth > 0 && !hasChildren(root);
	}
	else {
		int index = getCharIndex(word[depth]);
		if(removeWordFromTreeHelper(root->kids[index], word, depth + 1)) {
			free(root->kids[index]);
			root->kids[index] = NULL;
		}
		return depth > 0 && root->is_terminal == 0 && !hasChildren(root);
	}
}

void removeWordFromTree(Tree *root, char *word) {
	removeWordFromTreeHelper(root, word, 0);
}

void freeRefFileList(RefFileList *refList) {
	while(refList != NULL) {
		RefFileList *curr = refList;
		refList = refList->next;
		free(curr);
	}
}

void freeTree(Tree *root) {
	if(root == NULL)
		return;
	for(int i = 0; i < ALPHABET_SIZE; i++) {
		freeTree(root->kids[i]);
	}
	freeRefFileList(root->ref_list);
	free(root);
}
