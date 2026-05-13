// Stan David-Gabriel 313CD

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *read_id(FILE *in)
{
	char *id = (char *)malloc(sizeof(char) + 1);
	if (!id)
		return NULL;
	int c;
	int len = 0, size = 2;
	while ((c = fgetc(in)) != EOF && isspace(c))
		continue;
	if (c == EOF) {
		free(id);
		return NULL;
	}
	id[len] = c;
	len++;
	while ((c = fgetc(in)) != EOF && !isspace(c)) {
		if (len + 1 >= size) {
			size *= 2;
			char *tmp = realloc(id, sizeof(char) * size);
			if (!tmp) {
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
	if (!tmp) {
		free(id);
		return NULL;
	}
	id = tmp;
	return id;
}
