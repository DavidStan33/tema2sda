#include <stdio.h>
#include <string.h>
#include "list.h"
#include "commands.h"
#include "tree.h"

#define MAX_COMMAND_LENGTH 10

int main()
{
	FILE *in = fopen("indexare.in", "r");
	FILE *out = fopen("indexare.out", "wt");

	ListFile *fileList = initList();
	Tree *tree = createTreeNode('\0');
	int nr_commands;
	fscanf(in, "%d", &nr_commands);
	char command[MAX_COMMAND_LENGTH];
	for (int i = 0; i < nr_commands; i++)
	{
		fscanf(in, "%s", command);
		if (strcmp(command, "ADD") == 0)
		{
			char *id = readID(in);
			int score, nr_words;
			fscanf(in, "%d%d", &score, &nr_words);
			NodeFile *fileNode = createFileNode(id, score, NULL);
			for (int j = 0; j < nr_words; j++)
			{
				char word[MAX_WORD_LEN];
				fscanf(in, "%s", word);
				addWordToFile(fileNode, word);
			}
			int result = add(fileList, fileNode, tree);
			if (result == 0)
				fprintf(out, "EXISTS\n");
			else
			{
				fprintf(out, "OK\n");
			}
		}
		else if (strcmp(command, "DEL") == 0)
		{
			char *id = readID(in);
			int result = del(fileList, id, tree);
			if (result == 0)
				fprintf(out, "NOT FOUND\n");
			else
			{
				fprintf(out, "OK\n");
			}
		}
	}
	fclose(in);
	fclose(out);
	return 0;
}
