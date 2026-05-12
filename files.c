#include <stdlib.h>
#include <string.h>
#include "files.h"

NodeFile *createFileNode(char *id, int score, WordNode *words)
{
	NodeFile *node = (NodeFile *)malloc(sizeof(NodeFile));
	if (node == NULL)
		return NULL;
	node->id = id;
	node->score = score;
	node->words = words;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

WordNode *createWordNode(char *word) {
	WordNode *node = (WordNode *)malloc(sizeof(WordNode));
	if (node == NULL)
		return NULL;
	strcpy(node->word, word);
	node->next = NULL;
	return node;
}

ListFile *initList() {
	ListFile *list = (ListFile *) malloc(sizeof(ListFile));
	if(list == NULL)
		return NULL;
	list->head = NULL;
	list->tail = NULL;
	return list;
}

int isListEmpty(ListFile *list) {
	if(list == NULL)
		return 1;
	if(list->head == NULL)
		return 1;
	return 0;
}

int isWordListEmpty(WordNode *word) {
	if(word == NULL)
		return 1;
	return 0;
}

NodeFile *findFile(ListFile *list, char *id) {
	NodeFile *curr = list->head;
	while(curr != NULL) {
		if(strcmp(curr->id, id) == 0)
			return curr;
		curr = curr->next;
	}
	return NULL;
}

WordNode *fileHasWord(NodeFile *file, char *word) {
	WordNode *fileWords = file->words;
	while(fileWords != NULL) {
		if(strcmp(fileWords->word, word) == 0)
			return fileWords;
		fileWords = fileWords->next;
	}
	return NULL;

}

void insertFileAtTail(ListFile *list, NodeFile *node) {
	if(isListEmpty(list)) {
		list->head = node;
		list->tail = node;
		node->prev = NULL;
		node->next = NULL;
	} else {
		node->prev = list->tail;
		node->next = NULL;
		list->tail->next = node;
		list->tail = node;
	}
}

void addWordToFile(NodeFile *file, char *word) {
	if(fileHasWord(file, word) != NULL)
		return;
	if(isWordListEmpty(file->words)) {
		file->words = createWordNode(word);
		return;
	}
	WordNode *words = file->words;
	while(words->next != NULL) {
		words = words->next;
	}
	words->next = createWordNode(word);
}

void removeFileFromList(ListFile *list, NodeFile *file) {
	if(isListEmpty(list)) return;
	if(file->prev != NULL)
		file->prev->next = file->next;
	else 
		list->head = file->next;
	if(file->next != NULL)
		file->next->prev = file->prev;
	else
		list->tail = file->prev;

	file->prev = NULL;
	file->next = NULL;
}

void removeWordFromFile(NodeFile *file, char *word) {
	if(!fileHasWord(file, word))
		return;
	WordNode *prev = NULL;
	WordNode *curr = file->words;
	while(curr != NULL) {
		if(strcmp(curr->word, word) == 0) {
			if(prev == NULL)
				file->words = curr->next;
			else
				prev->next = curr->next;

			free(curr);
			return;
		}
		prev = curr;
		curr = curr->next;
	}
}

void freeWords(WordNode *words) {
	while(words != NULL) {
		WordNode *curr = words;
		words = words->next;
		free(curr);
	}
}

void freeFile(NodeFile *file) {
	if(file == NULL)
		return;
	free(file->id);
	freeWords(file->words);
	free(file);
}

void freeListFile(ListFile *list) {
	if(list == NULL)
		return;
	NodeFile *head = list->head;
	while(head != NULL) {
		NodeFile *curr = head;
		head = head->next;
		freeFile(curr);
	}
	free(list);
}
