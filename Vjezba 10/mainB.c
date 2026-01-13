#include <stdio.h>
#include "drzavaB.h"

int main()
{
    CountryB* root = openCountries("drzave.txt");
    if (!root)
        return -1;

    printCountries(root);

    freeCountries(root);
    return 0;
}
