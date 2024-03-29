#include "lista.h"
#include "string.h"
#include "service.h"
#include <stdlib.h>

ManagerMaterii createManager()
{
	ManagerMaterii store;
	store.materii = creeazaVid(distruge_materie);
	store.undolist = creeazaVid(distruge_lista);
	return store;
}


int adaugare_materie(ManagerMaterii* store, char* nume, char* producator, int cantitate)
{
	materie_prima* m = creeaza_materie(nume, producator, cantitate);
	int val = validare(m);
	if (!val)
	{
		distruge_materie(m);
		return 0;
	}
	ListaMaterii* undo = copylist(store->materii, creeaza_copie);
	adaugaSf(store->materii, m);
	adaugaSf(store->undolist, undo);
	return 1;
}

int este_deja_in_lista(ManagerMaterii* store, char* nume) {
	for (int i = 0; i < store->materii->lung; i++) {
		materie_prima* m = get(store->materii,i);
		//printf(m->nume);
		if (strcmp(m->nume, nume) == 0)
			return 1;
	}
	return 0;
}
int search_by_name(ManagerMaterii* store, char* nume) {
	for (int i = 0; i < store->materii->lung; i++) {
		materie_prima* m = get(store->materii, i);
		if (strcmp(m->nume, nume) == 0)
			return i;
	}
	return -1;
}

int stergere_dupa_index(ManagerMaterii* store, char* nume) {
	int poz = search_by_name(store, nume);
	if (poz != -1)
	{
		ListaMaterii* undo = copylist(store->materii, creeaza_copie);
		adaugaSf(store->undolist, undo);
		materie_prima* m = delete(store->materii, poz);
		distruge_materie(m);
		return 1;
	}
	else
		return 0;
}

ListaMaterii* ordoneaza_nume(ManagerMaterii* store) {
	ListaMaterii* lista_ord = creeazaVid(distruge_materie);
	for (int i = 0; i < store->materii->lung; i++)
		adaugaSf(lista_ord, creeaza_copie(store->materii->mats[i]));

	for (int i = 0; i < lista_ord->lung - 1; i++) {
		for (int j = i + 1; j < lista_ord->lung; j++) {
			materie_prima* m1 = lista_ord->mats[i];
			materie_prima* m2 = lista_ord->mats[j];
			if (strcmp(m2->nume,m1->nume) > 0) {
				// Schimba pozițiile elementelor în listă
				materie_prima* aux = lista_ord->mats[j];
				lista_ord->mats[j] = lista_ord->mats[i];
				lista_ord->mats[i] = aux;
			}
		}
	}

	return lista_ord;
}
ListaMaterii* ordoneaza_cantitate(ManagerMaterii* store) {
	ListaMaterii* lista_ord = creeazaVid(distruge_materie);
	for (int i = 0; i < store->materii->lung; i++)
		adaugaSf(lista_ord, creeaza_copie(store->materii->mats[i]));

	for (int i = 0; i < lista_ord->lung - 1; i++) {
		for (int j = i + 1; j < lista_ord->lung; j++) {
			materie_prima* m1 = lista_ord->mats[i];
			materie_prima* m2 = lista_ord->mats[j];
			if (m2->cantitate <m1->cantitate) {
				materie_prima* aux = lista_ord->mats[j];
				lista_ord->mats[j] = lista_ord->mats[i];
				lista_ord->mats[i] = aux;
			}
		}
	}

	return lista_ord;
}

void distruge_manager(ManagerMaterii* store)
{

	distruge_lista(store->materii);
	distruge_lista(store->undolist);
}
ListaMaterii* ordoneaza_dupa_2(ManagerMaterii* store, int (*f1)(materie_prima*, materie_prima*), int (*f2)(materie_prima*, materie_prima*)) {
	ListaMaterii* lista_ord = creeazaVid(distruge_materie);
	for (int i = 0; i < store->materii->lung; i++)
		adaugaSf(lista_ord, creeaza_copie(store->materii->mats[i]));
	for (int i = 0; i < lista_ord->lung - 1; i++) {
		for (int j = i + 1; j < lista_ord->lung; j++) {
			materie_prima* m1 = get(lista_ord, i);
			materie_prima* m2 = get(lista_ord, j);
			if ((*f1)(lista_ord->mats[j], lista_ord->mats[i])) {
				materie_prima* temp = lista_ord->mats[j];
				lista_ord->mats[j] = lista_ord->mats[i];
				lista_ord->mats[i] = temp;
			}
			else
			{
				if (m1->cantitate == m2->cantitate)
				{
					if (((*f2)(lista_ord->mats[j], lista_ord->mats[i])))
					{
						materie_prima* temp = lista_ord->mats[j];
						lista_ord->mats[j] = lista_ord->mats[i];
						lista_ord->mats[i] = temp;
					}
				}
			}
		}
	}
	return lista_ord;
}
ListaMaterii* ordoneaza_dupa_orice(ManagerMaterii* store, int (*f)(materie_prima*, materie_prima*)) {
	ListaMaterii* lista_ord = creeazaVid(distruge_materie);
	for (int i = 0; i < store->materii->lung; i++)
		adaugaSf(lista_ord, creeaza_copie(store->materii->mats[i]));
	for (int i = 0; i < lista_ord->lung - 1; i++) {
		for (int j = i + 1; j < lista_ord->lung; j++) {
			if ((*f)(lista_ord->mats[j], lista_ord->mats[i])) {
				materie_prima* temp = lista_ord->mats[j];
				lista_ord->mats[j] =lista_ord->mats[i];
				lista_ord->mats[i] = temp;
			}
		}
	}
	return lista_ord;
}
int compara_cantitate_crescatoare(materie_prima* a, materie_prima* b) {
	return a->cantitate <= b->cantitate;
}
int compara_nume_crescatoare(materie_prima* a, materie_prima* b) {
	return (strcmp(a->nume, b->nume) < 0);
}

int undo(ManagerMaterii* store)
{
	if (lungime(store->undolist) == 0)
		return 0;
	ListaMaterii* list = delete(store->undolist, store->undolist->lung - 1);
	distruge_lista(store->materii);
	store->materii = list;
	return 1;
}