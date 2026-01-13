#ifndef DRZAVA_H
#define DRZAVA_H

#include "grad.h"

typedef struct country{

    char name[50];
    char citiesFile[50];
    City* first_city; //pokazivac na prvi grad u strukturi city
    struct country *next; //pokazivac na sljedecu drzavu u listi
} Country;

Country* countrySorter(Country* head, char* name, char* cityFile);
Country* loadCountries(char* filename);
int loadCitiesByCountry(Country* country);
void printCountries(Country* head);
void freeCountries(Country* head);

#endif