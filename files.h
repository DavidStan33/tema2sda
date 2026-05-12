#ifndef FILES_H
#define FILES_H

#define MAX_WORD_LEN 101

typedef struct WordNode {
	char word[MAX_WORD_LEN];
	struct WordNode* next;
} WordNode;

typedef struct NodeFile {
	char *id;
	int score;
	WordNode* words;
	struct NodeFile* next;
	struct NodeFile* prev;
} NodeFile;

typedef struct ListFile {
	NodeFile* head;
	NodeFile* tail;
} ListFile;

NodeFile *createFileNode(char *id, int score, WordNode *words);

WordNode *createWordNode(char *word);

ListFile *initList();

NodeFile *findFile(ListFile *list, char *id);

int isListEmpty(ListFile *list);

void insertFileAtTail(ListFile *list, NodeFile *node);

WordNode *fileHasWord(NodeFile *file, char *word);

void addWordToFile(NodeFile *file, char *word);

int isWordListEmpty(WordNode *word);

void removeFileFromList(ListFile *list, NodeFile *file);

void removeWordFromFile(NodeFile *file, char *word);

void freeWords(WordNode *words);

void freeFile(NodeFile *file);

void freeListFile(ListFile *list);

#endif
