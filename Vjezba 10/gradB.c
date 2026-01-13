#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gradB.h"

CityB* loadCity(CityB* head, char* name, int people)
{
    CityB* city = (CityB*)malloc(sizeof(CityB));
    if (!city)
    {
        printf("Greska pri alokaciji gradova!\n");
        return head;
    }

    strcpy(city->name, name);
    city->number_of_people = people;
    city->next = NULL;

    //Umetanje na pocetak 
    if (!head ||
        people < head->number_of_people ||
        (people == head->number_of_people &&
         strcmp(name, head->name) < 0))
    {
        city->next = head;
        return city;
    }

    CityB* current = head;

    while (current->next &&
          (current->next->number_of_people < people ||
          (current->next->number_of_people == people &&
           strcmp(current->next->name, name) < 0)))
    {
        current = current->next;
    }

    city->next = current->next;
    current->next = city;

    return head;
}
