#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MALLOC_ERROR -1
#define FILE_ERROR   -2

// Struktura jednog clana polinoma
typedef struct p
{
    int coef;          // koeficijent
    int exp;           // eksponent
    struct p *nxt;     // pokazivac na sljedeci clan
} poly;

// Prototipi funkcija
int insertSorted(int, int, poly *);        // umetanje clana u sortiranu listu
int readFromFile(char *, poly *, poly *);  // ucitavanje 2 polinoma iz datoteke
int sumPoly(poly *, poly *, poly *);       // zbrajanje
int mulPoly(poly *, poly *, poly *);       // množenje
void freePoly(poly *);                     // dealokacija liste


int main()
{
    // Glave lista
    poly head1 = {0, 0, NULL};
    poly head2 = {0, 0, NULL};
    poly head_sum = {0, 0, NULL};
    poly head_prod = {0, 0, NULL};

    // Ucitavanje polinoma iz datoteke
    if (readFromFile("input.txt", &head1, &head2) == FILE_ERROR)
    {
        printf("Greska pri otvaranju datoteke.\n");
        return FILE_ERROR;
    }

    // Racunanje zbroja i umnoška
    sumPoly(&head1, &head2, &head_sum);
    mulPoly(&head1, &head2, &head_prod);

    // Ispis polinoma
    poly *ptr;

    printf("%12s", "POLINOM 1:");
    for (ptr = head1.nxt; ptr != NULL; ptr = ptr->nxt)
    {
        printf("%dx^%d", ptr->coef, ptr->exp);
        if (ptr->nxt != NULL) printf(" + ");
    }

    printf("\n%-12s", "POLINOM 2:");
    for (ptr = head2.nxt; ptr != NULL; ptr = ptr->nxt)
    {
        printf("%dx^%d", ptr->coef, ptr->exp);
        if (ptr->nxt != NULL) printf(" + ");
    }

    printf("\n%-12s", "ZBROJ:");
    for (ptr = head_sum.nxt; ptr != NULL; ptr = ptr->nxt)
    {
        printf("%dx^%d", ptr->coef, ptr->exp);
        if (ptr->nxt != NULL) printf(" + ");
    }

    printf("\n%-12s", "UMNOZAK:");
    for (ptr = head_prod.nxt; ptr != NULL; ptr = ptr->nxt)
    {
        printf("%dx^%d", ptr->coef, ptr->exp);
        if (ptr->nxt != NULL) printf(" + ");
    }

    printf("\n");

    // Dealokacija svih listi
    freePoly(&head1);
    freePoly(&head2);
    freePoly(&head_sum);
    freePoly(&head_prod);

    return 0;
}


/*
    insertSorted(coef, exp, head)

    — Ubacuje novi clan polinoma u SORTIRANI poredak
    — Sortira silazno po eksponentu (najveci exponent prvi)
    — Ako vec postoji clan s istim eksponentom -> koeficijenti se zbrajaju
*/
int insertSorted(int coef, int exp, poly *curr)
{
    poly *node = (poly *)malloc(sizeof(poly));
    if (node == NULL)
        return MALLOC_ERROR;

    node->coef = coef;
    node->exp  = exp;
    node->nxt  = NULL;

    // Pronalaženje odgovarajuce pozicije (silazno sortiranje)
    while (curr->nxt != NULL && curr->nxt->exp > exp)
        curr = curr->nxt;

    // Ako postoji clan sa istim eksponentom -> zbroji
    if (curr->nxt != NULL && curr->nxt->exp == exp)
    {
        curr->nxt->coef += coef;
        free(node);
        return 0;
    }

    // Inace ubaci novi clan
    node->nxt = curr->nxt;
    curr->nxt = node;

    return 0;
}


/*
    readFromFile(path, p1, p2)

    — Cita prvi red i dodaje u P1
    — Cita drugi red i dodaje u P2
    — Svaki red može imati proizvoljan broj clanova (dok ne dođe newline)
*/
int readFromFile(char *path, poly *p1, poly *p2)
{
    FILE *fp = fopen(path, "r");
    if (fp == NULL)
        return FILE_ERROR;

    char flag = '0';
    int tmpCoef = 0, tmpExp = 0;

    // PRVI RED -> P1
    while (flag != '\n' && flag != EOF)
    {
        if (fscanf(fp, "%d %d", &tmpCoef, &tmpExp) != 2)
            break;
        insertSorted(tmpCoef, tmpExp, p1);
        flag = fgetc(fp);
    }

    flag = '0';

    // DRUGI RED -> P2
    while (flag != EOF)
    {
        if (fscanf(fp, "%d %d", &tmpCoef, &tmpExp) != 2)
            break;
        insertSorted(tmpCoef, tmpExp, p2);
        flag = fgetc(fp);
    }

    fclose(fp);
    return 0;
}


/*
    Zbrajanje polinoma: P1 + P2
    — Samo redom ubacujemo sve clanove, sorting ce riješiti sve slucajeve
    — Ako postoje isti eksponenti → insertSorted ce ih zbrojit
*/
int sumPoly(poly *p1, poly *p2, poly *res)
{
    p1 = p1->nxt;
    p2 = p2->nxt;

    while (p1 != NULL)
    {
        insertSorted(p1->coef, p1->exp, res);
        p1 = p1->nxt;
    }

    while (p2 != NULL)
    {
        insertSorted(p2->coef, p2->exp, res);
        p2 = p2->nxt;
    }

    return 0;
}


/*
    Množenje polinoma: P1 * P2
    — Svaki clan prvog množi se sa svakim clanom drugog
    — Rezultat se ubacuje u sortiranu listu
*/
int mulPoly(poly *p1, poly *p2, poly *res)
{
    p1 = p1->nxt;
    p2 = p2->nxt;

    poly *start = p2;

    while (p1 != NULL)
    {
        p2 = start;
        while (p2 != NULL)
        {
            insertSorted(p1->coef * p2->coef, p1->exp + p2->exp, res);
            p2 = p2->nxt;
        }
        p1 = p1->nxt;
    }

    return 0;
}


/*
    freePoly(head)
    
    — Dealocira sve cvorove LISTE (ne briše glavu)
    — Koristi standardni traversal i free()
*/
void freePoly(poly *head)
{
    poly *curr = head->nxt;
    poly *tmp;

    while (curr != NULL)
    {
        tmp = curr;
        curr = curr->nxt;
        free(tmp);
    }

    head->nxt = NULL;
}
