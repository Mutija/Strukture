#include <stdio.h>
#include "bst.h"

static void menu(void) {
    printf("\n--- BST ---\n");
    printf("1) Insert\n");
    printf("2) Find\n");
    printf("3) Delete\n");
    printf("4) Print inorder\n");
    printf("5) Print preorder\n");
    printf("6) Print postorder\n");
    printf("7) Print level-order\n");
    printf("0) Exit\n");
}

int main() {
    Node* root = NULL;
    int choice;

    do {
        menu();
        printf("Odabir: ");
        if (scanf("%d", &choice) != 1) break;

        if (choice == 1) {
            int x;
            printf("Unesi broj: ");
            scanf("%d", &x);
            root = bst_insert(root, x);
        }
        else if (choice == 2) {
            int x;
            printf("Trazi broj: ");
            scanf("%d", &x);
            printf(bst_find(root, x) ? "Pronaden.\n" : "Nije pronaden.\n");
        }
        else if (choice == 3) {
            int x;
            printf("Brisi broj: ");
            scanf("%d", &x);
            root = bst_delete(root, x);
        }
        else if (choice == 4) {
            printf("Inorder: ");
            bst_inorder(root);
            printf("\n");
        }
        else if (choice == 5) {
            printf("Preorder: ");
            bst_preorder(root);
            printf("\n");
        }
        else if (choice == 6) {
            printf("Postorder: ");
            bst_postorder(root);
            printf("\n");
        }
        else if (choice == 7) {
            printf("Level-order: ");
            bst_levelorder(root);
            printf("\n");
        }

    } while (choice != 0);

    bst_free(root);
    return 0;
}
