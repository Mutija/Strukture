#ifndef DRZAVA_H
#define DRZAVA_H

#include "grad.h"

#define TABLE_SIZE 11

typedef struct countryNode {
    char name[50];
    char citiesFile[50];
    City* cityRoot;               //Korijen stabla gradova
    struct countryNode* next;     //Sljedeca drzava u lancu (sortirano po imenu)
} CountryNode;

typedef struct {
    CountryNode* table[TABLE_SIZE];
} HashTable;

//Hash funkcija
int hashFunction(const char* name);

//Rad s hash tablicom
void initHashTable(HashTable* ht);
CountryNode* createCountryNode(const char* name, const char* cityFile);
void insertCountry(HashTable* ht, const char* name, const char* cityFile);

//Ucitavanje iz datoteka
void loadCountries(HashTable* ht, const char* filename);
int loadCitiesByCountry(CountryNode* country);

//Ispis i oslobadanje memorije
void printHashTable(HashTable* ht);
void freeHashTable(HashTable* ht);

#endif