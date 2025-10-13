#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char ime[20];
    char prezime[50];
    int bodovi;
} Student;

//Funkcija za brojanje redaka
int rowCounter(FILE *fo) {
    int count = 0;
    char c;

    //Petlja za brojanje redaka
    while ((c = getc(fo)) != EOF) {

        if (c == '\n')
            count++;

    }

    rewind(fo); //Vracanje pokazivaca na pocetak datoteke

    return count;
}

//Funkcija za ucitavanje dinamickog niza
Student* loadStudent(FILE *fo, int count) {

    Student *stud = (Student*) malloc(sizeof(Student) * count);

    //Ucitavanje studenata u strukturu
    for (int i = 0; i < count; i++) {
        fscanf(fo, "%s %s %d", stud[i].ime, stud[i].prezime, &stud[i].bodovi);
    }

    return stud;
}

//Funkcija za ispis svih studenata + relativni bodovi
void printStudent(Student *stud, int count, int max) {

    for (int i = 0; i < count; i++) {

        float rel = (float)stud[i].bodovi / max * 100;

        printf("Ime i prezime: %s %s\n", stud[i].ime, stud[i].prezime);
        printf("Broj bodova: %d\n", stud[i].bodovi);
        printf("Relativan broj bodova: %.2f%%\n\n", rel);

    }
}

//Funkcija za trazenje maksimalnog broja bodova
int findMax(Student *stud, int count) {

    int max = stud[0].bodovi;
    for (int i = 1; i < count; i++) {
        if (stud[i].bodovi > max)
            max = stud[i].bodovi;
    }

    return max;
}

int main() {

    FILE *fo = fopen("student.txt", "r");

    int count = rowCounter(fo);
    Student *stud = loadStudent(fo, count);

    int max = findMax(stud, count);

    printStudent(stud, count, max);

    return 0;
}
