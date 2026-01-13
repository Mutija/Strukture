#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"drzava.h"

Country* countrySorter(Country* head, char* name, char*cityFile){

    Country* country = (Country*)malloc(sizeof(Country));
    if(!country){

        printf("Greska pri alokaciji memorije za drzave!");
        return head;

    }

    strcpy(country->name, name);
    strcpy(country->citiesFile, cityFile);
    country->first_city = NULL;
    country->next = NULL;

    //Slucaj kad je lista prazna ili nova drzava ide na pocetak
    if(head == NULL || strcmp(name, head->name) < 0){

        country->next = head;
        head = country;
    }
        else{
            //Postavljanje nakon prvog
            Country* current = head;
            while(current->next != NULL && strcmp(current->next->name, name) < 0){

                current = current->next;

            }

            country->next = current->next;
            current->next = country;
        }

        return head;
    }

//Ucitavanje drzava iz datoteke
Country* loadCountries(char* filename){

    FILE* f = fopen(filename, "r");

    if(!f){

        printf("Greska pri otvaranju! %s\n", filename);
        return NULL;

    }

    Country* head = NULL;
    char countryName[50];
    char cityFile[50];

    while (fscanf(f, "%s %s", countryName, cityFile) == 2){

        //Sortiranje drzava
        head = countrySorter(head, countryName, cityFile);

        Country* newCountry = head;
        while (newCountry->next != NULL && strcmp(newCountry->name, countryName) != 0)
            newCountry = newCountry->next;
        
            if(newCountry != NULL)
                loadCitiesByCountry(newCountry);

    }


    fclose(f);

    return head;

}

int loadCitiesByCountry(Country* country){

    FILE* f = fopen(country->citiesFile, "r");

    if(!f){

        printf("Greska pri otvaranju datoteke %s\n", country->citiesFile);
        return -1;

    }

    char cityName[50];
    int people;
    int cityCount = 0;

    while(fscanf(f, " %49[^,], %d", cityName, &people) == 2){

        country->first_city = loadCity(country->first_city, cityName, people);
        cityCount++;

    }

    fclose(f);
    
    return cityCount;

}

void printCountries(Country* head){

    Country* current = head;


    while(current != NULL){

        printf("%s\n", current->name);
        printCities(current->first_city);
        printf("\n");
        current = current->next;
    }

}

void freeCountries(Country* head)
{
    Country* temp;

    while(head){
        temp = head;
        head = head->next;

        freeCities(temp->first_city); // prvo gradovi
        free(temp);                   // onda drzava
    }
}
