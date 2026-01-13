#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "drzavaB.h"

CountryB* createCountry(char* name)
{
    CountryB* c = (CountryB*)malloc(sizeof(CountryB));
    if (!c)
        return NULL;

    strcpy(c->name, name);
    c->left = NULL;
    c->right = NULL;
    c->cityHead = NULL;

    return c;
}

CountryB* loadCountry(CountryB* root, char* name)
{
    if (!root)
        return createCountry(name);

    if (strcmp(name, root->name) < 0)
        root->left = loadCountry(root->left, name);
    else if (strcmp(name, root->name) > 0)
        root->right = loadCountry(root->right, name);

    return root;
}

CountryB* findCountry(CountryB* root, char* name)
{
    if (!root)
        return NULL;

    if (strcmp(name, root->name) == 0)
        return root;

    if (strcmp(name, root->name) < 0)
        return findCountry(root->left, name);

    return findCountry(root->right, name);
}

void loadCitiesFromFile(CountryB* country, char* filename)
{
    FILE* fp = fopen(filename, "r");
    if (!fp)
        return;

    char cityName[30];
    int people;

    while (fscanf(fp, " %[^,], %d", cityName, &people) == 2)
    {
        country->cityHead = loadCity(country->cityHead, cityName, people);
    }

    fclose(fp);
}

CountryB* openCountries(char* filename)
{
    FILE* fp = fopen(filename, "r");
    if (!fp)
    {
        printf("Ne mogu otvoriti %s\n", filename);
        return NULL;
    }

    CountryB* root = NULL;
    char countryName[50];
    char cityFile[50];

    while (fscanf(fp, " %s %s", countryName, cityFile) == 2)
    {
        root = loadCountry(root, countryName);

        CountryB* c = findCountry(root, countryName);
        if (c)
            loadCitiesFromFile(c, cityFile);
    }

    fclose(fp);
    return root;
}

void freeCities(CityB* head)
{
    CityB* tmp;
    while (head)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

void freeCountries(CountryB* root)
{
    if (!root)
        return;

    freeCountries(root->left);
    freeCountries(root->right);
    freeCities(root->cityHead);
    free(root);
}

// Pomoćna funkcija za ispis gradova
void printCities(CityB* head)
{
    CityB* tmp = head;
    while (tmp)
    {
        printf("    %s (%d)\n", tmp->name, tmp->number_of_people);
        tmp = tmp->next;
    }
}

// Rekurzivni ispis država i njihovih gradova
void printCountries(CountryB* root)
{
    if (!root)
        return;

    printCountries(root->left);

    printf("%s:\n", root->name);
    printCities(root->cityHead);

    printCountries(root->right);
}