#include "lista.h"
#include "domain.h"
#include "service.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include<stdio.h>

void test_stergere() {
	ListaMaterii* l = creeazaVid(distruge_materie);
	adaugaSf(l, creeaza_materie("ceva", "altceva", 200));
	adaugaSf(l, creeaza_materie("cv", "altcv", 500));
	adaugaSf(l, creeaza_materie("cev", "altc", 300));
	materie_prima* m0=delete(l, 0);
	distruge_materie(m0);
	assert(lungime(l) == 2);
	materie_prima* m = l->mats[0];
	materie_prima* m2 =l->mats[1];
	assert(strcmp(m->nume, "cv") == 0);
	assert(strcmp(m2->nume, "cev") == 0);
	distruge_lista(l);
}
void test_search() {
	ManagerMaterii store = createManager();
	adaugaSf(store.materii, creeaza_materie("ceva", "altceva", 200));
	adaugaSf(store.materii, creeaza_materie("cv", "altcv", 500));
	assert(search_by_name(&store, "cv") == 1);
	assert(search_by_name(&store, "ceva") == 0);
	assert(search_by_name(&store, "cev") == -1);
	distruge_manager(&store);
}
void testAdauga()
{
	ListaMaterii* l = creeazaVid(distruge_materie);
	assert(lungime(l) == 0);
	materie_prima* m = creeaza_materie("ceva", "altceva", 200);
	adaugaSf(l,m);
	assert(lungime(l) == 1);
	adaugaSf(l, creeaza_materie("cv", "altcv", 500));
	assert(lungime(l) == 2);
	assert(m->cantitate == 200);
	distruge_lista(l);
}

void test_deja_lista() {
	ManagerMaterii store = createManager();
	adaugaSf(store.materii, creeaza_materie("ceva", "altceva", 200));
	adaugaSf(store.materii, creeaza_materie("cv", "altcv", 100));
	assert(este_deja_in_lista(&store, "ceva") != 0);
	assert(este_deja_in_lista(&store, "cev") == 0);
	distruge_manager(&store);
}

void populate(ManagerMaterii* store)
{
	int succesful = adaugare_materie(store, "ceva", "altceava", 200);
	assert(succesful == 1);
	int succesful1=adaugare_materie(store,"cv","altcv",100);
	assert(succesful1 == 1);
}
void test_ordoneaza() {
	ManagerMaterii store = createManager();
	populate(&store);
	assert(lungime(store.materii) == 2);

	ListaMaterii* l1= ordoneaza_cantitate(&store);
	materie_prima* m01 = get(l1, 0);
	assert(m01->cantitate == 100);

	ListaMaterii* l2 = ordoneaza_nume(&store);
	materie_prima* m02 = get(l2, 0);
	assert(m02->cantitate == 100);

	ListaMaterii* l3 =ordoneaza_dupa_orice(&store, compara_cantitate_crescatoare);
	materie_prima* m03 = get(l3, 1);
	assert(m03->cantitate == 200);

	ListaMaterii* l4 = ordoneaza_dupa_orice(&store, compara_nume_crescatoare);
	materie_prima* m04 = get(l4, 0);
	assert(m04->cantitate == 200);

	int succesful = adaugare_materie(&store, "aur", "mihai", 100);
	int succesful1 = adaugare_materie(&store, "auriu", "liviu", 200);
	assert(succesful == 1);
	assert(succesful1 == 1);
	ListaMaterii* l5 = ordoneaza_dupa_2(&store, compara_cantitate_crescatoare, compara_nume_crescatoare);
	materie_prima* m05 = get(l5, 0);
	assert(strcmp(m05->nume,"aur")==0);


	distruge_lista(l1);
	distruge_lista(l2);
	distruge_lista(l3);
	distruge_lista(l4);
	distruge_lista(l5);
	distruge_manager(&store);
}

void test_validare() {
	materie_prima* mat = creeaza_materie("abc", "2", -1);
	assert(validare(mat) == 0);
	materie_prima* mat2 = creeaza_materie("", "2", -1);
	assert(validare(mat2) == 0);
	materie_prima* mat3 = creeaza_materie("abc", "", -1);
	assert(validare(mat3) == 0);
	distruge_materie(mat);
	distruge_materie(mat2);
	distruge_materie(mat3);
}

void testundo()
{
	ManagerMaterii store = createManager();
	assert(adaugare_materie(&store, "metal", "maricica", 100) == 1);
	assert(este_deja_in_lista(&store, "metal") == 1);
	assert(stergere_dupa_index(&store, "metal") == 1);
	undo(&store);
	assert(lungime(store.materii) == 1);
	undo(&store);
	int moreundo = undo(&store);
	assert(moreundo == 0);
	distruge_manager(&store);

}

void testlistedeliste()
{
	ListaMaterii* m1 = creeazaVid(distruge_materie);
	ListaMaterii* m2 = creeazaVid(distruge_materie);
	ListaMaterii* undol = creeazaVid(distrugere_lista_materii);
	adaugaSf(m1, creeaza_materie("metal", "marinel", 2000));
	adaugaSf(m1, creeaza_materie("aur", "hagi", 20));
	adaugaSf(undol, m1);
	assert(lungime(undol) == 1);
	adaugaSf(undol, m2);
	assert(lungime(undol) == 2);
	distruge_lista(undol);
}

void run_tests() {
	testAdauga();
	test_search();
	test_deja_lista();
	test_stergere();
	test_ordoneaza();
	test_validare();
	testundo();
	testlistedeliste();
}