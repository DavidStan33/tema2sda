// Stan David-Gabriel 313CD

#ifndef FILES_H
#define FILES_H

#define MAX_WORD_LEN 101

typedef struct word_node {
	char word[MAX_WORD_LEN];
	struct word_node *next;
} word_node;

typedef struct node_file {
	char *id;
	int score;
	word_node *words;
	struct node_file *next;
	struct node_file *prev;
} node_file;

typedef struct list_file {
	node_file *head;
	node_file *tail;
} list_file;

node_file *create_file_node(char *id, int score, word_node *words);

word_node *create_word_node(char *word);

list_file *init_list(void);

node_file *find_file(list_file *list, char *id);

int is_list_empty(list_file *list);

void insert_file_at_tail(list_file *list, node_file *node);

word_node *file_has_word(node_file *file, char *word);

void add_word_to_file(node_file *file, char *word);

int is_word_list_empty(word_node *word);

void remove_file_from_list(list_file *list, node_file *file);

void remove_word_from_file(node_file *file, char *word);

void free_words(word_node *words);

void free_file(node_file *file);

void free_list_file(list_file *list);

#endif
