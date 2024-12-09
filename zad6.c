#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct artikl* pozicijaartikl;
typedef struct artikl {
    char ime[32];
    int kolicina;
    float cijena;
    pozicijaartikl next;
} artikl;

typedef struct racun* pozicijaracun;
typedef struct racun {
    char datum[32];
    pozicijaartikl artikli;
    pozicijaracun next;
} racun;

int kreirajracun(pozicijaracun head, const char* filename);
int sortunosracuna(pozicijaracun head, pozicijaracun novi);
int jeveci(pozicijaracun prvi, pozicijaracun drugi);
int sortartikle(pozicijaartikl glava, pozicijaartikl novi);
int pretrazi(pozicijaracun head, int dani1, int dani2, char* naziv);
int ukupnodanaodpocetka(int godina, int mjesec, int dan);

int main() {
    pozicijaracun head = (pozicijaracun)malloc(sizeof(racun));
    if (!head) {
        printf("Greska pri alokaciji memorije.\n");
        return -1;
    }
    head->next = NULL;
    head->artikli = NULL;
    strcpy(head->datum, "");

    if (kreirajracun(head, "racuni.txt") != EXIT_SUCCESS) {
        printf("Greska pri citanju datoteke.\n");
        free(head);
        return -1;
    }

    int godina1, mjesec1, dan1;
    int godina2, mjesec2, dan2;
    char x[32];

    printf("Unesite datum1 u formatu GGGG-MM-DD:\n");
    scanf("%d-%d-%d", &godina1, &mjesec1, &dan1);
    printf("Unesite datum2 u formatu GGGG-MM-DD:\n");
    scanf("%d-%d-%d", &godina2, &mjesec2, &dan2);
    printf("Unesite trazeni artikl:\n");
    scanf("%s", x);

    int dani1 = ukupnodanaodpocetka(godina1, mjesec1, dan1);
    int dani2 = ukupnodanaodpocetka(godina2, mjesec2, dan2);

    if (dani1 > dani2) {
        printf("Greska: Datum1 mora biti manji od Datum2.\n");
        free(head);
        return -1;
    }

    pretrazi(head, dani1, dani2, x);

    pozicijaracun temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}

int kreirajracun(pozicijaracun head, const char* filename) {
    FILE* fh = fopen(filename, "r");
    if (!fh) {
        printf("Greska prilikom otvaranja datoteke: %s\n", filename);
        return -1;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fh)) {
        buffer[strcspn(buffer, "\n")] = '\0';

        FILE* fh2 = fopen(buffer, "r");
        if (!fh2) {
            printf("Greska pri otvaranju racuna: %s\n", buffer);
            continue;
        }

        char bufferdatum[32];
        if (fgets(bufferdatum, sizeof(bufferdatum), fh2)) {
            bufferdatum[strcspn(bufferdatum, "\n")] = '\0';
            pozicijaracun novi = (pozicijaracun)malloc(sizeof(racun));
            if (!novi) {
                printf("Greska pri alokaciji racuna.\n");
                fclose(fh2);
                continue;
            }
            strcpy(novi->datum, bufferdatum);
            novi->artikli = NULL;
            novi->next = NULL;

            char name[32];
            int kolicina;
            float cijena;

            while (fgets(buffer, sizeof(buffer), fh2)) {
                buffer[strcspn(buffer, "\n")] = '\0';

                if (sscanf(buffer, "%31s %d %f", name, &kolicina, &cijena) == 3) {
                    pozicijaartikl noviartikl = (pozicijaartikl)malloc(sizeof(artikl));
                    if (!noviartikl) {
                        printf("Greska pri alokaciji artikla.\n");
                        continue;
                    }
                    strcpy(noviartikl->ime, name);
                    noviartikl->kolicina = kolicina;
                    noviartikl->cijena = cijena;
                    noviartikl->next = NULL;

                    if (!novi->artikli) {
                        novi->artikli = noviartikl;
                    }
                    else {
                        sortartikle(novi->artikli, noviartikl);
                    }
                }
            }

            sortunosracuna(head, novi);
        }
        fclose(fh2);
    }

    fclose(fh);
    return EXIT_SUCCESS;
}

int sortunosracuna(pozicijaracun head, pozicijaracun novi) {
    pozicijaracun curr = head;
    while (curr->next && jeveci(curr->next, novi)) {
        curr = curr->next;
    }
    novi->next = curr->next;
    curr->next = novi;

    return EXIT_SUCCESS;
}

int jeveci(pozicijaracun prvi, pozicijaracun drugi) {
    return strcmp(prvi->datum, drugi->datum) > 0;
}

int sortartikle(pozicijaartikl glava, pozicijaartikl novi) {
    pozicijaartikl curr = glava;
    while (curr->next && strcmp(curr->next->ime, novi->ime) < 0) {
        curr = curr->next;
    }
    novi->next = curr->next;
    curr->next = novi;

    return EXIT_SUCCESS;
}

int pretrazi(pozicijaracun head, int dani1, int dani2, char* naziv) {
    int ukupna_kolicina = 0;
    float ukupna_cijena = 0.0f;

    pozicijaracun curr = head->next;
    while (curr) {
        int godina, mjesec, dan;
        sscanf(curr->datum, "%d-%d-%d", &godina, &mjesec, &dan);
        int trenutni_dani = ukupnodanaodpocetka(godina, mjesec, dan);

        if (trenutni_dani >= dani1 && trenutni_dani <= dani2) {
            pozicijaartikl artikl = curr->artikli;
            while (artikl) {
                if (strcmp(artikl->ime, naziv) == 0) {
                    ukupna_kolicina += artikl->kolicina;
                    ukupna_cijena += artikl->kolicina * artikl->cijena;
                }
                artikl = artikl->next;
            }
        }
        curr = curr->next;
    }

    printf("Ukupna kolicina %s je %d, a ukupna cijena je %.2f\n", naziv, ukupna_kolicina, ukupna_cijena);
    return EXIT_SUCCESS;
}

int ukupnodanaodpocetka(int godina, int mjesec, int dan) {
    int daniumjesecu[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    
    if (godina % 4 == 0) {
        daniumjesecu[1] = 29;
    }

    int ukupno_dana = (godina - 1) * 365 + (godina - 1) / 4;

    for (int i = 0; i < mjesec - 1; i++) {
        ukupno_dana += daniumjesecu[i];
    }

    ukupno_dana += dan;
    return ukupno_dana;
}
