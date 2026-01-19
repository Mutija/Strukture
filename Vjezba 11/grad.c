#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grad.h"

City* loadCity(City* root, char* name, int people) {
    if (root == NULL) {
        City* city = (City*)malloc(sizeof(City));
        if (!city) {
            printf("Greska pri alokaciji gradova!\n");
            return NULL;
        }

        strcpy(city->name, name);
        city->number_of_people = people;
        city->left = NULL;
        city->right = NULL;
        return city;
    }

    if (people < root->number_of_people) {
        root->left = loadCity(root->left, name, people);
    }
    else if (people > root->number_of_people) {
        root->right = loadCity(root->right, name, people);
    }
    else {
        int compare = strcmp(name, root->name);
        if (compare < 0)
            root->left = loadCity(root->left, name, people);
        else if (compare > 0)
            root->right = loadCity(root->right, name, people);
    }

    return root;
}

void printCities(City* root) {
    if (!root)
        return;

    printCities(root->left);
    printf("    %s %d\n", root->name, root->number_of_people);
    printCities(root->right);
}

void freeCities(City* root) {
    if (!root)
        return;

    freeCities(root->left);
    freeCities(root->right);
    free(root);
}
