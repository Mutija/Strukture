#include <stdio.h>

int main() {

    FILE *fo; //pokazivac za otvaranje datoteke

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


    return 0;
}
