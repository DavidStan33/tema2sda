#include <stdio.h>
#include <stdlib.h>
#include "read.h"

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
