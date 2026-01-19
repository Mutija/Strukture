#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "drzava.h"

//Hash za zbroj ASCII kodova - unsigned char zbog raspona obicnog chara (-128 - 127) -> (0 - 255)
int hashFunction(const char* name) {
    int sum = 0;
    for (int i = 0; i < 5 && name[i] != '\0'; i++) {
        sum += (unsigned char)name[i];
    }
    return sum % TABLE_SIZE;
}

void initHashTable(HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++)
        ht->table[i] = NULL;
}

CountryNode* createCountryNode(const char* name, const char* cityFile) {
    CountryNode* node = (CountryNode*)malloc(sizeof(CountryNode));
    if (!node) {
        printf("Greska pri alokaciji memorije za drzave!\n");
        return NULL;
    }

    strcpy(node->name, name);
    strcpy(node->citiesFile, cityFile);
    node->cityRoot = NULL;
    node->next = NULL;
    return node;
}

//Umetanje u sortiranu vezanu listu u ladici
void insertCountry(HashTable* ht, const char* name, const char* cityFile) {
    int index = hashFunction(name);
    CountryNode* head = ht->table[index];

    CountryNode* newNode = createCountryNode(name, cityFile);
    if (!newNode)
        return;

    //Lista prazna ili se ide na pocetak
    if (head == NULL || strcmp(name, head->name) < 0) {
        newNode->next = head;
        ht->table[index] = newNode;
        return;
    }

    //Trazi mjesto u listi sortirano po imenu
    CountryNode* current = head;
    while (current->next != NULL && strcmp(current->next->name, name) < 0) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

//Ucitavanje svih drzava i formiranje hash tablice
void loadCountries(HashTable* ht, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Greska pri otvaranju %s\n", filename);
        return;
    }

    char countryName[50];
    char cityFile[50];

    while (fscanf(f, "%s %s", countryName, cityFile) == 2) {
        insertCountry(ht, countryName, cityFile);
    }

    fclose(f);

    //Nakon ubacivanja dzava, ucitavamo gradove u stablo
    for (int i = 0; i < TABLE_SIZE; i++) {
        CountryNode* current = ht->table[i];
        while (current) {
            loadCitiesByCountry(current);
            current = current->next;
        }
    }
}

int loadCitiesByCountry(CountryNode* country) {
    FILE* f = fopen(country->citiesFile, "r");
    if (!f) {
        printf("Greska pri otvaranju datoteke %s\n", country->citiesFile);
        return -1;
    }

    char cityName[50];
    int people;
    int cityCount = 0;

    while (fscanf(f, " %49[^,], %d", cityName, &people) == 2) {
        country->cityRoot = loadCity(country->cityRoot, cityName, people);
        cityCount++;
    }

    fclose(f);
    return cityCount;
}

void printHashTable(HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Ladica %d:\n", i);
        CountryNode* current = ht->table[i];

        if (!current) {
            printf("  (prazno)\n");
        }

        while (current) {
            printf("  %s\n", current->name);
            //Ispis gradova sortirano po broju stanovnika pa po imenu
            printCities(current->cityRoot);
            printf("\n");
            current = current->next;
        }
        printf("-------------------------\n");
    }
}

void freeHashTable(HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        CountryNode* current = ht->table[i];
        while (current) {
            CountryNode* temp = current;
            current = current->next;
            freeCities(temp->cityRoot);
            free(temp);
        }
        ht->table[i] = NULL;
    }
}
