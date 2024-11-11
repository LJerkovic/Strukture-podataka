#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define BUFFER_SIZE 1024

typedef struct polinom* pozicija;
typedef struct polinom {

    int exp;
    int coef;
    pozicija next;

}polinom;

void sort_unos(pozicija, int, int);
void iscitaj_i_unesi(pozicija, char*);
void ispis(pozicija);
pozicija zbroji_polinome(pozicija, pozicija);
pozicija pomnozi_polinome(pozicija, pozicija);
void IzbrisiSve(pozicija);

int main() {

    pozicija head = (pozicija)malloc(sizeof(polinom)); if (head == NULL) { return -1; }
    head->next = NULL;
    iscitaj_i_unesi(head, "polinom1.txt");
    printf("\nPrvi polinom\n");
    ispis(head);
    printf("\n");


    pozicija head1 = (pozicija)malloc(sizeof(polinom)); if (head1 == NULL) { return -1; }
    head1->next = NULL;
    iscitaj_i_unesi(head1, "polinom2.txt");
    printf("\nDrugi polinom\n");
    ispis(head1);
    printf("\n_____\n");


    pozicija novi = zbroji_polinome(head, head1);
    printf("\nZbrojeni polinomi\n");
    ispis(novi);
    printf("\n");
    IzbrisiSve(novi);
    free(novi);

    pozicija pom = pomnozi_polinome(head, head1);
    printf("\nPomno�eni polinomi\n");
    ispis(pom);
    printf("\n");
    IzbrisiSve(pom);
    free(pom);

    IzbrisiSve(head);
    free(head);

    IzbrisiSve(head1);
    free(head1);

    return 0;
}

void sort_unos(pozicija head, int coef, int exp) {

    pozicija novi = (pozicija)malloc(sizeof(polinom)); if (novi == NULL) { return; }
    novi->exp = exp;
    novi->coef = coef;
    novi->next = NULL;
    pozicija curr = head;

    while (curr->next != NULL && curr->next->exp <= exp) {

        pozicija tmp = curr->next;

        if (tmp->exp == novi->exp) {


            novi->coef = coef + tmp->coef;
            if (novi->coef) {
                novi->next = tmp->next;
                curr->next = novi;

                free(tmp);
            }
            else if (!novi->coef) {
                curr->next = tmp->next; //curr->next=curr->next->next
                free(novi);
                free(tmp);
            }


            return;

        }
        curr = curr->next;
    }

    novi->next = curr->next;
    curr->next = novi;

}

void iscitaj_i_unesi(pozicija head, char* ime_filea) {
    char buffer[BUFFER_SIZE];
    FILE* data = NULL;
    data = fopen(ime_filea,"r");
    {
        if (data == NULL) { return; }
    }

    int exp, coef, offset = 0, numBytes;

    fgets(buffer, BUFFER_SIZE, data);

    while (sscanf(buffer + offset, "%d %d %n,", &coef, &exp, &numBytes) == 2) {
        sort_unos(head, coef, exp);
        offset += numBytes;

    }

    fclose(data);

}

void ispis(pozicija head) {

    pozicija curr = head->next;

    if (curr == NULL) {
        printf("Polinoma nema!!");
        return;
    }

    while (curr != NULL) {

        if (!curr->next) {
            printf("%dx^%d", curr->coef, curr->exp);
        }
        else {
            printf("%dx^%d + ", curr->coef, curr->exp);
        }


        curr = curr->next;
    }

}

pozicija zbroji_polinome(pozicija head1, pozicija head2) {

    pozicija novi = (pozicija)malloc(sizeof(polinom)); {
        if (novi == NULL) { return NULL; }
    }

    novi->next = NULL;


    pozicija curr1 = head1->next;
    pozicija curr2 = head2->next;
    while (curr1 != NULL) {

        sort_unos(novi, curr1->coef, curr1->exp);
        curr1 = curr1->next;
    }



    while (curr2 != NULL) {

        sort_unos(novi, curr2->coef, curr2->exp);
        curr2 = curr2->next;
    }

    return novi;

}


pozicija pomnozi_polinome(pozicija head1, pozicija head2) {

    pozicija novi = (pozicija)malloc(sizeof(polinom)); {
        if (novi == NULL) { return NULL; }
    }

    novi->next = NULL;

    pozicija curr1 = head1->next;

    while (curr1 != NULL) {

        pozicija curr2 = head2->next;

        while (curr2 != NULL) {
            int exp, coef;
            exp = curr1->exp + curr2->exp;
            coef = curr1->coef * curr2->coef;

            sort_unos(novi, coef, exp);

            curr2 = curr2->next;
        }



        curr1 = curr1->next;
    }

    return novi;

}

void IzbrisiSve(pozicija head) {
    pozicija temp;

    while (head->next != NULL) {
        temp = head->next;
        head->next = head->next->next;
        free(temp);
    }
}
