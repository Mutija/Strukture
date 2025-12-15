#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "directory.h"

Directory* createDirectory(const char *name, Directory *parent) {
    Directory *dir = malloc(sizeof(Directory));
    if (!dir) {
        printf("Greska pri alokaciji memorije za direktorij '%s'.\n", name);
        return NULL;
    }

    strncpy(dir->name, name, NAME_LEN - 1);
    dir->name[NAME_LEN - 1] = '\0';

    dir->child = NULL;
    dir->sibling = NULL;
    dir->parent = parent;

    return dir;
}

void addChildDirectory(Directory *current, const char *name) {
    if (!current) return;

    Directory *tmp = current->child;
    while (tmp) {
        if (strcmp(tmp->name, name) == 0) {
            printf("Direktorij '%s' vec postoji.\n", name);
            return;
        }
        tmp = tmp->sibling;
    }

    Directory *newDir = createDirectory(name, current);
    if (!newDir) return;

    newDir->sibling = current->child;
    current->child = newDir;

    printf("Direktorij '%s' je kreiran.\n", name);
}

Directory* findChild(Directory *current, const char *name) {
    Directory *tmp = current->child;
    while (tmp) {
        if (strcmp(tmp->name, name) == 0)
            return tmp;
        tmp = tmp->sibling;
    }
    return NULL;
}

void printDir(Directory *current) {
    printf("Sadrzaj direktorija ");
    printPath(current);
    printf(":\n");

    if (!current->child) {
        printf("  (prazno)\n");
        return;
    }

    Directory *tmp = current->child;
    while (tmp) {
        printf("  <DIR> %s\n", tmp->name);
        tmp = tmp->sibling;
    }
}

void printPath(Directory *current) {
    if (!current) return;

    if (current->parent) {
        printPath(current->parent);
        printf("\\%s", current->name);
    } else {
        printf("%s", current->name);
    }
}

void freeTree(Directory *root) {
    if (!root) return;
    freeTree(root->child);
    freeTree(root->sibling);
    free(root);
}
