// Stan David-Gabriel 313CD

#include <stdlib.h>
#include <string.h>
#include "files.h"

node_file *create_file_node(char *id, int score, word_node *words)
{
	node_file *node = (node_file *)malloc(sizeof(node_file));
	if (!node)
		return NULL;
	node->id = id;
	node->score = score;
	node->words = words;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

word_node *create_word_node(char *word)
{
	word_node *node = (word_node *)malloc(sizeof(word_node));
	if (!node)
		return NULL;
	strcpy(node->word, word);
	node->next = NULL;
	return node;
}

list_file *init_list(void)
{
	list_file *list = (list_file *)malloc(sizeof(list_file));
	if (!list)
		return NULL;
	list->head = NULL;
	list->tail = NULL;
	return list;
}

int is_list_empty(list_file *list)
{
	if (!list)
		return 1;
	if (!list->head)
		return 1;
	return 0;
}

int is_word_list_empty(word_node *word)
{
	if (!word)
		return 1;
	return 0;
}

node_file *find_file(list_file *list, char *id)
{
	node_file *curr = list->head;
	while (curr) {
		if (strcmp(curr->id, id) == 0)
			return curr;
		curr = curr->next;
	}
	return NULL;
}

word_node *file_has_word(node_file *file, char *word)
{
	word_node *file_words = file->words;
	while (file_words) {
		if (strcmp(file_words->word, word) == 0)
			return file_words;
		file_words = file_words->next;
	}
	return NULL;
}

void insert_file_at_tail(list_file *list, node_file *node)
{
	if (is_list_empty(list)) {
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

void add_word_to_file(node_file *file, char *word)
{
	if (file_has_word(file, word))
		return;
	if (is_word_list_empty(file->words)) {
		file->words = create_word_node(word);
		return;
	}
	word_node *words = file->words;
	while (words->next) {
		words = words->next;
	}
	words->next = create_word_node(word);
}

void remove_file_from_list(list_file *list, node_file *file)
{
	if (is_list_empty(list))
		return;
	if (file->prev)
		file->prev->next = file->next;
	else
		list->head = file->next;
	if (file->next)
		file->next->prev = file->prev;
	else
		list->tail = file->prev;

	file->prev = NULL;
	file->next = NULL;
}

void remove_word_from_file(node_file *file, char *word)
{
	if (!file_has_word(file, word))
		return;
	word_node *prev = NULL;
	word_node *curr = file->words;
	while (curr) {
		if (strcmp(curr->word, word) == 0) {
			if (!prev)
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

void free_words(word_node *words)
{
	while (words) {
		word_node *curr = words;
		words = words->next;
		free(curr);
	}
}

void free_file(node_file *file)
{
	if (!file)
		return;
	free(file->id);
	free_words(file->words);
	free(file);
}

void free_list_file(list_file *list)
{
	if (!list)
		return;
	node_file *head = list->head;
	while (head) {
		node_file *curr = head;
		head = head->next;
		free_file(curr);
	}
	free(list);
}
