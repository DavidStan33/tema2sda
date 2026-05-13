// Stan David-Gabriel 313CD

#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdio.h>
#include "files.h"
#include "tree.h"

int add(list_file *file_list, node_file *file, tree *root);

int del(struct list_file *file_list, char *id, struct tree *root);

int add_kw(struct list_file *file_list, struct tree *root, char *id,
	   char *word);

int del_kw(struct list_file *file_list, struct tree *root, char *id,
	   char *word);

void find_c(struct tree *root, char *word, FILE *out);

void top_k(struct tree *root, char *word, int k, FILE *out);

void print_c(struct tree *root, FILE *out);

void prefix(struct tree *root, char *prefix, FILE *out);

#endif
