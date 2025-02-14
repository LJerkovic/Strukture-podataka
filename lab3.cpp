#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _person* position;
typedef struct _person {
    char fname[32];
    char lname[32];
    int birth_year;
    position next;
} person;

position create_person(position head, char* fname, char* lname, int birth_year);
int prepend_list(position head, char* fname, char* lname, int birth_year);
int append_list(position head, char* fname, char* lname, int birth_year);
int insert_after(position previous, char* fname, char* lname, int birth_year);
int print_list(position first);
position find_by_lname(position first, char* lname);
position find_last(position head);
position findPrevious(position first, position target);
void delete_person(position head, position target);
int write_to_file(position head, const char* filename);
int read_from_file(position head, const char* filename);
int insert_before(position head, position target, char* fname, char* lname, int birth_year);

int main() {
    char fname1[32], fname2[32], fname3[32], fname4[32];
    char lname1[32], lname2[32], lname3[32], lname4[32],lname5[32];
    int bday1, bday2, bday3, bday4;

    person head = { .fname = "", .lname = "", .next = NULL };

    
    printf("Dodajte element na pocetak liste: \n");
    scanf("%s %s %d", fname1, lname1, &bday1);
    prepend_list(&head, fname1, lname1, bday1);
    printf("Lista nakon dodavanja elementa na pocetak:\n");
    print_list(head.next);

    
    printf("Dodajte element na kraj liste: \n");
    scanf("%s %s %d", fname2, lname2, &bday2);
    append_list(&head, fname2, lname2, bday2);
    printf("Lista nakon dodavanja elementa na kraj:\n");
    print_list(head.next);

    
    printf("Potrazite neko prezime u listi: \n");
    scanf("%s", lname3);
    position target = find_by_lname(head.next, lname3);
    if (target != NULL) {
        printf("Pronađen je element: %s %s %d\n", target->fname, target->lname, target->birth_year);
    }
    else {
        printf("Osoba s prezimenom %s nije pronađena.\n", lname3);
    }

    
    printf("Unesite prezime osobe iza koje želite uneti novu osobu:\n");
    scanf("%s", lname4);
    target = find_by_lname(head.next, lname4);
    if (target != NULL) {
        printf("Unesite ime, prezime i godinu rođenja nove osobe:\n");
        scanf("%s %s %d", fname3, lname3, &bday3);
        insert_after(target, fname3, lname3, bday3);
        printf("Lista nakon umetanja novog elementa iza %s:\n", lname4);
        print_list(head.next);
    }
    else {
        printf("Osoba s prezimenom %s nije pronađena za umetanje.\n", lname4);
    }

    printf("Unesite prezime osobe prije koje želite uneti novu osobu:\n");
    scanf("%s", lname5);
    target = find_by_lname(head.next, lname5);
    if (target != NULL) {
        printf("Unesite ime, prezime i godinu rođenja nove osobe:\n");
        scanf("%s %s %d", fname4, lname4, &bday4);
        insert_before(&head, target, fname4, lname4, bday4);
        printf("Lista nakon umetanja novog elementa prije %s:\n", lname5);
        print_list(head.next);
    }
    else {
        printf("Osoba s prezimenom %s nije pronađena za umetanje.\n", lname5);
    }

    
    printf("Unesite prezime osobe koju želite obrisati iz liste: \n");
    scanf("%s", lname3);
    target = find_by_lname(head.next, lname3);
    if (target != NULL) {
        delete_person(&head, target);
        printf("Lista nakon brisanja osobe %s:\n", lname3);
        print_list(head.next);
    }
    else {
        printf("Osoba s prezimenom %s nije pronađena za brisanje.\n", lname3);
    }

    
    write_to_file(head.next, "lista.txt");
    printf("Lista je upisana u datoteku 'lista.txt'.\n");

    
    person new_head = { .fname = "", .lname = "", .next = NULL };
    read_from_file(&new_head, "lista.txt");
    printf("Lista pročitana iz datoteke:\n");
    print_list(new_head.next);

    return 0;
}

position create_person(position head, char* fname, char* lname, int birth_year) {
    position new_person = (person*)malloc(sizeof(person));
    if (new_person == NULL) {
        printf("Error allocating memory.\n");
        return NULL;
    }
    strcpy(new_person->fname, fname);
    strcpy(new_person->lname, lname);
    new_person->birth_year = birth_year;
    new_person->next = NULL;
    return new_person;
}

int prepend_list(position head, char* fname, char* lname, int birth_year) {
    position new_person = create_person(head, fname, lname, birth_year);
    if (new_person == NULL) {
        return -1;
    }
    new_person->next = head->next;
    head->next = new_person;
    return EXIT_SUCCESS;
}

int append_list(position head, char* fname, char* lname, int birth_year) {
    position new_person = create_person(head, fname, lname, birth_year);
    if (new_person == NULL) {
        return -1;
    }
    position last_person = find_last(head);
    last_person->next = new_person;
    new_person->next = NULL;
    return 0;
}

int print_list(position first) {
    position temp = first;
    while (temp) {
        printf("First name: %s\nLast name: %s\nBirth Year: %d\n", temp->fname, temp->lname, temp->birth_year);
        temp = temp->next;
    }
    return EXIT_SUCCESS;
}

position find_last(position head) {
    position temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    return temp;
}

position find_by_lname(position first, char* lname) {
    position temp = first;
    while (temp) {
        if (strcmp(temp->lname, lname) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

position findPrevious(position first, position target) {
    position temp = first;
    if (first == target) {
        return NULL;
    }
    while (temp->next != NULL && temp->next != target) {
        temp = temp->next;
    }
    return temp;
}

void delete_person(position head, position toDelete) {
    if (head == NULL || toDelete == NULL) {
        return;
    }
    position previous = findPrevious(head, toDelete);
    if (previous != NULL) {
        previous->next = toDelete->next;
        free(toDelete);
    }
}

int insert_after(position previous, char* fname, char* lname, int birth_year) {
    if (previous == NULL) {
        printf("Error: previous position is NULL.\n");
        return -1;
    }
    position new_person = create_person(previous, fname, lname, birth_year);
    if (new_person == NULL) return -1;
    new_person->next = previous->next;
    previous->next = new_person;
    return 0;
}

int write_to_file(position head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return -1;
    }
    position temp = head;
    while (temp != NULL) {
        fprintf(file, "%s %s %d\n", temp->fname, temp->lname, temp->birth_year);
        temp = temp->next;
    }
    fclose(file);
    return 0;
}

int read_from_file(position head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return -1;
    }

    char line[128];
    char fname[32], lname[32];
    int birth_year;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (sscanf(line, "%s %s %d", fname, lname, &birth_year) == 3) {
            append_list(head, fname, lname, birth_year);
        }
        else {
            printf("Invalid line format: %s", line);
        }
    }

    fclose(file);
    return 0;
}

int insert_before(position head, position target, char* fname, char* lname, int birth_year) {
    if (target == NULL) {
        printf("Error: target position is NULL.\n");
        return -1;
    }

    position new_person = create_person(head, fname, lname, birth_year);
    if (new_person == NULL) {
        return -1;
    }

    
    position previous = findPrevious(head, target);

    if (previous == NULL) {
        printf("Error: Target is the head of the list, cannot insert before it directly.\n");
        free(new_person);
        return -1;
    }

    
    new_person->next = target;
    previous->next = new_person;

    return 0;
}

