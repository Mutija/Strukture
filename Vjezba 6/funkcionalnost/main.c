#include <stdio.h>
#include "../header/racun.h"

int main()
{
    Bill *head = loadAllBills("racuni.txt");

    if (head == NULL)
    {
        printf("Nema ucitanih racuna.\n");
        return 0;
    }

    int choice = 0;

    do
    {
        printf("1. Ispis svih racuna\n");
        printf("2. Upit - potrosnja po artiklu\n");
        printf("3. Statistika\n");
        printf("4. Izlaz\n");
        printf("Odabir: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printAllBills(head);
                break;

            case 2:
                queryProduct(head);
                break;

            case 3:
                showStatistics(head);
                break;

            case 4:
                printf("Izlaz iz programa...\n");
                break;

            default:
                printf("Neispravan odabir! Pokusajte ponovno.\n");
        }

    } while (choice != 4);

    clear(head);
    return 0;
}
