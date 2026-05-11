#ifndef LIST_H
#define LIST_H

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

typedef struct RefFileList {
	NodeFile* file;
	struct RefFileList* next;
} RefFileList;

typedef struct ListFile {
	NodeFile* head;
	NodeFile* tail;
} ListFile;

char *readID(FILE *in);

NodeFile *createFileNode(char *id, int score, WordNode *words);

ListFile *initList();

NodeFile *findFile(ListFile *list, char *id);

int isListEmpty(ListFile *list);

ListFile *insertFileAtTail(ListFile *list, NodeFile *node);

WordNode *createWordNode(char *word);

WordNode *fileHasWord(NodeFile *file, char *word);

void addWordToFile(NodeFile *file, char *word);

int isWordListEmpty(WordNode *word);

#endif
