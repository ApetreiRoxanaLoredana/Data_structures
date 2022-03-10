#include "Multime.h"
#include "IteratorMultime.h"
#include <iostream>

using namespace std;

//o posibila relatie
bool rel(TElem e1, TElem e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}


Multime::Multime() {
	/* de adaugat */
	// Complexitate: θ(n)

	capacitate = 100000;
	dimensiune = 0;

	element = new TElem[capacitate];
	stanga = new int[capacitate];
	dreapta = new int[capacitate];
	parinti = new int[capacitate];
	radacina = NULL_TELEM;

	// Complexitate: θ(n)
	init_spatiu_liber();
	prim_liber = 0;
}


bool Multime::adauga(TElem elem) {
	/* de adaugat */
	// Complexitate: O(h)

	//daca lista e vida
	if (radacina == NULL_TELEM) 
	{
		radacina = aloca();
		element[radacina] = elem;
		stanga[radacina] = dreapta[radacina] = parinti[radacina] = NULL_TELEM;
		dimensiune++;
		return true;
	}
	//cautam pozitia unde trebuie inserat (parintele)
	int poz = cauta_poz(elem); // Complexitate: O(n)
	//daca elementul exista deja
	if (element[poz] == elem)
		return false;
	
	//daca nu exista
	int poz_nou = aloca();

	//daca respecta relatia va fi inserat in partea stanga a parintelui, altfel in dreapta
	if (rel(elem, element[poz])) 
		stanga[poz] = poz_nou;
	else 
		dreapta[poz] = poz_nou;

	element[poz_nou] = elem;
	stanga[poz_nou] = dreapta[poz_nou] = NULL_TELEM;
	parinti[poz_nou] = poz;
	dimensiune++;
	return true;
}


bool Multime::sterge(TElem elem) {
	/* de adaugat */
	// Complexitate: O(h)

	//daca arborele e vid
	if (radacina == NULL_TELEM)
		return false;

	//cautam pozitia elementului
	int poz = cauta_poz(elem); // Complexitate: O(h)
	//daca nu a gasit elementul
	if (element[poz] != elem) 
		return false;

	//daca a gasit elementul
	//CAZUL 1: daca nodul e frunza
	if (stanga[poz] == NULL_TELEM && dreapta[poz] == NULL_TELEM)
	{
		//daca a ramas doar radacina
		if (dimensiune == 1)
			radacina = NULL_TELEM;
		else
			refa_legatura(poz, parinti[poz], NULL_TELEM);
	}
	else 
		//CAZUL 2: daca are doi fii 
		if (stanga[poz] != NULL_TELEM && dreapta[poz] != NULL_TELEM)
		{
			int curent = stanga[poz];
			while (dreapta[curent] != NULL_TELEM)
				curent = dreapta[curent];

			if (curent != stanga[poz]) 
			{
				dreapta[parinti[curent]] = stanga[curent];
				parinti[stanga[curent]] = parinti[curent];
				stanga[curent] = stanga[poz];
			}
			dreapta[curent] = dreapta[poz];
			parinti[curent] = parinti[poz];
			if (poz == radacina)
				radacina = curent;
		}
		//CAZUL 3: daca are un singur fiu
		else
		{
			int val;
			if (stanga[poz] == NULL_TELEM)
				val = dreapta[poz]; //daca are fiul drept
			else
				val = stanga[poz]; //daca are fiul stang

			if (poz != radacina)
			{
				refa_legatura(poz, parinti[poz], val);
				parinti[val] = parinti[poz];
			}
			else
			{
				radacina = val;
				parinti[radacina] = NULL_TELEM;
			}
		}
	dimensiune--;
	dealoca(poz);
	return true;
}


bool Multime::cauta(TElem elem) const {
	/* de adaugat */
	// Complexitate: O(h)

	int curent = radacina;
	while (curent != NULL_TELEM)
	{
		if (elem == element[curent])
			return true;
		if (rel(elem, element[curent]))
			curent = stanga[curent];
		else
			curent = dreapta[curent];
	}
	return false;
}


int Multime::dim() const {
	/* de adaugat */
	// Complexitate: θ(1)
	return dimensiune;
}

bool Multime::vida() const {
	/* de adaugat */
	// Complexitate: θ(1)
	return radacina == NULL_TELEM;
}

IteratorMultime Multime::iterator() const {
	// Complexitate: θ(1)
	return IteratorMultime(*this);
}


Multime::~Multime() {
	/* de adaugat */
	// Complexitate: θ(1)
	delete[] element;
	delete[] stanga;
	delete[] dreapta;
	delete[] parinti;
}


int Multime::aloca() {
	// Complexitate: θ(1)
	int i = prim_liber;
	prim_liber = stanga[prim_liber];
	return i;
}

void Multime::dealoca(int i) {
	// Complexitate: θ(1)
	stanga[i] = prim_liber;
	prim_liber = i;
}

void Multime::init_spatiu_liber() {
	// Complexitate: θ(n)
	// initiere spatiu liber
	for (int i = 0; i < capacitate - 1; ++i) 
		stanga[i] = i + 1;
	stanga[capacitate - 1] = NULL_TELEM;
}

int Multime::cauta_poz(TElem e) {
	// Complexitate: O(h)

	int poz = radacina;
	int anterior = radacina;
	while (poz != NULL_TELEM)
	{
		anterior = poz;
		if (e == element[poz])
			return poz;
		if (rel(e, element[poz]))
			poz = stanga[poz];
		else
			poz = dreapta[poz];
	}
	return anterior;
}

void Multime::refa_legatura(int fiu, int parinte, int val) {
	// Complexitate: θ(1)
	if (rel(element[fiu], element[parinte]))
		stanga[parinte] = val;
	else
		dreapta[parinte] = val;
}



