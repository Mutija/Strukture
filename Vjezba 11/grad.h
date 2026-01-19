#ifndef GRAD_H
#define GRAD_H

typedef struct city {
    char name[30];
    int number_of_people;
    struct city* left;
    struct city* right;
} City;

City* loadCity(City* root, char* name, int people);
void printCities(City* root);
void freeCities(City* root);

#endif
