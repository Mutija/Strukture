#ifndef GRADB_H
#define GRADB_H


typedef struct cityB
{
    char name[30];
    int number_of_people;
    struct cityB *next;
}CityB;

CityB* loadCity(CityB* head, char* name, int people);
#endif