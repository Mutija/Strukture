#ifndef DRZAVAB_H
#define DRZAVAB_H

#include "gradB.h"

typedef struct countryB
{
    char name[50];
    struct countryB* left;
    struct countryB* right;
    CityB* cityHead;
} CountryB;

//Ucitavanje drzava i gradova 
CountryB* openCountries(char* filename);

CountryB* loadCountry(CountryB* root, char* name);
CountryB* findCountry(CountryB* root, char* name);

void loadCitiesFromFile(CountryB* country, char* filename);
void printCountries(CountryB* root);

void freeCountries(CountryB* root);

#endif
