#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"drzava.h"
#include"grad.h"

int main(){

    Country* head = NULL;

    head = loadCountries("drzave.txt");
    printCountries(head);

    freeCountries(head);
    
    return 0;
}