#ifndef DRZAVAB_H
#define DRZAVAB_H

#include "gradB.h"

typedef struct countryB
{
    char name[50];
    struct countryB* left;
    struct countryB* right;
    CityB* cityHead; //pocetak liste gradova
}CountryB;

CountryB* loadCountry(CountryB* root, char* name);

#endif