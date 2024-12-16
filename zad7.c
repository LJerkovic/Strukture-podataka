#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_ime 256

typedef struct direktorij* pozicija;
typedef struct stog* pozicija_stoga;

typedef struct direktorij {
	char ime[max_ime];
	pozicija brat;
	pozicija dijete;
}direktorij;

typedef struct stog {
	pozicija podaci;
	pozicija_stoga sljedeci;
} stog;

pozicija alociraj_memoriju_direktorij();
pozicija_stoga alociraj_memoriju_stog();
int push(pozicija, pozicija_stoga);
pozicija pop(pozicija_stoga);
pozicija napravi_direktorij(pozicija, char*);
pozicija promijeni_u_direktorij(pozicija, pozicija_stoga, char*);
pozicija promijeni_u_prosli(pozicija_stoga);
int ispisi_direktorij(pozicija);
int putanja(pozicija, pozicija_stoga);
int korisnicki_unos(pozicija trenutni, pozicija_stoga glava_stoga);
void obrisi(pozicija);

int main() {
	direktorij c;
	c.brat = NULL;
	c.dijete = NULL;
	strcpy(c.ime, "C:");

	stog glava_stoga;
	glava_stoga.podaci = NULL;
	glava_stoga.sljedeci = NULL;

	push(&c, &glava_stoga);
	korisnicki_unos(&c, &glava_stoga);

	return 0;
}

pozicija alociraj_memoriju_direktorij() {
	pozicija novi = (pozicija)malloc(sizeof(direktorij));
	if (!novi) {
		printf("Ne mogu alocirati memoriju!\n");
		return NULL;
	}
	novi->brat = NULL;
	novi->dijete = NULL;
	return novi;
}

pozicija_stoga alociraj_memoriju_stog() {
	pozicija_stoga novi = (pozicija_stoga)malloc(sizeof(stog));
	if (!novi) {
		printf("Ne mogu alocirati memoriju!\n");
		return NULL;
	}
	return novi;
}

int push(pozicija trenutni, pozicija_stoga glava_stoga) {
	pozicija_stoga novi = alociraj_memoriju_stog();
	if (!novi)
		return -1;

	novi->podaci = trenutni;
	novi->sljedeci = glava_stoga->sljedeci;
	glava_stoga->sljedeci = novi;

	return 0;
}

pozicija pop(pozicija_stoga glava_stoga) {
	if (!glava_stoga->sljedeci)
		return NULL;

	pozicija_stoga temp = glava_stoga->sljedeci;
	pozicija direktorij = temp->podaci;
	glava_stoga->sljedeci = temp->sljedeci;
	free(temp);

	return direktorij;
}

pozicija napravi_direktorij(pozicija trenutni, char* ime) {
	pozicija novi = alociraj_memoriju_direktorij();
	if (!novi)
		return NULL;

	strcpy(novi->ime, ime);
	if (!trenutni->dijete) {
		trenutni->dijete = novi;
	}
	else {
		pozicija temp = trenutni->dijete;
		while (temp->brat)
			temp = temp->brat;
		temp->brat = novi;
	}
	return trenutni;
}

pozicija promijeni_u_direktorij(pozicija trenutni, pozicija_stoga glava_stoga, char* ime) {
	if (!trenutni->dijete)
		return trenutni;

	pozicija temp = trenutni->dijete;
	while (temp) {
		if (strcmp(temp->ime, ime) == 0) {
			push(trenutni, glava_stoga);
			return temp;
		}
		temp = temp->brat;
	}
	return trenutni;
}

pozicija promijeni_u_prosli(pozicija_stoga glava_stoga) {
	return pop(glava_stoga);
}

int ispisi_direktorij(pozicija trenutni) {
	if (!trenutni->dijete) {
		printf("Direktorij je prazan!\n");
		return 0;
	}

	trenutni = trenutni->dijete;
	while (trenutni) {
		printf("%s\n", trenutni->ime);
		trenutni = trenutni->brat;
	}
	return 0;
}

void obrisi(pozicija trenutni) {
	if (!trenutni)
		return;

	obrisi(trenutni->brat);
	obrisi(trenutni->dijete);
	free(trenutni);
}

int putanja(pozicija trenutni, pozicija_stoga glava_stoga) {
	char ispis[max_ime] = "";
	pozicija_stoga temp = glava_stoga->sljedeci;
	while (temp) {
		strcat(ispis, temp->podaci->ime);
		strcat(ispis, "\\");
		temp = temp->sljedeci;
	}
	strcat(ispis, trenutni->ime);
	strcat(ispis, "> ");
	printf("%s", ispis);
	return 0;
}

int korisnicki_unos(pozicija trenutni, pozicija_stoga glava_stoga) {
	char unos[max_ime];
	char naredba[10];
	char ime[max_ime];

	do {
		putanja(trenutni, glava_stoga);
		fgets(unos, max_ime, stdin);
		sscanf(unos, "%s %s", naredba, ime);

		if (strcmp(naredba, "md") == 0) {
			napravi_direktorij(trenutni, ime);
		}
		else if (strcmp(naredba, "cd") == 0) {
			trenutni = promijeni_u_direktorij(trenutni, glava_stoga, ime);
		}
		else if (strcmp(naredba, "cd..") == 0) {
			pozicija prosli = promijeni_u_prosli(glava_stoga);
			if (prosli)
				trenutni = prosli;
		}
		else if (strcmp(naredba, "dir") == 0) {
			ispisi_direktorij(trenutni);
		}
		else if (strcmp(naredba, "exit") == 0) {
			obrisi(trenutni);
		}
		else {
			printf("Nepoznata naredba!\n");
		}
	} while (strcmp(naredba, "exit") != 0);

	return 0;
}
