#include <stdio.h>
#include<stdlib.h>

typedef struct{
    
    char ime[20];
    char prezime[50];
    int bodovi;

}student;



int main() {

    FILE *fo; //pokazivac za otvaranje datoteke

    student *stud; //pokazivac na strukturu

    int count = 0; //varijabla brojaca

    char c; //trenutni character

    fo = fopen("student.txt", "r");

    if(fo == NULL){

        printf("Datoteka se ne moze otvoriti!");

    }

    //for petlja za brojanje svih redaka u datoteci
    for(; (c = getc(fo)) != EOF;){

        if(c == '\n'){

            count++;

        }

    }

    //vracanje na pocetak datoteke da bi mogli ponovo krenuti od pocetka u for petlji
    rewind(fo);

    //dinamicka alokacija za niz struktura
    stud = (student *)malloc(sizeof(student) * count);

    //ucitavanje podataka iz datoteke
    for (int i = 0; i < count; i++)
    {
        fscanf(fo, "%s %s %d", stud[i].ime, stud[i].prezime, &stud[i].bodovi);
    }
    
    for (int i = 0; i < count; i++)
    {
        printf("%s %s: %d\n", stud[i].ime, stud[i].prezime, stud[i].bodovi);
    }
    
    return 0;
}
