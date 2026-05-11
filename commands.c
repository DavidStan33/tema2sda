#include <stdlib.h>
#include "list.h"
#include "tree.h"

int add(ListFile *fileList, NodeFile *file, Tree *root) {
	if(findFile(fileList, file->id) != NULL)
		return 0;
	insertFileAtTail(fileList, file);
	WordNode *words = file->words;
	while(words != NULL) {
		Tree *terminalNode = insertWordInTree(root, words->word);
		addFileRefToTreeNode(terminalNode, file);
		words = words->next;
	}
	return 1;
}

int del(ListFile *fileList, char *id, Tree *root) {
	NodeFile *file = findFile(fileList, id);
	if(file == NULL)
		return 0;
	WordNode *words = file->words;
	while(words != NULL) {
		Tree *node = findWordInTree(root, words->word);
		if(node != NULL)
			removeFileRefFromTreeNode(node, file);
		words = words->next;
	}
	removeFileFromList(fileList, file);
	return 1;
}
