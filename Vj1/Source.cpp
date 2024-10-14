#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#define ERROR_OF 1
#define MAX 1024
#define MAX_BODOVA 100

typedef struct
{
	char ime[50];
	char prezime[50];
	int bodovi;
} Student;

int NumberOfRows(const char *fileName);
Student *LoadStudents(const char *fileName, int brojStudenata);
void IspisiStudente(Student *studenti, int brojStudenata);

int main()
{
	const char *fileName = "imedat.txt";
	int numOfRows = NumberOfRows(fileName);

	if (numOfRows == -1)
	{
		printf("Pogreška pri otvaranju datoteke.\n");
		return ERROR_OF;
	}

	Student *studenti = LoadStudents(fileName, numOfRows);

	if (studenti == NULL)
	{
		printf("Pogreška pri učitavanju studenata.\n");
		return ERROR_OF;
	}

	IspisiStudente(studenti, numOfRows);

	free(studenti);

	return 0;
}

int NumberOfRows(const char *fileName)
{
	FILE *fp = fopen(fileName, "r");
	if (!fp)
	{
		return -1;
	}

	int numOfRows = 0;
	char buffer[MAX] = {};

	while (fgets(buffer, MAX, fp))
	{
		numOfRows++;
	}

	fclose(fp);
	return numOfRows;
}

Student *LoadStudents(const char *fileName, int brojStudenata)
{
	FILE *fp = fopen(fileName, "r");
	if (!fp)
	{
		return NULL;
	}

	Student *studenti = (Student *)malloc(brojStudenata * sizeof(Student));
	if (studenti == NULL)
	{
		fclose(fp);
		return NULL;
	}

	for (int i = 0; i < brojStudenata; i++)
	{
		fscanf(fp, "%s %s %d", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);
	}

	fclose(fp);
	return studenti;
}

void IspisiStudente(Student *studenti, int brojStudenata)
{
	for (int i = 0; i < brojStudenata; i++)
	{
		double relativniBodovi = (double)studenti[i].bodovi / MAX_BODOVA * 100;
		printf("Ime: %s, Prezime: %s, Apsolutni bodovi: %d, Relativni bodovi: %.2f%%\n",
			   studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, relativniBodovi);
	}
}