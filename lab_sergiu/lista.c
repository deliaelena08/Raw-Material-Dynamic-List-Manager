#include "domain.h"
#include <stdlib.h>
#include "lista.h"
#include <stdio.h>
ListaMaterii* creeazaVid(DestroyFunction f)
{/*Crezaza o lista fara elemente
 returneaza lista
 */
	ListaMaterii* nou = malloc(sizeof(ListaMaterii));
	nou->capacitate = 1;
	nou->mats = malloc(sizeof(ElemType) * nou->capacitate);
	nou->lung = 0;
	nou->fnct = f;
	return nou;
}

ElemType get(ListaMaterii* l, int poz)
{
	return l->mats[poz];
}


void adaugaSf(ListaMaterii* l, ElemType materie)
{
	if (l->capacitate <= l->lung) {
		ElemType* aux = malloc(sizeof(ElemType) * (l->capacitate + 5));
		for (int i = 0; i < l->lung; i++)
			aux[i] = l->mats[i];
		free(l->mats);
		l->mats = aux;
		l->capacitate += 5;
	}
	l->mats[l->lung] = materie;
	l->lung++;
	
}

int lungime(ListaMaterii* l) {
	return l->lung;
}
void distruge_lista(ListaMaterii* l) {
	for (int i = 0; i < l->lung; i++) {
		l->fnct(l->mats[i]);
	}
	l->lung = 0;
	free(l->mats);
	free(l);
}

void distrugere_lista_materii(ListaMaterii* l)
{
	distruge_lista(l);
}

ElemType delete(ListaMaterii* l, int poz)
{
	ElemType m = l->mats[poz];
	for (int i = poz; i<l->lung-1; i++)
	{
		l->mats[i] = l->mats[i + 1];
	}
	l->lung--;
	return m;
}

ListaMaterii* copylist(ListaMaterii* l,CopyFct copyfct)
{
	ListaMaterii* rez = creeazaVid(l->fnct);
	for (int i = 0; i < lungime(l); i++)
	{
		ElemType p = get(l, i);
		adaugaSf(rez, copyfct(p));
	}
	return rez;
}
