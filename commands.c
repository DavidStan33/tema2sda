#include <stdlib.h>
#include <string.h>
#include "commands.h"
#include "heap.h"
#include "utils.h"

int add(ListFile *fileList, NodeFile *file, Tree *root)
{
	if (findFile(fileList, file->id) != NULL)
	{
		freeFile(file);
		return 0;
	}
	insertFileAtTail(fileList, file);
	WordNode *words = file->words;
	while (words != NULL)
	{
		Tree *terminalNode = insertWordInTree(root, words->word);
		addFileRefToTreeNode(terminalNode, file);
		words = words->next;
	}
	return 1;
}

int del(ListFile *fileList, char *id, Tree *root)
{
	NodeFile *file = findFile(fileList, id);
	if (file == NULL)
		return 0;
	WordNode *words = file->words;
	while (words != NULL)
	{
		Tree *node = findWordInTree(root, words->word);
		if (node != NULL)
		{
			removeFileRefFromTreeNode(node, file);
			if (node->nr_files == 0)
				removeWordFromTree(root, words->word);
		}
		words = words->next;
	}
	removeFileFromList(fileList, file);
	freeFile(file);
	return 1;
}

int addkw(ListFile *fileList, Tree *root, char *id, char *word)
{
	NodeFile *file = findFile(fileList, id);
	if (file == NULL)
		return 0;
	if (fileHasWord(file, word))
		return 1;
	addWordToFile(file, word);
	Tree *node = insertWordInTree(root, word);
	addFileRefToTreeNode(node, file);
	return 1;
}

int delkw(ListFile *fileList, Tree *root, char *id, char *word)
{
	NodeFile *file = findFile(fileList, id);
	if (file == NULL)
		return 0;
	if (!fileHasWord(file, word))
		return 1;
	Tree *node = findWordInTree(root, word);
	if (node != NULL)
	{
		removeFileRefFromTreeNode(node, file);
		if (node->nr_files == 0)
			removeWordFromTree(root, word);
	}
	removeWordFromFile(file, word);
	if (file->words == NULL) {
		removeFileFromList(fileList, file);
		freeFile(file);
	}
	return 1;
}

void findC(Tree *root, char *word, FILE *out)
{
	Tree *node = findWordInTree(root, word);
	if (node == NULL || node->nr_files == 0)
	{
		fprintf(out, "EMPTY\n");
		return;
	}
	NodeFile **files = (NodeFile **)malloc(sizeof(NodeFile *) * node->nr_files);
	RefFileList *refList = node->ref_list;
	int index = 0;
	while (refList != NULL)
	{
		files[index++] = refList->file;
		refList = refList->next;
	}
	for (int i = 0; i < index - 1; i++)
	{
		for (int j = i + 1; j < index; j++)
		{
			if (strcmp(files[i]->id, files[j]->id) > 0)
			{
				NodeFile *aux = files[i];
				files[i] = files[j];
				files[j] = aux;
			}
		}
	}
	fprintf(out, "%d", index);
	for (int i = 0; i < index; i++)
	{
		fprintf(out, " %s", files[i]->id);
	}
	fprintf(out, "\n");
	free(files);
}

void topk(Tree *root, char *word, int k, FILE *out)
{
	Tree *node = findWordInTree(root, word);
	if (node == NULL || node->nr_files == 0)
	{
		fprintf(out, "EMPTY\n");
		return;
	}
	Heap *heap = createHeap(node->nr_files);
	RefFileList *refList = node->ref_list;
	while (refList != NULL)
	{
		insertHeap(heap, refList->file);
		refList = refList->next;
	}
	int limit = minim(k, node->nr_files);
	fprintf(out, "%d", limit);
	for (int i = 0; i < limit; i++)
	{
		NodeFile *file = extractMax(heap);
		fprintf(out, " %s", file->id);
	}
	fprintf(out, "\n");
	freeHeap(heap);
}

void printTree(Tree *root, char *word, int depth, int *printed, FILE *out)
{
	if (root->is_terminal == 1)
	{
		word[depth] = '\0';
		*printed = 1;
		fprintf(out, "%s %d", word, root->nr_files);
		NodeFile **files = (NodeFile **)malloc(sizeof(NodeFile *) * root->nr_files);
		RefFileList *refList = root->ref_list;
		int index = 0;
		while (refList != NULL)
		{
			files[index++] = refList->file;
			refList = refList->next;
		}
		for (int i = 0; i < index - 1; i++)
		{
			for (int j = i + 1; j < index; j++)
			{
				if (strcmp(files[i]->id, files[j]->id) > 0)
				{
					NodeFile *aux = files[i];
					files[i] = files[j];
					files[j] = aux;
				}
			}
		}
		for (int i = 0; i < index; i++)
		{
			fprintf(out, " %s", files[i]->id);
		}
		fprintf(out, "\n");
		free(files);
	}
	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		if (root->kids[i] != NULL)
		{
			word[depth] = getCharByIndex(i);
			printTree(root->kids[i], word, depth + 1, printed, out);
		}
	}
}

void printC(Tree *root, FILE *out) {
	char *word = malloc(sizeof(char) * MAX_WORD_LEN);
	int printed = 0;
	printTree(root, word, 0, &printed, out);
	if(printed == 0)
		fprintf(out, "EMPTY\n");
	free(word);
}
