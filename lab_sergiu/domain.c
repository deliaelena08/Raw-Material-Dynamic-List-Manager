#include <stdlib.h>
#include <string.h>
#include "domain.h"
#define _CRT_SECURE_NO_WARNINGS

materie_prima* creeaza_materie(char* nume, char* producator, int cantitate) {
	materie_prima* materie_creata=malloc(sizeof(materie_prima));
	size_t c = strlen(nume) + 1;
	materie_creata->nume = malloc(sizeof(char) * c);
	strcpy_s(materie_creata->nume, c, nume);
	size_t c2 = strlen(producator)+1;
	materie_creata->producator = malloc(sizeof(char) * c2);
	strcpy_s(materie_creata->producator, c2, producator);
	materie_creata->cantitate = cantitate;
	return materie_creata;
}
void distruge_materie(materie_prima* materie) {
	free(materie->nume);
	free(materie->producator);
	free(materie);
}

materie_prima* creeaza_copie(materie_prima* mat)
{
	return creeaza_materie(mat->nume, mat->producator, mat->cantitate);
}

int validare(materie_prima* mat) {
	if (strlen(mat->nume) == 0)
		return 0;
	if (strlen(mat->producator) == 0)
		return 0;
	if (mat->cantitate < 0)
		return 0;
	return 1;
}