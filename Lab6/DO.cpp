#include "Iterator.h"
#include "DO.h"
#include <iostream>

#include <exception>
using namespace std;

void DO::act_prim_liber()
// Complexitate: O(n), dar in ipoteza dispersiei uniforme va fi Theta(1)
{
	prim_liber++;
	while (prim_liber < cp && e[prim_liber].first != NULL_TVALOARE)
		prim_liber++;
}

int DO::dispersie(TCheie e) const
// Complexitate: θ(1)
{
	return hash_code(e) % cp;
}

int DO::hash_code(TCheie e) const
// Complexitate: θ(1)
{
	return abs(e);
}


DO::DO(Relatie r)
// Complexitate: θ(n)
{
	/* de adaugat */
	cp = 10000; //initializam capacitatea cu o valoare predefinita
	dimensiune = 0;
	rel = r;

	e = new TElem[cp];
	urm = new int[cp];

	for (int i = 0; i < cp; ++i)
	{
		e[i].first = NULL_TVALOARE;
		e[i].second = NULL_TVALOARE;
		urm[i] = NULL_TVALOARE;
	}

	prim_liber = 0;
}

//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
TValoare DO::adauga(TCheie c, TValoare v) 
// Complexitate: O(n), dar in ipoteza dispersiei uniforme va fi Theta(1)
{
	/* de adaugat */
	int index = dispersie(c);

	//daca locatia e libera
	if (e[index].first == NULL_TVALOARE) 
	{
		e[index].first = c;
		e[index].second = v;

		if (index == prim_liber)
			act_prim_liber();

		dimensiune++;
		return NULL_TVALOARE;
	}

	//locatia nu e libera
	int i = index, j;

	//cautam daca cheia exista deja 
	while (i != NULL_TVALOARE && e[i].first != c)
	{
		j = i;
		i = urm[i];
	}

	// daca am gasit cheia
	if (i != NULL_TVALOARE)
	{
		TValoare v_veche = e[i].second;
		e[i].second = v;
		return v_veche;
	}

	// daca nu am gasit cheia
	if (prim_liber < cp) // tabela nu e plina
	{
		e[prim_liber].first = c;
		e[prim_liber].second = v;
		urm[j] = prim_liber;

		dimensiune++;
		act_prim_liber();
		return NULL_TVALOARE;
	}

	throw std::exception{ "Tabela e plina" };
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare DO::cauta(TCheie c) const 
// Complexitate: O(n), dar in ipoteza dispersiei uniforme va fi Theta(1)
{
	/* de adaugat */
	int i = dispersie(c);

	while (i != NULL_TVALOARE && e[i].first != c)
		i = urm[i];

	// nu a gasit cheia
	if (i == NULL_TVALOARE)
		return NULL_TVALOARE;

	// a gasit cheia
	return e[i].second;
}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
TValoare DO::sterge(TCheie c) 
// Complexitate: O(n), dar in ipoteza dispersiei uniforme va fi Theta(1)
{
	/* de adaugat */
	int i = dispersie(c);
	int j = -1;

	while (i != NULL_TVALOARE && e[i].first != c)
	{
		j = i;
		i = urm[i];
	}

	//daca cheia nu exista
	if (i == NULL_TVALOARE)
		return NULL_TVALOARE;

	int curent, prec;

	do {

		prec = i;
		curent = urm[i];

		while (curent != NULL_TVALOARE && dispersie(e[curent].first) != i)
		{
			prec = curent;
			curent = urm[curent];
		}
		if (curent == NULL_TVALOARE)
			break;

		e[i].first = e[curent].first;
		e[i].second = e[curent].second;
		i = curent;
		j = prec;

	} while (curent != NULL_TVALOARE);

	if (j != NULL_TVALOARE)
		urm[j] = urm[i];

	TValoare v_veche = e[i].second;
	e[i].first = NULL_TVALOARE;
	e[i].second = NULL_TVALOARE;
	urm[i] = NULL_TVALOARE;
	dimensiune--;

	if (i < prim_liber)
		prim_liber = i;

	return v_veche;
}

//returneaza numarul de perechi (cheie, valoare) din dictionar
int DO::dim() const 
// Complexitate: θ(1)
{
	/* de adaugat */
	return dimensiune;
}

//verifica daca dictionarul e vid
bool DO::vid() const 
// Complexitate: θ(1)
{
	/* de adaugat */
	return dimensiune == 0;
}

Iterator DO::iterator() const 
// Complexitate: O(nlog(n)) //pentru ca sortarea cu merge sort
{
	return  Iterator(*this);
}

DO::~DO()
// Complexitate: θ(1)
{
	/* de adaugat */
	delete[] e;
	delete[] urm;
}
