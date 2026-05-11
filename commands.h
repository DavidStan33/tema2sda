#ifndef COMMANDS_H
#define COMMANDS_H

#include "list.h"
#include "tree.h"

int add(ListFile *fileList, NodeFile *file, Tree *root);

int del(ListFile *fileList, char *id, Tree *root);

#endif
