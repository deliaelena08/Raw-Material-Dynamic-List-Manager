#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "teste.h"
#include "service.h"
#include <crtdbg.h>
#include <stdlib.h>
#define _CRTDBG_MAP_ALLOC

void print_dupa_cant_min(ListaMaterii* l, int cant_min) {
	/*printeaza tote materiile care au cantitatea mai mica decat cant_min

	*/
	for (int i = 0; i < l->lung; i++)
	{
		materie_prima* m = l->mats[i];
		if (m->cantitate < cant_min)
			printf("Nume %s\nProducator %s\nCantitate %d\n", m->nume, m->producator, m->cantitate);
		printf("\n");
	}
}

void print_dupa_lungime(ListaMaterii* l, int lg)
{
	for (int i = 0; i < l->lung; i++)
	{
		materie_prima* m = l->mats[i];
		if (strlen(m->producator)==lg)
			printf("Nume %s\nProducator %s\nCantitate %d\n\n", m->nume, m->producator, m->cantitate);
	}
}

void print_dupa_litera(ListaMaterii* l, char litera) {
	/*printeaza toate materiile care au numele care incepe cu o litera specificata
	* litera->litera cu care sa inceapa numele
	* l->lista
	*/
	for (int i = 0; i < l->lung; i++) {

		materie_prima* m = l->mats[i];
		if (m->nume[0] == litera)
			printf("Nume %s\nProducator %s\nCantitate %d\n", m->nume, m->producator, m->cantitate);
		printf("\n");
	}
}
void undoui(ManagerMaterii* store)
{
	int succesful = undo(store);
	if (succesful)
		printf("undo realizat cu succes!\n");
	else
		printf("nu se mai poate face undo\n");
}

void print_all(ListaMaterii* l) {
	/*Da print la toate materiile din lista
	* l -> lista
	*/
	for (int i = 0; i < l->lung; i++) {
		materie_prima* m = get(l, i);
		printf("Nume %s\nProducator %s\nCantitate %d\n\n", m->nume, m->producator, m->cantitate);
	}
}

void adaugabydefault(ManagerMaterii* store)
{
	adaugare_materie(store, "aluminiu", "ALex", 200);
	adaugare_materie(store, "cupru", "Ciprian", 1000);
	adaugare_materie(store, "uraniu", "Maria", 100);
	adaugare_materie(store, "quartz", "Cristina", 10);
}

void interfata() {
	/*Start aplicatie*/
	ManagerMaterii store = createManager();
	adaugabydefault(&store);
	while (1) {
		printf("\n1.Adauga\n2.Modificare\n3.Stergere\n4.Filtrare\n5.Ordonare\n6.Iesire\n7.Undo\n8.Afisare lista\nAlegeti o optiune:\n");
		int optiune;
		scanf_s("%d", &optiune);
		switch (optiune)
		{
		case 1:
		{
			printf("Introduceti un nume\n");
			char nume[20];
			scanf_s("%s", nume, 20);
			printf("Introduceti un producator\n");
			char producator[20];
			scanf_s("%s", producator, 20);
			printf("Introduceti o cantitate\n");
			int cantitate;
			scanf_s("%d", &cantitate);
			if (este_deja_in_lista(&store, nume) == 0) {
				int val = adaugare_materie(&store, nume, producator, cantitate);
				if (val == 1)
					printf("adaugare cu succes!\n\n");
				else
					printf("date invalide:( \n\n");
			}
			else
			{
				materie_prima* m = store.materii->mats[search_by_name(&store, nume)];
				m->cantitate = cantitate;
			}
			print_all(store.materii);
			//printf(m->nume);

			break;
		}
		case 2: {
			char nume_de_modificat[20], producator_de_modificat[20];

			printf("Introduceti un nume\n");
			scanf_s("%s", nume_de_modificat, 20);
			printf("Introduceti noul producator\n");

			scanf_s("%s", producator_de_modificat, 20);
			printf("Introduceti noua cantitate\n");
			int cantitate_de_modificat;
			scanf_s("%d", &cantitate_de_modificat);
			if (este_deja_in_lista(&store, nume_de_modificat) == 0) {
				printf("Introduceti un nume deja existent");
			}
			else {
				ListaMaterii* undo = copylist(store.materii, creeaza_copie);
				adaugaSf(store.undolist, undo);
				materie_prima* m = store.materii->mats[search_by_name(&store, nume_de_modificat)];
				m->cantitate = cantitate_de_modificat;
				producator_de_modificat[19] = '\0';
				strcpy(m->producator, producator_de_modificat);
			}
			break;
		}
		case 3: {
			printf("Introduceti un nume\n");
			char nume_de_sters[20];
			scanf_s("%s", nume_de_sters, 20);
			stergere_dupa_index(&store, nume_de_sters);
			print_all(store.materii);
			break;
		}
		case 4: {
			int opt;
			printf("1.Dupa litera numelui unei materii\n2.Dupa cantitate\n3.Dupa lungimea numelui producatorului\nIntroduceti optiunea dorita: \n");
			scanf_s("%d", &opt);
			if (opt == 1) {

				printf("Introduceti litera\n");
				char litera_inceput[2];
				scanf_s("%s", litera_inceput, 2);
				print_dupa_litera(store.materii, litera_inceput[0]);
				break;
			}
			else if (opt == 2) {
				printf("Introduceti cantitatea maxima\n");
				int cant_max;
				scanf_s("%d", &cant_max);
				print_dupa_cant_min(store.materii, cant_max);
				break;
			}
			else if (opt == 3) {
				printf("Introduceti lungimea dorita\n");
				int lung;
				scanf_s("%d", &lung);
				print_dupa_lungime(store.materii, lung);
			}
		}
		case 5: {
			int opt;
			printf("1.Dupa cantitate\n2.Dupa nume\n3.Dupa 2 criterii\n");
			scanf_s("%d", &opt);
			if (opt == 1) {
				ListaMaterii* undo = copylist(store.materii, creeaza_copie);
				adaugaSf(store.undolist, undo);
				ListaMaterii* lista_ord = ordoneaza_dupa_orice(&store,compara_cantitate_crescatoare);
				print_all(lista_ord);
				distruge_lista(lista_ord);
				break;
			}
			else if (opt == 2) {
				ListaMaterii* undo = copylist(store.materii, creeaza_copie);
				adaugaSf(store.undolist, undo);
				ListaMaterii* lista_ord_2 = ordoneaza_dupa_orice(&store, compara_nume_crescatoare);
				print_all(lista_ord_2);
				distruge_lista(lista_ord_2);
				break;
			}
			else if (opt == 3)
			{
				ListaMaterii* undo = copylist(store.materii, creeaza_copie);
				adaugaSf(store.undolist, undo);
				ListaMaterii* lista_ord_3 = ordoneaza_dupa_2(&store,compara_cantitate_crescatoare,compara_nume_crescatoare);
				print_all(lista_ord_3);
				distruge_lista(lista_ord_3);
				break;
			}
		}
		case 6: {
			goto iesire;
		}
		case 7:
			undoui(&store);
			break;
		case 8:
			print_all(store.materii);
		default:
			break;
		}
	}
iesire:;
	distruge_lista(store.materii);
}

int main() {
	run_tests();
	interfata();
	_CrtDumpMemoryLeaks();
	return 0;
}