#pragma once
#include "domain.h"


typedef void* ElemType;
typedef void (*DestroyFunction)(ElemType);
typedef ElemType(*CopyFct)(ElemType);

typedef struct {
	ElemType* mats;
	int lung;
	int capacitate;
	DestroyFunction fnct;
}ListaMaterii;

ListaMaterii* creeazaVid(DestroyFunction f);
void adaugaSf(ListaMaterii* l, ElemType materie);
/*Adauga o materie la finalul unui liste
	* materie->materia care se vrea adaugata
	* l- lista unde se vrea adaugata
	*/
int lungime(ListaMaterii* l);
/*Returneaza lungimea unei liste
	*/
void distruge_lista(ListaMaterii* l);
/*Distruge o lista(dealocare)
*/
void distrugere_lista_materii(ListaMaterii* l);
ElemType get(ListaMaterii* l, int poz);
ElemType delete(ListaMaterii* l, int poz);
ListaMaterii* copylist(ListaMaterii* l,CopyFct copyfct);