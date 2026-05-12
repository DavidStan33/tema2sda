#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdio.h>
#include "files.h"
#include "tree.h"

int add(ListFile *fileList, NodeFile *file, Tree *root);

int del(ListFile *fileList, char *id, Tree *root);

int addkw(ListFile *fileList, Tree *root, char *id, char *word);

int delkw(ListFile *fileList, Tree *root, char *id, char *word);

void findC(Tree *root, char *word, FILE *out);

void topk(Tree *root, char *word, int k, FILE *out);

void printC(Tree *root, FILE *out);

#endif
