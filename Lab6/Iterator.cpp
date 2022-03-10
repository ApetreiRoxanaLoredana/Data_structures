#include "Iterator.h"
#include "DO.h"
#include <exception>

using namespace std;

Iterator::Iterator(const DO& d) : dict(d)
// Complexitate: O(nlog(n))
{
	/* de adaugat */
	curent = 0;
	dim = dict.dimensiune;
	elem = new TElem[dim];

	int k = 0;
	//adaugam elementele intr-un vector nou
	for (int i = 0; i < dict.cp; ++i)
		if (dict.e[i].first != NULL_TVALOARE && dict.e[i].second != NULL_TVALOARE)
			elem[k++] = dict.e[i];

	mergeSort(elem, 0, dim - 1, dict.rel);
}

/// Preconditii: k - intreg, it - Iterator
/// Postconditii: it - Iterator
/// Subalgoritm avanseazaKPasi
///		Daca k < 0 sau k = 0 atunci
///			Arunca exceptie
///		Altfel
///			Daca !it.valid() atunci
///				Arunca exceptie
///			Altfel
///				it.curent <- it.curent + k
///				Daca !it.valid() atunci
///					Arunca exceptie
///				SfDaca
///			SfDaca
///		SfDaca
///		avanseazaKPasi<-it.curent
/// SfSubalgoritm avanseazaKPasi
void Iterator::avanseazaKPasi(int k)
/// Complexitate caz favorabil = caz defavorabil = caz mediu
/// Complexitate totala: Theta(1);
{
	//k nevalid
	if (k <= 0)
		throw std::exception();
	if (!valid())
		throw std::exception();

	curent += k;
	if (!valid())
		throw std::exception();
}

void Iterator::prim()
// Complexitate: θ(1)
{
	/* de adaugat */
	curent = 0;
}

void Iterator::urmator()
// Complexitate: θ(1)
{
	/* de adaugat */
	if (!valid())
		throw std::exception();
	curent++;
}

bool Iterator::valid() const
// Complexitate: θ(1)
{
	/* de adaugat */
	return curent < dim;
}

TElem Iterator::element() const
// Complexitate: θ(1)
{
	/* de adaugat */
	if (!valid())
		throw std::exception();
	return elem[curent];
}

void Iterator::merge(TElem arr[], int l, int m, int r, Relatie rel)
// Complexitate: θ(max(n1, n2)) 
{
	int n1 = m - l + 1;
	int n2 = r - m;

	TElem* L = new TElem[n1];
	TElem* R = new TElem[n2];

	for (int i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (int j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	int i = 0;
	int j = 0;
	int k = l;

	while (i < n1 && j < n2) {
		if (rel(L[i].first, R[j].first)) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

void Iterator::mergeSort(TElem arr[], int l, int r, Relatie rel) 
// Complexitate: O(nlog(n))
{
	if (l >= r) {
		return;//returns recursively
	}
	int m = l + (r - l) / 2;
	mergeSort(arr, l, m, rel);
	mergeSort(arr, m + 1, r, rel);
	merge(arr, l, m, r, rel);
}

Iterator::~Iterator()
// Complexitate: θ(1)
{
	delete[] elem;
}


