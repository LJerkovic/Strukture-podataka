#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct drzava* cvor_drzava;
typedef struct  grad* cvor_grad;

typedef struct drzava {

    char ime[20];

    cvor_drzava next;

    cvor_grad head_grad;

}drzava;


typedef struct  grad
{
    char ime_grada[20];
    int br_stan;

    cvor_grad livo, desno;



}grad;

void unesi_drzavu(cvor_drzava, char*, char*);
void print_listu(cvor_drzava);
void inorder(cvor_grad, int);

int ispis(cvor_drzava, char*, int);

cvor_grad unesi_grad(cvor_grad, char*, int);

int main() {


    cvor_drzava head = malloc(sizeof(drzava)); if (!head) return -1;

    head->next = NULL;


    FILE* fp = NULL;

    fp = fopen("drzave.txt", "r"); if (!fp) { printf("greska pri otvarnaju datoteke!"); return -1; }

    char ime_drzave[20];
    char ime_datoteke[20];

    while (fscanf(fp, "%s %s", ime_drzave, ime_datoteke) == 2) {

        unesi_drzavu(head, ime_drzave, ime_datoteke);
    }
    fclose(fp);



    char trazeni[20];
    int br;

    printf("Unesite ime drzave cije gardove zelite pretraziti: "); scanf("%s", trazeni);
    printf("Unesite broj stavnika "); scanf("%d", &br);

    if (!ispis(head, trazeni, br)) {
        printf("Drzava nije proandjena");
    }




}


void unesi_drzavu(cvor_drzava head, char* ime_drzave, char* grad_datoteke) {

    cvor_drzava novi = malloc(sizeof(drzava)); if (!novi) return;

    novi->next = NULL;
    novi->head_grad = NULL;
    strcpy(novi->ime, ime_drzave);

    cvor_drzava curr = head;

    while (curr->next != NULL && (strcmp(novi->ime, curr->next->ime) > 0)) {
        curr = curr->next;
    }

    novi->next = curr->next;

    curr->next = novi;



    FILE* file = NULL;

    file = fopen(grad_datoteke, "r"); if (!file) { printf("Greska u icitavanju gradova"); return; }

    int br;
    char temp[20];



    while (fscanf(file, "%s %d", temp, &br) == 2) {

        novi->head_grad = unesi_grad(novi->head_grad, temp, br);

    }


    fclose(file);




}
void print_listu(cvor_drzava head) {
    cvor_drzava curr = head->next;

    while (curr != NULL) {
        printf("Drzava: %s\n", curr->ime);
        printf("Gradovi:\n");
        inorder(curr->head_grad, 000);
        printf("\n");
        curr = curr->next;
    }
}

void inorder(cvor_grad root, int br) {
    if (!root) return;

    inorder(root->livo, br);
    if (root->br_stan > br)  printf("%s : %d\n", root->ime_grada, root->br_stan);

    inorder(root->desno, br);
}

cvor_grad unesi_grad(cvor_grad root, char* ime_grada, int br_st) {


    if (!root) {

        root = malloc(sizeof(grad)); if (!root) return NULL;
        root->desno = NULL;
        root->livo = NULL;
        strcpy(root->ime_grada, ime_grada);
        root->br_stan = br_st;

    }
    else if (br_st < root->br_stan) {

        root->livo = unesi_grad(root->livo, ime_grada, br_st);

    }
    else if (br_st > root->br_stan) {

        root->desno = unesi_grad(root->desno, ime_grada, br_st);

    }

    return root;

}

int ispis(cvor_drzava head, char* ime_drz, int br) {

    if (!head) return 0;

    cvor_drzava curr = head->next;

    while (curr != NULL && strcmp(curr->ime, ime_drz) != 0) {

        curr = curr->next;

    }

    if (!curr) return 0;

    printf("%s:", curr->ime);
    inorder(curr->head_grad, br);

    return 1;


}
