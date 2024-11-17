#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


typedef struct cvor* position;
typedef struct cvor {

	int broj;
	position next;

}cvor;

int dodajelement(position head, int a);
int ucitaj(const char* filename, position head);
int odradioperaciju(position head, char operacija);
void ispis(position head);

int main() {

	position head = (position)malloc(sizeof(cvor));
	if (head == NULL) {
		printf("Greska prilikom alokacije\n");
		return -1;
	}
	head->next = NULL;

	ucitaj("postfiks.txt", head);
	ispis(head);




	return 0;
}

int dodajelement(position head, int a) {
	position novi = (position)malloc(sizeof(cvor));
	if (novi == NULL) {
		printf("Greska u alokaciji\n");
		return -1;
	}
	novi->broj = a;
	novi->next = head->next;
	head->next = novi;

	return EXIT_SUCCESS;
}

int ucitaj(const char* filename, position head) {

	FILE* fh = NULL;
	fh = fopen(filename, "r");
	if (fh == NULL) {
		printf("Greska u otvaranju\n");
		return -1;
	}
	char buffer[1024];
	int number;
	int bytes;
	char operacija;
	int offset = 0;
	fgets(buffer, sizeof(buffer), fh);
	while (1) {
		if (sscanf(buffer + offset, "%d %n", &number,&bytes) == 1) {
			dodajelement(head, number);
			offset = offset + bytes;
		}
		else if (sscanf(buffer + offset, "%c%n", &operacija, &bytes) == 1) {
			offset = offset + bytes;
			odradioperaciju(head,operacija);

		}
		else {
			break;
		}
		
	}

	return EXIT_SUCCESS;
}

int odradioperaciju(position head, char operacija) {

	position curr = head->next;
	if (curr == NULL || curr->next == NULL) {
		printf("Nema dovoljno elemenata\n");
		return -1;
	}
	if (operacija == '+') {
		curr->next->broj += curr->broj;
		head->next = head->next->next;
		free(curr);
	}
	else if (operacija == '-') {
		curr->next->broj -= curr->broj;
		head->next = head->next->next;
		free(curr);

	}
	else if (operacija == '*') {
		curr->next->broj *= curr->broj;
		head->next = head->next->next;
		free(curr);
	}
	else {
		return -1;
	}
	return EXIT_SUCCESS;
}

void ispis(position head) {
	position curr = head->next;
	while (curr != NULL) {
		printf("%d", curr->broj);
		curr = curr->next;

	}
	return EXIT_SUCCESS;
}
