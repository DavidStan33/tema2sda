// Stan David-Gabriel 313CD

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "files.h"
#include "read.h"
#include "commands.h"
#include "tree.h"

#define MAX_COMMAND_LENGTH 10

int main(void)
{
	FILE *in = fopen("indexare.in", "r");
	FILE *out = fopen("indexare.out", "wt");

	list_file *file_list = init_list();
	tree *root = create_tree_node('\0');
	int nr_commands;
	fscanf(in, "%d", &nr_commands);
	char command[MAX_COMMAND_LENGTH];
	for (int i = 0; i < nr_commands; i++) {
		fscanf(in, "%s", command);
		if (strcmp(command, "ADD") == 0) {
			char *id = read_id(in);
			int score, nr_words;
			fscanf(in, "%d%d", &score, &nr_words);
			node_file *file_node =
			    create_file_node(id, score, NULL);
			for (int j = 0; j < nr_words; j++) {
				char word[MAX_WORD_LEN];
				fscanf(in, "%s", word);
				add_word_to_file(file_node, word);
			}
			int result = add(file_list, file_node, root);
			if (result == 0)
				fprintf(out, "EXISTS\n");
			else {
				fprintf(out, "OK\n");
			}
		} else if (strcmp(command, "DEL") == 0) {
			char *id = read_id(in);
			int result = del(file_list, id, root);
			if (result == 0)
				fprintf(out, "NOT FOUND\n");
			else {
				fprintf(out, "OK\n");
			}
			free(id);
		} else if (strcmp(command, "ADDKW") == 0) {
			char *id = read_id(in);
			char word[MAX_WORD_LEN];
			fscanf(in, "%s", word);
			int result = add_kw(file_list, root, id, word);
			if (result == 0)
				fprintf(out, "NOT FOUND\n");
			else
				fprintf(out, "OK\n");
			free(id);
		} else if (strcmp(command, "DELKW") == 0) {
			char *id = read_id(in);
			char word[MAX_WORD_LEN];
			fscanf(in, "%s", word);
			int result = del_kw(file_list, root, id, word);
			if (result == 0)
				fprintf(out, "NOT FOUND\n");
			else
				fprintf(out, "OK\n");
			free(id);
		} else if (strcmp(command, "FIND") == 0) {
			char word[MAX_WORD_LEN];
			fscanf(in, "%s", word);
			find_c(root, word, out);
		} else if (strcmp(command, "TOPK") == 0) {
			char word[MAX_WORD_LEN];
			int k;
			fscanf(in, "%s %d", word, &k);
			top_k(root, word, k, out);
		} else if (strcmp(command, "PRINT") == 0) {
			print_c(root, out);
		} else if (strcmp(command, "PREFIX") == 0) {
			char pref[MAX_WORD_LEN];
			fscanf(in, "%s", pref);
			prefix(root, pref, out);
		}
	}
	free_tree(root);
	free_list_file(file_list);
	fclose(in);
	fclose(out);
	return 0;
}
