#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../header/racun.h"

//Funkcija za alociranje novog racuna 
Bill *createBill(const char *productDate){

    Bill *b = malloc(sizeof(Bill));

    if(!b){

        printf("Greška pri alokaciji memorije!");
        return NULL;

    }

    strcpy(b->date, productDate);
    b->products = NULL;
    b->next = NULL;

    return b;

}

//Funkcija za alociranje novog artikla
Product *createProduct(const char *productName, int amount, double price){

    Product *p = malloc(sizeof(Product));

    if(!p){

        printf("Greška pri alokaciji memorije!");
        return NULL;

    }

    strcpy(p->name, productName);
    p->amount = amount;
    p->price = price;
    p->next = NULL;

    return p;

}

//Funkcija za ucitavanje jednog racuna
Bill *loadBillProducts(const char *fileName){

    FILE *file = fopen(fileName, "r");

    if(!file){

        printf("Greska: Datoteka se ne moze otvoriti!");
        exit(EXIT_FAILURE);

    }

    char productDate[MAX_DATE];
    char productName[MAX_NAME];
    int amount;
    double price;

    //Citanje datuma
    if (fscanf(file, "%10s", productDate) != 1)
    {

        printf("Datum nije ispravan %s", fileName);
        fclose(file);
        return NULL;

    }
    
    Bill *b = createBill(productDate);

    //Citanje imena, kolicine i cijene
    while (fscanf(file, " %19[^,], %d, %lf", productName, &amount, &price) == 3){

        Product *p = createProduct(productName, amount, price);

        if (!p)
            continue;

        insertProductSorted(b, p);

    }
    
    fclose(file);

    return b;

}

//Funkcija za gradenje liste svih racuna
Bill *loadAllBills (const char *dataList){

    FILE *file = fopen(dataList, "r");

    if(!file){

        printf("Greska: Datoteka se ne moze otvoriti!");
        exit(EXIT_FAILURE);

    }

    Bill *head = NULL;
    char fileName[20];

    while (fscanf(file, "%19s", fileName) == 1)
    {

        Bill *b = loadBillProducts(fileName);

        if(b == NULL)
            continue;

        insertBillSorted(&head, b);

    }
    
    fclose(file);

    return head;

}

void printAllBills(Bill *head){

    while(head != NULL){

        printf("Racun - datum %s\n", head->date);

        Product *p = head->products;

        while(p != NULL){

            printf("%s, kolicina: %d, cijena: %.2f\n", p->name, p->amount, p->price);
            p = p->next;

        }

        printf("\n");
        head = head->next;

    }

}

void clear(Bill *head)
{
    while (head != NULL)
    {
        Bill *tempBill = head;
        head = head->next;

        Product *p = tempBill->products;
        while (p != NULL)
        {
            Product *tempProd = p;
            p = p->next;
            free(tempProd);
        }

        free(tempBill);
    }
}

void toLowerStr(char *s) {
    for (int i = 0; s[i]; i++)
        s[i] = tolower((unsigned char)s[i]);
}

void queryProduct(Bill *head)
{
    char wantedName[MAX_NAME];
    char fromDate[MAX_DATE];
    char toDate[MAX_DATE];

    printf("Unesi naziv artikla: ");
    scanf(" %19s", wantedName);

    printf("Unesi pocetni datum (YYYY-MM-DD): ");
    scanf(" %10s", fromDate);

    printf("Unesi krajnji datum (YYYY-MM-DD): ");
    scanf(" %10s", toDate);

    int totalAmount = 0;
    double totalMoney = 0.0;

    Bill *b = head;

    //Pretvaranje wantedNamea u lowercase
    char wantedLower[MAX_NAME];
    strcpy(wantedLower, wantedName);
    toLowerStr(wantedLower);

    while (b != NULL)
    {
        if (strcmp(b->date, fromDate) >= 0 && strcmp(b->date, toDate) <= 0)
        {
            Product *p = b->products;
            while (p != NULL)
            {
                char productLower[MAX_NAME];
                strcpy(productLower, p->name);
                toLowerStr(productLower);

                if (strcmp(productLower, wantedLower) == 0)
                {
                    totalAmount += p->amount;
                    totalMoney += p->amount * p->price;
                }

                p = p->next;
            }
        }

        b = b->next;
    }

    if (totalAmount == 0)
    {
        printf("Artikl %s nije kupljen u zadanom razdoblju.\n", wantedName);
    }
    else
    {
        printf("Artikl: %s\n", wantedName);
        printf("Ukupna kolicina: %d\n", totalAmount);
        printf("Ukupno potroseno: %.2f\n", totalMoney);
    }
}


void insertProductSorted(Bill *bill, Product *p)
{
    //Ako je lista prazna ili novi treba biti prvi 
    if (bill->products == NULL || strcmp(p->name, bill->products->name) < 0)
    {
        p->next = bill->products;
        bill->products = p;
        return;
    }

    //Trazenje mjesta gdje treba ubaciti
    Product *current = bill->products;
    while (current->next != NULL && strcmp(current->next->name, p->name) < 0)
    {
        current = current->next;
    }

    //Ubacivanje iza trenutnog
    p->next = current->next;
    current->next = p;
}

void insertBillSorted(Bill **head, Bill *b)
{
    // ako je lista prazna ili novi racun treba biti prvi po datumu
    if (*head == NULL || strcmp(b->date, (*head)->date) < 0)
    {
        b->next = *head;
        *head = b;
        return;
    }

    Bill *current = *head;
    while (current->next != NULL && strcmp(current->next->date, b->date) < 0)
    {
        current = current->next;
    }

    b->next = current->next;
    current->next = b;
}

void showStatistics(Bill *head)
{
    double totalMoney = 0.0;       
    int totalUnits = 0;            
    int totalLines = 0;            

    double maxLineSpent = 0.0;
    char maxName[MAX_NAME] = "";
    char maxDate[MAX_DATE] = "";

    Bill *b = head;

    while (b != NULL)
    {
        Product *p = b->products;
        while (p != NULL)
        {
            double lineSpent = p->price;

            totalMoney += lineSpent;
            totalUnits += p->amount;
            totalLines++;

            if (lineSpent > maxLineSpent)
            {
                maxLineSpent = lineSpent;
                strcpy(maxName, p->name);
                strcpy(maxDate, b->date);
            }

            p = p->next;
        }

        b = b->next;
    }

    printf("\nSTATISTIKA\n");

    if (totalLines == 0)
    {
        printf("Nema artikala u racunima.\n");
        return;
    }

    printf("Ukupno potroseno: %.2f€\n", totalMoney);
    printf("Ukupno kupljenih proizvoda: %d\n", totalUnits);
    printf("Ukupan broj razlicitih proizvoda: %d\n", totalLines);

    if (totalUnits > 0)
    {
        double avgPerUnit = totalMoney / totalUnits;
        printf("Prosjecna cijena po proizvodu: %.2f\n", avgPerUnit);
    }

    if (maxLineSpent > 0.0)
    {
        printf("\nNajskuplji proizvod:\n");
        printf("  Artikl: %s\n", maxName);
        printf("  Datum racuna: %s\n", maxDate);
        printf("  Ukupno za tu stavku: %.2f\n", maxLineSpent);
    }

    printf("\n");
}


