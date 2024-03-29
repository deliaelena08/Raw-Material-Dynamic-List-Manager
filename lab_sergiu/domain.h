#pragma once
typedef struct {
	char* nume;
	char* producator;
	int cantitate;
}materie_prima;
materie_prima* creeaza_materie(char* nume, char* producator, int cantitate);

/* Creeaza o materie cu nume,producator,cantitate
	* Returneaza materia
	*/
void distruge_materie(materie_prima* materie);
/*Distruge o materie(dealocare)
*/
int validare(materie_prima* mat);
/*Verifica daca datele pentru o materie sunt valide
* returneaza -1 daca nu e bine,0 altfel
*/
materie_prima* creeaza_copie(materie_prima* mat);
