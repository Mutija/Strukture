#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bst.h"

static void menu() {
    printf("\n==============================\n");
    printf("   IZBORNIK – BINARNO STABLO\n");
    printf("==============================\n");
    printf(" 1) Unos novog elementa (BST)\n");
    printf(" 2) Pronalaženje elementa\n");
    printf(" 3) Brisanje elementa\n");
    printf("\n--- ISPISI STABLA ---\n");
    printf(" 4) Ispis inorder\n");
    printf(" 5) Ispis preorder\n");
    printf(" 6) Ispis postorder\n");
    printf(" 7) Ispis po razinama (level-order)\n");
    printf("\n--- 9. ZADATAK ---\n");
    printf(" 8) Stvori stablo iz zadanog niza (Slika 1)\n");
    printf(" 9) Zamijeni vrijednosti (suma potomaka – Slika 2)\n");
    printf("10) Slucajni brojevi + upis u datoteku\n");
    printf("\n11) Obrisi cijelo stablo\n");
    printf(" 0) Izlaz\n");
    printf("==============================\n");
}


static void build_task9_fixed(Node** proot) {
    int arr[] = {2,5,7,8,11,1,4,2,3,7};
    int n = (int)(sizeof(arr)/sizeof(arr[0]));

    bst_free(*proot);
    *proot = NULL;

    for (int i = 0; i < n; i++)
        *proot = bst_insert9(*proot, arr[i]);

    printf("Stablo (Slika 1) napravljeno.\n");
}

static void task9c_random(Node** proot) {
    int n;
    printf("Koliko brojeva generirati? ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Neispravan unos.\n");
        return;
    }

    bst_free(*proot);
    *proot = NULL;

    srand((unsigned)time(NULL));

    for (int i = 0; i < n; i++) {
        int x = 10 + rand() % 80;  
        *proot = bst_insert9(*proot, x); 
    }

    FILE* fa = fopen("inorder_a.txt", "w");
    if (!fa) { perror("fopen inorder_a.txt"); return; }
    bst_inorder_to_file(*proot, fa);
    fclose(fa);
    printf("Upisano: inorder_a.txt (nakon a)\n");

    bst_replace_sum_desc(*proot);

    FILE* fb = fopen("inorder_b.txt", "w");
    if (!fb) { perror("fopen inorder_b.txt"); return; }
    bst_inorder_to_file(*proot, fb);
    fclose(fb);
    printf("Upisano: inorder_b.txt (nakon b)\n");
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
        else if (choice == 8) {
            build_task9_fixed(&root);
            printf("Level-order: ");
            bst_levelorder(root);
            printf("\n");
        }
        else if (choice == 9) {
            bst_replace_sum_desc(root);
            printf("Replace odraden.\n");
            printf("Level-order: ");
            bst_levelorder(root);
            printf("\n");
        }
        else if (choice == 10) {
            task9c_random(&root);
        }
        else if (choice == 11) {
            bst_free(root);
            root = NULL;
            printf("Stablo ocisceno.\n");
        }

    } while (choice != 0);

    bst_free(root);
    return 0;
}
