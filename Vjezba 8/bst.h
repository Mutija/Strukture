#ifndef BST_H
#define BST_H

#include <stdio.h>

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;

Node* bst_insert(Node* root, int x);
Node* bst_find(Node* root, int x);
Node* bst_delete(Node* root, int x);
void  bst_free(Node* root);

void bst_inorder(Node* root);
void bst_preorder(Node* root);
void bst_postorder(Node* root);
void bst_levelorder(Node* root);

#endif
