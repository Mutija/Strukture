#ifndef DIRECTORY_H
#define DIRECTORY_H

#define NAME_LEN 50

typedef struct Directory {
    char name[NAME_LEN];
    struct Directory *child;
    struct Directory *sibling;
    struct Directory *parent;
} Directory;


Directory* createDirectory(const char *name, Directory *parent);
void addChildDirectory(Directory *current, const char *name);
Directory* findChild(Directory *current, const char *name);
void printDir(Directory *current);
void printPath(Directory *current);
void freeTree(Directory *root);

#endif
