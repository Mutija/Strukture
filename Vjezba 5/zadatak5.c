#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// DEFINICIJA STRUKTURE

typedef struct StackNode {
    double value;               // Vrijednost pohranjena u cvoru
    struct StackNode* next;     // Pokazivac na sljedeci cvor u stogu
} StackNode;

typedef StackNode* Position;


// DEKLARACIJE FUNKCIJA

FILE* openFile(const char* filename, const char* mode);
int push(Position head, double value);
double pop(Position head);
int printStack(Position head);
double evaluatePostfix(const char* filename);


// GLAVNA FUNKCIJA

int main() {
    double result = evaluatePostfix("postfix.txt");
    printf("Konacni rezultat: %.2lf\n", result);
    return 0;
}


// FUNKCIJA ZA OTVARANJE DATOTEKE

FILE* openFile(const char* filename, const char* mode) {
    FILE* file = fopen(filename, mode);
    if (file == NULL) {
        printf("Greska: nije moguce otvoriti datoteku '%s'\n", filename);
        exit(EXIT_FAILURE);
    }
    return file;
}


// OPERACIJE NAD STOGOM


// Dodaje novi element na vrh stoga
int push(Position head, double value) {
    Position newNode = (Position)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        printf("Greska: neuspjela alokacija memorije.\n");
        return -1;
    }

    newNode->value = value;
    newNode->next = head->next;
    head->next = newNode;
    return 0;
}

// Uklanja element s vrha stoga i vraca njegovu vrijednost
double pop(Position head) {
    Position temp = head->next;
    if (temp == NULL) {
        printf("Greska: stog je prazan.\n");
        return 0;
    }

    double poppedValue = temp->value;
    head->next = temp->next;
    free(temp);
    return poppedValue;
}

// Ispisuje sve elemente na stogu (od vrha prema dnu)
int printStack(Position head) {
    Position temp = head->next;
    while (temp != NULL) {
        printf("%.2lf ", temp->value);
        temp = temp->next;
    }
    printf("\n");
    return 0;
}


// FUNKCIJA ZA IZRAcUNAVANJE POSTFIKSNOG IZRAZA

double evaluatePostfix(const char* filename) {
    FILE* file = openFile(filename, "r");  // Otvara datoteku s izrazom

    StackNode head;
    head.next = NULL; // Inicijalizacija praznog stoga

    char token[1024]; // Privremeni string za citanje brojeva i operatora

    // cita po jedan token iz datoteke dok ih ima
    while (fscanf(file, "%s", token) == 1) {

        // Ako token predstavlja broj (ili negativan broj)
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(&head, atof(token)); // Pretvara string u broj i stavlja ga na stog
        }
        // Ako je token operator
        else {
            double operand2 = pop(&head);
            double operand1 = pop(&head);
            double result = 0;

            // Izvrsava odgovarajucu matematicku operaciju
            switch (token[0]) {
                case '+': result = operand1 + operand2; break;
                case '-': result = operand1 - operand2; break;
                case '*': result = operand1 * operand2; break;
                case '/':
                    if (operand2 == 0) {
                        printf("Greska: dijeljenje s nulom.\n");
                        fclose(file);
                        return 0;
                    }
                    result = operand1 / operand2;
                    break;
                default:
                    printf("Greska: nepoznat operator '%s'\n", token);
                    fclose(file);
                    return 0;
            }
            // Rezultat operacije vraca natrag na stog
            push(&head, result);
        }
    }

    fclose(file);

    // Na kraju bi na stogu trebao ostati samo jedan element — konacni rezultat
    double finalResult = pop(&head);
    return finalResult;
}
