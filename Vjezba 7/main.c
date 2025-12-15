#include <stdio.h>
#include <stdlib.h>
#include "directory.h"

int main() {
    int choice;
    char name[NAME_LEN];

    Directory *root = createDirectory("C:", NULL);
    Directory *current = root;

    do {
        printf("\n");
        printf("Trenutni direktorij: ");
        printPath(current);
        printf("\n");
        printf("1 - md\n");
        printf("2 - cd dir\n");
        printf("3 - cd..\n");
        printf("4 - dir\n");
        printf("5 - izlaz\n");
        printf("Odabir: ");

        if (scanf("%d", &choice) != 1) {
            printf("Molim vas unesite broj (1-5).\n");

            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}

            continue; //Vrati se na meni
        }

        switch (choice) {
        case 1:
            printf("Ime novog direktorija: ");
            scanf("%49s", name); 
            addChildDirectory(current, name);
            break;

        case 2:
            printf("Unesite ime poddirektorija: ");
            scanf("%49s", name); 
            {
                Directory *next = findChild(current, name);
                if (next) current = next;
                else printf("Ne postoji '%s'.\n", name);
            }
            break;

        case 3:
            if (current->parent)
                current = current->parent;
            else
                printf("Vec ste u root direktoriju.\n");
            break;

        case 4:
            printDir(current);
            break;

        case 5:
            printf("Izlaz...\n");
            break;

        default:
            printf("Nepostojeca opcija!\n");
        }

    } while (choice != 5);

    freeTree(root);
    return 0;
}
