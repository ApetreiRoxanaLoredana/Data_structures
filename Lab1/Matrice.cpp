#include "Matrice.h"
#include <exception>
#include <iostream>

using namespace std;


int Matrice::compara(TElement a, int i, int j) const
//Complexitate: ϴ(1)
{
	if (a.linie < i)
		return -1;
	if (a.linie == i)
	{
		if (a.coloana == j)
			return 0;
		if (a.coloana < j)
			return -1;
		if (a.coloana > j)
			return 1;
	}
	if (a.linie > i)
		return 1;
}

Matrice::Matrice(int m, int n) 
//Complexitate: ϴ(1)
{
	/* de adaugat */
	if (m <= 0 || n <= 0)
		throw exception();
	v = new VectorDinamic[1];
	v->e = new TElement[n * m];
	v->n = 0;
	v->cp = n * m;
	nr_linii = m;
	nr_coloane = n;
}

Matrice::~Matrice()
//Complexitate: ϴ(1)
{
	delete[] v->e;
	delete[] v;
}

int Matrice::nrLinii() const 
//Complexitate: ϴ(1)
{
	/* de adaugat */
	return this->nr_linii;
}


int Matrice::nrColoane() const 
//Complexitate: ϴ(1)
{
	/* de adaugat */
	return this->nr_coloane;
}


TElem Matrice::element(int i, int j) const 
//Complexitate: O(log2(n))
//n - numarul total de elemente din lista
{
	/* de adaugat */
	if (!valideaza(i, j))
		throw exception();
	
	int poz = cautare_binara(i, j);

	if (v->e[poz].linie == i && v->e[poz].coloana == j)
		return v->e[poz].valoare;
	return NULL_TELEMENT;
	
}


TElem Matrice::modifica(int i, int j, TElem e) 
//Complexitate: O(n)
//n - numarul total de elemente din lista
{
	/* de adaugat */
	if (!valideaza(i, j))
		throw exception();

	int poz = cautare_binara(i, j);
	int valoare_veche;

	if (v->e[poz].linie == i && v->e[poz].coloana == j)
	{
		if (e == NULL_TELEMENT)
		{
			//stergere
			valoare_veche = v->e[poz].valoare;
			for (int i = poz; i < v->n - 1; ++i)
				v->e[i] = v->e[i + 1];
			(v->n)--;
			return valoare_veche;
		}

		//modificare
		valoare_veche = v->e[poz].valoare;
		v->e[poz].valoare = e;
		return valoare_veche;
	}
	//adauga
	for (int i = v->n; i > poz; --i)
		v->e[i] = v->e[i - 1];
	v->e[poz].linie = i;
	v->e[poz].coloana = j;
	v->e[poz].valoare = e;
	v->n++;
	return NULL_TELEMENT;
}

bool Matrice::valideaza(int i, int j) const
//Complexitate: ϴ(1)
{
	if(i < 0 || j < 0)
		return false;
	if (i > nr_linii || j > nr_coloane)
		return false;
	return true;
}

int Matrice::cautare_binara(int i, int j) const
//Complexitate: O(log2(n))
//n - numarul total de elemente din lista
{
	int Left = 0, Right = v->n - 1;
	if (v->n == 0)
		return 0;
	if (i > v->e[Right - 1].linie)
		return Right+1;
	if (i < v->e[0].linie )
		return 0;

	while (Left <= Right)
	{
		int Mid = (Left + Right) / 2;
		if (compara(v->e[Mid], i, j) == 0)
			return Mid;
		if (compara(v->e[Mid], i, j) > 0)
			Right = Mid - 1;
		if (compara(v->e[Mid], i, j) < 0)
			Left = Mid + 1;
	}
	return Left;
}

