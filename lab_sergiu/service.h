#pragma once
#include "lista.h"
#include <stdlib.h>

typedef struct {
	ListaMaterii* materii;
	ListaMaterii* undolist;
}ManagerMaterii;

ManagerMaterii createManager();

int adaugare_materie(ManagerMaterii* store, char* nume, char* producator, int cantitate);
int este_deja_in_lista(ManagerMaterii* store, char* nume);
/*Verifica daca o materie este in lista(dupa un nume)
	* l->pointer la lista
	* nume->pointer la nume
	* Returneaza 1 daca este,0 altfel
	*/
int search_by_name(ManagerMaterii* store, char* nume);
/*Gaseste indexul la care se afla o materie cu un nume dat in lista
	* l->pointer la lista
	* nume->pointer la nume
	* Returneaza pozitia in lista daca gaseste,-1 altfel
	*/
int stergere_dupa_index(ManagerMaterii* store,char* nume);
/*Sterge un element din lista,de la index specificat
* l-lista din care se vrea sters
* index->indexul unde se afla elementul viitor sters
*
*/
ListaMaterii* ordoneaza_dupa_2(ManagerMaterii* store, int (*f1)(materie_prima*, materie_prima*), int (*f2)(materie_prima*, materie_prima*));
/*
Ordoneaza materiile dupa 2 criterii: nume apoi cantitate
Daca numele dunt egale atunci compara dupa cantitate
Returneaza o lista cu elem ord
*/
ListaMaterii* ordoneaza_nume(ManagerMaterii* store);
/*Ordoneaza materiile din lista dupa nume
* Returneaza o lista cu elem ord
*/
ListaMaterii* ordoneaza_cantitate(ManagerMaterii* store);
/*Ordoneaza materiile din lista dupa cantitate
	* Returneaza o lista cu elem ord
	*/
ListaMaterii* ordoneaza_dupa_orice(ManagerMaterii* store, int (*f)(materie_prima*, materie_prima*));
int compara_cantitate_crescatoare(materie_prima* a, materie_prima* b);
int compara_nume_crescatoare(materie_prima* a, materie_prima* b);
void distruge_manager(ManagerMaterii* store);
int undo(ManagerMaterii* store);