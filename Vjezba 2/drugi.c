#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//STRUKTURA 
typedef struct Person {
    char ime[50];
    char prezime[50];
    int godina;
    struct Person* next;
} Person;

//PROTOTIPOVI 
Person* addToBeginning(Person* head);
void printList(Person* head);
Person* addToEnd(Person* head);
Person* findBySurname(Person* head, const char* prezime);
Person* deleteBySurname(Person* head, const char* prezime);
void initPerson(Person* p);
void formatName(char* str);         
int compareIgnoreCase(const char* a, const char* b); 

//MAIN 
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
        }
    } while (izbor != 0);

    //Oslobađanje memorije
    Person* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}

// FUNKCIJE 

// 1. Dodavanje na početak
Person* addToBeginning(Person* head) {
    Person* newPerson = (Person*)malloc(sizeof(Person));
    if (!newPerson) {
        printf("Greska pri alokaciji memorije!\n");
        return head;
    }

    initPerson(newPerson);
    newPerson->next = head;
    return newPerson;
}

// 2. Ispis liste
void printList(Person* head) {
    Person* current = head;
    if (!current) {
        printf("Lista je prazna.\n");
        return;
    }

    while (current != NULL) {
        printf("%s %s, %d\n", current->ime, current->prezime, current->godina);
        current = current->next;
    }
}

// 3. Dodavanje na kraj
Person* addToEnd(Person* head) {
    Person* newPerson = (Person*)malloc(sizeof(Person));
    if (!newPerson) {
        printf("Greska pri alokaciji memorije!\n");
        return head;
    }
    initPerson(newPerson);
    newPerson->next = NULL;

    if (head == NULL)
        return newPerson;

    Person* current = head;
    while (current->next != NULL)
        current = current->next;

    current->next = newPerson;
    return head;
}

// 4. Pronalaženje po prezimenu (case-insensitive)
Person* findBySurname(Person* head, const char* prezime) {
    Person* current = head;
    while (current != NULL) {
        if (compareIgnoreCase(current->prezime, prezime) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}

// 5. Brisanje po prezimenu (case-insensitive)
Person* deleteBySurname(Person* head, const char* prezime) {
    Person* current = head;
    Person* previous = NULL;

    while (current != NULL && compareIgnoreCase(current->prezime, prezime) != 0) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Osoba s prezimenom '%s' nije pronadena.\n", prezime);
        return head;
    }

    if (previous == NULL)
        head = current->next;
    else
        previous->next = current->next;

    free(current);
    printf("Osoba obrisana.\n");

    return head;
}

//Funkcija za unos i formatiranje imena
void initPerson(Person* p) {
    printf("Unesi ime: ");
    scanf("%s", p->ime);
    formatName(p->ime);  //prvo veliko, ostala mala

    printf("Unesi prezime: ");
    scanf("%s", p->prezime);
    formatName(p->prezime);  

    printf("Unesi godinu rodenja: ");
    scanf("%d", &p->godina);
}

//Formatiranje stringa tako da prvo slovo bude veliko, ostala mala
void formatName(char* str) {
    if (str[0] != '\0') {
        str[0] = toupper((unsigned char)str[0]);
        for (int i = 1; str[i]; i++)
            str[i] = tolower((unsigned char)str[i]);
    }
}

//Usporedba neovisna o veličini slova
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