#ifndef RACUN_H
#define RACUN_H

#define MAX_DATE 11 //zbog '\0'
#define MAX_NAME 20

//Struktura za produkt na racunu
typedef struct Product 
{
    char name[MAX_NAME];
    int amount;
    double price;
    struct Product *next;
}Product;

//Struktura za jedan racun
typedef struct Bill
{
    char date[MAX_DATE];
    Product *products;
    struct Bill *next;
}Bill;

//Funkcija za ucitavanje svih racuna iz racuni.txt
Bill *loadAllBills(const char *dataList);

//Funkcija za ispis svih racuna
void printAllBills(Bill *head);

//Funkcija za ciscenje memorije
void clear(Bill *head);

//Funkcija za upit
void queryProduct(Bill *head);

//Funkcija za sortirani unos artikala
void insertProductSorted(Bill *bill, Product *p);

//Funkcija za sortirani unos racuna
void insertBillSorted(Bill **head, Bill *b);

//Funkcija za izracun statistike prodaje
void showStatistics(Bill *head);

#endif