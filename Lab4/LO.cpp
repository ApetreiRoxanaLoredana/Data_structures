#include "Iterator.h"
#include "LO.h"
#include <exception>
#include <iostream>
using namespace std;


int LO::aloca()
{
	// Complexitate: θ(1)
	int i = prim_liber;
	prim_liber = urm[prim_liber];
	return i;
}

void LO::dealoca(int i)
{
	// Complexitate: θ(1)
	urm[i] = prim_liber;
	prim_liber = i;
}

void LO::init_spatiu_liber()
{
	// Complexitate: θ(n)
	for (int i = 0; i < cp - 1; ++i) // initiere spatiu liber
		urm[i] = i + 1;
	urm[cp - 1] = -1;
}

int LO::creeaza_nod(TElement e)
{	
	// Complexitate: O(n)
	if (prim_liber == -1)
		redim(); // Complexitate: θ(n)
	int i = aloca(); // Complexitate: θ(1)
	if (i != -1)
	{
		this->e[i] = e;
		urm[i] = -1;
		prec[i] = -1;
	}
	return i;
}

void LO::redim()
{
	// Complexitate: θ(n)
	TElement* aux = new TElement[cp * 2];
	int* aux2 = new int[cp * 2];
	int* aux3 = new int[cp * 2];
	for (int i = 0; i < cp; ++i)
	{
		aux[i] = e[i];
		aux2[i] = urm[i];
		aux3[i] = prec[i];
	}

	delete[] e;
	delete[] urm;
	delete[] prec;

	e = aux;
	urm = aux2;
	prec = aux3;

	for (int i = cp; i < cp * 2 - 1; ++i) // initiere spatiu liber
		urm[i] = i + 1;
	urm[cp * 2 - 1] = -1;
	prim_liber = cp;

	cp *= 2; //dublam capacitatea
}

LO::LO(Relatie r) : rel{ r } {
	/* de adaugat */
	// Complexitate: θ(n)
	dimensiune = 0;
	prim = -1;
	ultim = -1;
	cp = 1;

	urm = new int[cp];
	prec = new int[cp];
	e = new TElement[cp];

	init_spatiu_liber(); // Complexitate: θ(n)

	prim_liber = 0;
}

// returnare dimensiune
//returneaza numarul de perechi (cheie, valoare) din dictionar
int LO::dim() const {
	/* de adaugat */
	// Complexitate: θ(1)
	return this->dimensiune;
}

// verifica daca LO e vida
bool LO::vida() const {
	/* de adaugat */
	// Complexitate: θ(1)
	return prim == -1;
}

// returnare element
//arunca exceptie daca i nu e valid
TElement LO::element(int i) const {
	/* de adaugat */
	// Complexitate: O(n)

	//daca i nu e valid
	if (i < 0 || i >= dimensiune)
		throw std::exception();

	Iterator it = Iterator{ *this };

	//cautam elementul de pe pozitia i
	for (int cnt = 0; cnt < i; ++cnt)
		it.urmator();

	return this->e[it.curent];
}

// sterge element de pe o pozitie i si returneaza elementul sters
//arunca exceptie daca i nu e valid
TElement LO::sterge(int i) {
	/* de adaugat */
	// Complexitate: O(n)

	// daca i nu e valid
	if (i < 0 || i >= dimensiune)
		throw std::exception();

	Iterator it = iterator();

	// cautam elementul de pe pozitia i
	for (int cnt = 0; cnt < i; ++cnt)
		it.urmator();

	// salvam elementul
	TElement e = this->e[it.curent];

	// daca e singurul element din lista
	if (prim == it.curent && ultim == it.curent)
	{
		prim = ultim = -1;
		dealoca(it.curent);
		dimensiune--;
		return e;
	}

	// daca e primul element
	if (it.curent == prim)
	{
		prim = urm[it.curent];
		prec[prim] = -1;
		dealoca(it.curent);
		dimensiune--;
		return e;
	}
	// daca e ultimul element
	if (it.curent == ultim)
	{
		ultim = prec[it.curent];
		urm[ultim] = -1;
		dealoca(it.curent);
		dimensiune--;
		return e;
	}

	//altfel
	urm[prec[it.curent]] = urm[it.curent];
	prec[urm[it.curent]] = prec[it.curent];
	dealoca(it.curent);
	dimensiune--;
	return e;
}

// cauta element si returneaza prima pozitie pe care apare (sau -1)
int LO::cauta(TElement e) const {
	/* de adaugat */
	// Complexitate: O(n)

	// daca lista e vida
	if (vida())
		return -1;
	
	Iterator poz{ *this };
	int cnt = 0;
	while (poz.valid() && !rel(e, poz.element()))
	{
		poz.urmator();
		cnt++;
	}

	// daca nu a gasit elementul
	if (!poz.valid())
		return -1;

	// daca a gasit elementul
	if (poz.element() == e)
		return cnt;
	return -1;
}

// adaugare element in LO
void LO::adauga(TElement e) {
	/* de adaugat */
	// Complexitate: O(n)
	TElement nod = creeaza_nod(e); //noul element ce trebuie adaugat
	// daca nu exista nici un element in lista
	if (vida()) 
	{
		prim = ultim = nod;
		dimensiune++;
		return;
	}
	// daca e primul element din lista
	if (rel(this->e[nod], this->e[prim]))
	{
		prec[prim] = nod;
		urm[nod] = prim;
		prim = nod;
		dimensiune++;
		return;
	}

	// daca trebuie adaugat pe ultima pozitie
	if (rel(this->e[ultim], this->e[nod]))
	{
		urm[ultim] = nod;
		prec[nod] = ultim;
		ultim = nod;
		dimensiune++;
		return;
	}

	//cautam pozitia unde trebuie sa fie inserat
	Iterator poz = iterator();
	while (!rel(this->e[nod], poz.element()))
		poz.urmator();

	//adaugam pe pozitia poz;
	prec[nod] = prec[poz.curent];
	urm[nod] = poz.curent;
	urm[prec[poz.curent]] = nod;
	prec[poz.curent] = nod;
	dimensiune++;
}

// returnare iterator
Iterator LO::iterator() {
	// Complexitate: θ(1)
	return Iterator(*this);
}


//destructor
LO::~LO() {
	/* de adaugat */
	// Complexitate: θ(1)
	delete[] e;
	delete[] prec;
	delete[] urm;
}

/// <summary>
///
/// Caz favorabil: elementele din list se afla pe primele pozitii in my_list: theta(n)
/// Caz defavorabil: elementele din list se afla in my_list pe ultimele penultimele pozitii: theta(n * m)
/// Caz mediu: theta(n * m)
/// Complexitate: O(n * m)
/// n - nr de elemente din list
///	m - nr de elemente din my_list
///
/// Preconditii: list (LO), my_list (Lo)
/// Postconditii: nr (int)
/// 
/// Subalgoritm
///		Daca list.vida sau my_list.vida atunci
///			nr<-0
///			iesi_din_algoritm
///		SfDaca
/// 
///		nr<-0
///		
///		Cat timp it1.valid executa
///			Cat timp it2.valid executa
///				Daca it1.element = it2.element atunci
///					nr<-nr+1
///					Daca it2.curent = prim si i2.curent = ultim atunci
///						prim <- -1
///						ultim <- -1
///						dealoca(it2.curent)
///						dimensiune<-dimensiune-1
///						iesi_din_cat_timp
///					SfDaca
///					Daca it2.curent = prim atunci
///						prim <- urm[it2.curent]
///						prec[prim] <- -1
///						dealoca(it2.curent)
///						dimensiune<-dimensiune-1
///						iesi_din_cat_timp
///					SfDaca
///					Daca it2.curent = ultim atunci
///						ultim <- prec[it2.curent]
///                     urm[ultim] <- -1
///                     dealoca(it2.curent)
///                     dimensiune<-dimensiune-1
///						iesi_din_cat_timp
///					SfDaca
///					urm[prec[it2.curent]] <- urm[it2.curent]
///                 prec[urm[it2.curent]] <- prec[it2.curent]
///                 dealoca(it2.curent)
///                 dimensiune <- dimensiune-1
///					iesi_din_cat_timp
///				SfDaca				
/// 
///				urmator(it2)
///			SfCat_timp
///			it1.urmator()
///		SfCat_timp
/// 
/// </summary>
int LO::eliminaToate(LO& lista)
{
	if (lista.vida() || this->vida())
		return 0;

	int nr = 0;

	Iterator it1 = lista.iterator();

	while (it1.valid())
	{
		Iterator it2 = this->iterator();
		while (it2.valid())
		{
			if (it1.element() == it2.element())
			{
				nr++;
				if (prim == it2.curent && ultim == it2.curent)
				{
					prim = ultim = -1;
					dealoca(it2.curent);
					dimensiune--;
					break;
				}
				if (it2.curent == prim)
				{
					prim = urm[it2.curent];
					prec[prim] = -1;
					dealoca(it2.curent);
					dimensiune--;
					break;
				}
				if (it2.curent == ultim)
				{
					ultim = prec[it2.curent];
					urm[ultim] = -1;
					dealoca(it2.curent);
					dimensiune--;
					break;
				}
		
				urm[prec[it2.curent]] = urm[it2.curent];
				prec[urm[it2.curent]] = prec[it2.curent];
				dealoca(it2.curent);
				dimensiune--;
				break;
			}

			it2.urmator();
		}

		it1.urmator();
	}

	return nr;

}

int LO::eliminaToate2(LO& lista)
{
	if (lista.vida() || this->vida())
		return 0;

	int nr = 0;

	Iterator it1 = lista.iterator();

	while (it1.valid())
	{
		Iterator it2 = this->iterator();
		while (it2.valid())
		{
			if (it1.element() == it2.element())
			{
				nr++;
				if (prim == it2.curent && ultim == it2.curent)
				{
					prim = ultim = -1;
					dealoca(it2.curent);
					dimensiune--;
				}
				else
				if (it2.curent == prim)
				{
					prim = urm[it2.curent];
					prec[prim] = -1;
					dealoca(it2.curent);
					dimensiune--;
				}
				else
				if (it2.curent == ultim)
				{
					ultim = prec[it2.curent];
					urm[ultim] = -1;
					dealoca(it2.curent);
					dimensiune--;
				}
				else
				{

					urm[prec[it2.curent]] = urm[it2.curent];
					prec[urm[it2.curent]] = prec[it2.curent];
					dealoca(it2.curent);
					dimensiune--;
				}
			}

			it2.urmator();
		}

		it1.urmator();
	}

	return nr;

}
