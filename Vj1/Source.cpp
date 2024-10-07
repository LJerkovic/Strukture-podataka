#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#define ERROR_OF 1
#define MAX 1024


int NumberOfRows(const char*);

int main() {
	 
	int numOfRows = NumberOfRows("imedat.txt");

 
	



	return 0;


}

int NumberOfRows(const char*) {
	FILE *fp = NULL;
	int numOfRows = 0;
	char buffer[MAX] = {};
	fp = fopen(fileName, "r");
	if (!fp) {

		return -1;
	}
	while (!feof(fp)) {
		fgets(buffer, MAX, fp);
		numOfRows++;
	}

}
