#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

char *readID(FILE *in)
{
	char *id = (char *)malloc(sizeof(char) + 1);
	if (id == NULL)
		return NULL;
	int c;
	int len = 0, size = 2;
	while ((c = fgetc(in)) == ' ' || c == '\n')
		continue;
	if (c == EOF)
	{
		free(id);
		return NULL;
	}
	id[len] = c;
	len++;
	while ((c = fgetc(in)) != ' ' && c != '\n' && c != EOF)
	{
		if (len + 1 >= size)
		{
			size *= 2;
			char *tmp = realloc(id, sizeof(char) * size);
			if (tmp == NULL)
			{
				free(id);
				return NULL;
			}
			id = tmp;
		}
		id[len] = c;
		len++;
	}
	id[len] = '\0';
	char *tmp = realloc(id, sizeof(char) * (len + 1));
	if (tmp == NULL)
	{
		free(id);
		return NULL;
	}
	id = tmp;
	return id;
}

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
