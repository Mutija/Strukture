#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// STRUKTURA OSOBE U POVEZANOJ LISTI
typedef struct Person {
    char ime[50];
    char prezime[50];
    int godina;
    struct Person* next;
} Person;

// PROTOTIPI FUNKCIJA
Person* addToBeginning(Person* head);
void printList(Person* head);
Person* addToEnd(Person* head);
Person* findBySurname(Person* head, const char* prezime);
Person* deleteBySurname(Person* head, const char* prezime);
void initPerson(Person* p);
void formatName(char* str);
int compareIgnoreCase(const char* a, const char* b);

// Novi prototipi za zadatak 3
Person* addAfterSurname(Person* head, const char* prezime);
Person* addBeforeSurname(Person* head, const char* prezime);
Person* sortList(Person* head);
void writeToFile(Person* head, const char* filename);
Person* readFromFile(const char* filename);
FILE* openFile(const char* filename, const char* mode);

// MAIN FUNKCIJA
int main() {
    Person* head = NULL;
    int izbor;
    char prezime[50];

    do {
        printf("\n----- IZBORNIK -----\n");
        printf("1. Dodaj na pocetak\n");
        printf("2. Ispisi listu\n");
        printf("3. Dodaj na kraj\n");
        printf("4. Pronadi po prezimenu\n");
        printf("5. Obrisi po prezimenu\n");
        printf("6. Dodaj iza prezimena\n");
        printf("7. Dodaj prije prezimena\n");
        printf("8. Sortiraj po prezimenu\n");
        printf("9. Spremi u datoteku\n");
        printf("10. Ucitaj iz datoteke\n");
        printf("0. Izlaz\n");

        printf("Odabir: ");
        scanf("%d", &izbor);

        switch (izbor) {
            case 1:
                head = addToBeginning(head);
                break;
            case 2:
                printList(head);
                break;
            case 3:
                head = addToEnd(head);
                break;
            case 4:
                printf("Unesi prezime: ");
                scanf("%s", prezime);
                {
                    Person* found = findBySurname(head, prezime);
                    if (found)
                        printf("Pronaden: %s %s, %d\n", found->ime, found->prezime, found->godina);
                    else
                        printf("Osoba nije pronadena.\n");
                }
                break;
            case 5:
                printf("Unesi prezime za brisanje: ");
                scanf("%s", prezime);
                head = deleteBySurname(head, prezime);
                break;
            case 6:
                printf("Unesi prezime iza kojeg dodajes: ");
                scanf("%s", prezime);
                head = addAfterSurname(head, prezime);
                break;
            case 7:
                printf("Unesi prezime ispred kojeg dodajes: ");
                scanf("%s", prezime);
                head = addBeforeSurname(head, prezime);
                break;
            case 8:
                head = sortList(head);
                printf("Lista sortirana.\n");
                break;
            case 9:
                writeToFile(head, "osobe.txt");
                break;
            case 10:
                head = readFromFile("osobe.txt");
                printf("Lista ucitana iz datoteke.\n");
                break;
        }
    } while (izbor != 0);

    // Oslobadanje memorije
    Person* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    return 0;
}

// FUNKCIJA: ULAZ KORISNIKA
void initPerson(Person* p) {
    printf("Unesi ime: ");
    scanf("%s", p->ime);
    formatName(p->ime);

    printf("Unesi prezime: ");
    scanf("%s", p->prezime);
    formatName(p->prezime);

    printf("Unesi godinu rodenja: ");
    scanf("%d", &p->godina);
}

// FUNKCIJA: PRVO SLOVO VELIKO, OSTALA MALA
void formatName(char* str) {
    if (str[0] != '\0') {
        str[0] = toupper((unsigned char)str[0]);
        for (int i = 1; str[i]; i++)
            str[i] = tolower((unsigned char)str[i]);
    }
}

// FUNKCIJA: DODAVANJE NA POCETAK
Person* addToBeginning(Person* head) {
    Person* newPerson = (Person*)malloc(sizeof(Person));
    initPerson(newPerson);
    newPerson->next = head;
    return newPerson;
}

// FUNKCIJA: Ispis liste
void printList(Person* head) {
    if (!head) {
        printf("Lista je prazna.\n");
        return;
    }
    Person* current = head;
    while (current) {
        printf("%s %s, %d\n", current->ime, current->prezime, current->godina);
        current = current->next;
    }
}

// FUNKCIJA: Dodavanje na kraj
Person* addToEnd(Person* head) {
    Person* newPerson = (Person*)malloc(sizeof(Person));
    initPerson(newPerson);
    newPerson->next = NULL;

    if (!head)
        return newPerson;

    Person* current = head;
    while (current->next)
        current = current->next;
    current->next = newPerson;
    return head;
}

// Funkcija: Pronadenje osobe po prezimenu (NEOVISNO O VELICINI SLOVA)
int compareIgnoreCase(const char* a, const char* b) {
    while (*a && *b) {
        char ca = tolower((unsigned char)*a);
        char cb = tolower((unsigned char)*b);
        if (ca != cb)
            return ca - cb;
        a++;
        b++;
    }
    return *a - *b;
}

// TRAZENJE PREZIMENA
Person* findBySurname(Person* head, const char* prezime) {
    while (head) {
        if (compareIgnoreCase(head->prezime, prezime) == 0)
            return head;
        head = head->next;
    }
    return NULL;
}

// BRISANJE PREZIMENA
Person* deleteBySurname(Person* head, const char* prezime) {
    Person* current = head;
    Person* previous = NULL;

    while (current && compareIgnoreCase(current->prezime, prezime) != 0) {
        previous = current;
        current = current->next;
    }

    if (!current) {
        printf("Prezime nije pronadeno.\n");
        return head;
    }

    if (!previous)
        head = current->next;
    else
        previous->next = current->next;

    free(current);
    printf("Osoba obrisana.\n");
    return head;
}

// DODAVANJE IZA ODREDENOG PREZIMENA
Person* addAfterSurname(Person* head, const char* prezime) {
    Person* current = head;
    while (current && compareIgnoreCase(current->prezime, prezime) != 0)
        current = current->next;

    if (!current) {
        printf("Prezime nije pronadeno.\n");
        return head;
    }

    Person* newPerson = (Person*)malloc(sizeof(Person));
    initPerson(newPerson);
    newPerson->next = current->next;
    current->next = newPerson;
    return head;
}

// DODAVANJE ISPRED ODREDENOG PREZIMENA
Person* addBeforeSurname(Person* head, const char* prezime) {
    Person* current = head;
    Person* previous = NULL;

    while (current && compareIgnoreCase(current->prezime, prezime) != 0) {
        previous = current;
        current = current->next;
    }

    if (!current) {
        printf("Prezime nije pronadeno.\n");
        return head;
    }

    Person* newPerson = (Person*)malloc(sizeof(Person));
    initPerson(newPerson);

    if (!previous) {
        newPerson->next = head;
        return newPerson;
    }

    newPerson->next = current;
    previous->next = newPerson;
    return head;
}

// SORTIRANJE BUBBLE SORTOM – ZAMJENOM PODATAKA U ČVOROVIMA
Person* sortList(Person* head) {
    if (!head)
        return head;

    int swapped;
    Person* ptr;
    Person* last = NULL;

    do {
        swapped = 0;
        ptr = head;

        while (ptr->next != last) {
            if (compareIgnoreCase(ptr->prezime, ptr->next->prezime) > 0) {
                char tempIme[50], tempPrezime[50];
                int tempGodina;

                strcpy(tempIme, ptr->ime);
                strcpy(ptr->ime, ptr->next->ime);
                strcpy(ptr->next->ime, tempIme);

                strcpy(tempPrezime, ptr->prezime);
                strcpy(ptr->prezime, ptr->next->prezime);
                strcpy(ptr->next->prezime, tempPrezime);

                tempGodina = ptr->godina;
                ptr->godina = ptr->next->godina;
                ptr->next->godina = tempGodina;

                swapped = 1;
            }
            ptr = ptr->next;
        }
        last = ptr;
    } while (swapped);

    return head;
}

// SIGURNO OTVARANJE DATOTEKE UZ PROVJERU POGREŠKE
FILE* openFile(const char* filename, const char* mode) {
    FILE* fp = fopen(filename, mode);
    if (!fp) {
        printf("Greska pri otvaranju datoteke!\n");
        exit(1);
    }
    return fp;
}

// UPIS PODATAKA U DATOTEKU
void writeToFile(Person* head, const char* filename) {
    FILE* fp = openFile(filename, "w");

    while (head) {
        fprintf(fp, "%s %s %d\n", head->ime, head->prezime, head->godina);
        head = head->next;
    }

    fclose(fp);
    printf("Lista uspjesno upisana u datoteku.\n");
}

// UCITAVANJE LISTE IZ DATOTEKE
Person* readFromFile(const char* filename) {
    FILE* fp = openFile(filename, "r");
    Person* head = NULL;
    Person* last = NULL;

    while (!feof(fp)) {
        Person* temp = (Person*)malloc(sizeof(Person));

        if (fscanf(fp, "%s %s %d", temp->ime, temp->prezime, &temp->godina) != 3) {
            free(temp);
            break;
        }

        formatName(temp->ime);
        formatName(temp->prezime);
        temp->next = NULL;

        if (!head) {
            head = temp;
            last = temp;
        } else {
            last->next = temp;
            last = temp;
        }
    }

    fclose(fp);
    return head;
}
