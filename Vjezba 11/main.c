#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "drzava.h"
#include "grad.h"

int main() {
    
    HashTable ht;
    initHashTable(&ht);

    loadCountries(&ht, "drzave.txt");

    printHashTable(&ht);

    freeHashTable(&ht);

    return 0;
}
