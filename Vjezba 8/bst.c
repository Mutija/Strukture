#include "bst.h"
#include <stdlib.h>

static Node* create_node(int x) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (!n) {
        perror("malloc");
        return NULL;
    }
    n->value = x;
    n->left = n->right = NULL;
    return n;
}

Node* bst_insert(Node* root, int x) {
    if (!root) return create_node(x);

    if (x < root->value)
        root->left = bst_insert(root->left, x);
    else if (x > root->value)
        root->right = bst_insert(root->right, x);
    return root;
}

Node* bst_find(Node* root, int x) {
    if (!root) return NULL;
    if (x == root->value) return root;
    if (x < root->value) return bst_find(root->left, x);
    return bst_find(root->right, x);
}

static Node* find_min(Node* root) {
    while (root && root->left) root = root->left;
    return root;
}

Node* bst_delete(Node* root, int x) {
    if (!root) return NULL;

    if (x < root->value) {
        root->left = bst_delete(root->left, x);
    } else if (x > root->value) {
        root->right = bst_delete(root->right, x);
    } else {

        if (!root->left && !root->right) {
            free(root);
            return NULL;
        }
        if (!root->left) {
            Node* r = root->right;
            free(root);
            return r;
        }
        if (!root->right) {
            Node* l = root->left;
            free(root);
            return l;
        }

        Node* succ = find_min(root->right);
        root->value = succ->value;
        root->right = bst_delete(root->right, succ->value);
    }
    return root;
}

void bst_inorder(Node* root) {
    if (!root) return;
    bst_inorder(root->left);
    printf("%d ", root->value);
    bst_inorder(root->right);
}

void bst_preorder(Node* root) {
    if (!root) return;
    printf("%d ", root->value);
    bst_preorder(root->left);
    bst_preorder(root->right);
}

void bst_postorder(Node* root) {
    if (!root) return;
    bst_postorder(root->left);
    bst_postorder(root->right);
    printf("%d ", root->value);
}

typedef struct QNode {
    Node* data;
    struct QNode* next;
} QNode;

typedef struct {
    QNode* front;
    QNode* back;
} Queue;

static void q_init(Queue* q) { 
    q->front = q->back = NULL; 
}

static int q_empty(Queue* q) { 
    return q->front == NULL; 
}

static void q_push(Queue* q, Node* n) {
    QNode* x = (QNode*)malloc(sizeof(QNode));
    if (!x) { perror("malloc"); return; }
    x->data = n;
    x->next = NULL;

    if (!q->back) q->front = q->back = x;
    else { q->back->next = x; q->back = x; }
}

static Node* q_pop(Queue* q) {
    if (q_empty(q)) return NULL;
    QNode* f = q->front;
    Node* ret = f->data;
    q->front = f->next;
    if (!q->front) q->back = NULL;
    free(f);
    return ret;
}

void bst_levelorder(Node* root) {
    if (!root) return;

    Queue q;
    q_init(&q);
    q_push(&q, root);

    while (!q_empty(&q)) {
        Node* cur = q_pop(&q);
        printf("%d ", cur->value);
        if (cur->left)  q_push(&q, cur->left);
        if (cur->right) q_push(&q, cur->right);
    }
}

void bst_free(Node* root) {
    if (!root) return;
    bst_free(root->left);
    bst_free(root->right);
    free(root);
}
