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
int insert_after(position previous,char *fname, char *lname,int birth_year);
int print_list(position first);
position find_by_lname(position first, char* lname);
position find_last(position head);
position findPrevious(position first, position target);
void delete_person(position head, position target);
//sortiranje se ne trazi
+



int main() {
    char fname1[32], fname2[32];
    char lname1[32], lname2[32], lname3[32];
    int bday1, bday2;
	char osoba[32];

    person head = { .fname = "", .lname = "", .next = NULL };

    printf("Dodajte element na pocetak liste: \n");
    scanf("%s %s %d", fname1, lname1, &bday1);
    prepend_list(&head, fname1, lname1, bday1);

    printf("Lista sad izgleda ovako: \n");
    print_list(head.next);

    printf("Dodajte element na kraj liste: \n");
    scanf("%s %s %d", fname2, lname2, &bday2);
    append_list(&head, fname2, lname2, bday2);

    printf("Lista nakon dodavanja na kraj izgleda ovako: \n");
    print_list(head.next);

    printf("Potrazite neko prezime iz liste: \n");
    scanf("%s", lname3);
    position target = find_by_lname(head.next, lname3);
    if (target != NULL) {
        printf("Pronađen je element u listi: %s %s %d\n", target->fname, target->lname, target->birth_year);
    }
    else {
        printf("Osoba s prezimenom %s nije pronađena.\n", lname3);
    }

    printf("Unesite prezime osobe za brisanje: \n");
    scanf("%s", lname3);
    target = find_by_lname(head.next, lname3);
    if (target != NULL) {
        delete_person(&head, target);
        printf("Osoba je obrisana. Lista sada izgleda ovako: \n");
        print_list(head.next);
    }
    else {
        printf("Osoba s prezimenom %s nije pronađena.\n", lname3);
    }

	printf("Unesite prezime osobe iza koje zelite unijeti novu:\n");
	scanf("%s", osoba);
	
	position target = find_by_lname(head.next, osoba);
	if (target != NULL) {
		insert_after(target);
	}

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

int insert_after(position previous) {
	if (previous = NULL) {
		printf("Greska");
		return -1;
	}
	char fname[32];
	char lname[32];
	int birth_year;

	printf("Unesite ime nove osobe:\n");
	scanf("%s", fname);
	printf("Unesite preziem\n");
	scanf("%s", lname);
	printf("Unesite datum rodjenja:\n");
	scanf("%d", &birth_year);
	position new_person = create_person(previous, fname, lname, birth_year);
	if (new_person == NULL)return -1;
	new_person->next = previous->next;
	previous->next = new_person;



	return 0;

}
