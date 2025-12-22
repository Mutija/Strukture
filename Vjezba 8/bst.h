#ifndef BST_H
#define BST_H

#include <stdio.h>

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;

/*8. zadatak*/
Node* bst_insert(Node* root, int x);
Node* bst_find(Node* root, int x);
Node* bst_delete(Node* root, int x);

/*9. zadatak*/
Node* bst_insert9(Node* root, int x);


void bst_inorder(Node* root);
void bst_preorder(Node* root);
void bst_postorder(Node* root);
void bst_levelorder(Node* root);

void bst_inorder_to_file(Node* root, FILE* f);

void bst_replace_sum_desc(Node* root);

void bst_free(Node* root);

#endif
