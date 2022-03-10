
#include <exception>

#include "IteratorLP.h"
#include "Lista.h"

#include <iostream>

Lista::Lista() {
	/* de adaugat */
	//Complexitate θ(1)
	this->primul = nullptr;
	this->ultimul = nullptr;
	this->dimensiune = 0;
}

int Lista::dim() const {
	/* de adaugat */
	//Complexitate θ(1)
	return dimensiune;
}


bool Lista::vida() const {
	/* de adaugat */
	//Complexitate θ(1)
	return primul == nullptr;
}

IteratorLP Lista::prim() const {
	/* de adaugat */
	//Complexitate θ(1)
	IteratorLP poz = IteratorLP(*this);
	poz.prim();
	return poz;
}

TElem Lista::element(IteratorLP poz) const {
	/* de adaugat */
	//Complexitate θ(1)
	if (!poz.valid())
		throw std::exception();
	return poz.element();
}

TElem Lista::sterge(IteratorLP& poz) {
	/* de adaugat */
	//Complexitate O(n)
	if (!poz.valid())
		throw std::exception();

	PNod sters = poz.curent;
	TElem vechi = sters->element();

	if (sters == primul) //daca elementul se afla pe prima pozitie
	{
		primul = primul->urm;
		poz.urmator();
		delete sters;
		dimensiune--;
		return vechi;
	}

	IteratorLP cauta(*this);
	cauta.prim();

	while (cauta.curent->urm != sters)
		cauta.urmator();

	poz.urmator();

	cauta.curent->urm = sters->urm;
	delete sters;

	if (cauta.curent->urm == nullptr) //daca elementul sters a fost ultimul
		ultimul = cauta.curent;

	dimensiune--;
	return vechi;
	
}

IteratorLP Lista::cauta(TElem e) const {
	/* de adaugat */
	//Complexitate O(n)
	IteratorLP poz = IteratorLP(*this);
	poz.prim();

	while (poz.curent != nullptr && poz.element() != e)
		poz.urmator();
	return poz;
}

TElem Lista::modifica(IteratorLP poz, TElem e) {
	/* de adaugat */
	//Complexitate θ(1)
	if (!poz.valid())
		throw std::exception();

	TElem vechi = poz.element();
	poz.curent->e = e;
	return vechi;
}

void Lista::adauga(IteratorLP& poz, TElem e) {
	/* de adaugat */
	//Complexitate θ(1)
	if (!poz.valid())
		throw std::exception();

	PNod nou = new Nod{ e, nullptr };
	PNod curent = poz.curent;

	nou->urm = curent->urm;
	curent->urm = nou;

	if (nou->urm == nullptr) //daca a fost adaugat pe ultima pozitie
		ultimul = nou;

	dimensiune++;
	poz.urmator();
}

void Lista::adaugaInceput(TElem e) {
	/* de adaugat */
	//Complexitate θ(1)
	PNod nou = new Nod{ e, primul };
	primul = nou;
	dimensiune++;
}

void Lista::adaugaSfarsit(TElem e) {
	/* de adaugat */
	//Complexitate θ(1)
	PNod nou = new Nod{ e, nullptr };

	if (primul == nullptr)
		primul = ultimul = nou;
	else {
		ultimul->urm = nou;
		ultimul = nou;
	}
	dimensiune++;
}

Lista::~Lista() {
	/* de adaugat */
	//Complexitate θ(n)
	while (primul != nullptr)
	{
		PNod nou = primul;
		primul = primul->urm;
		delete nou;
	}
}

/*
* Cerinta
//Listă (indiferent dacă este ordonată sau nu)
// returnează ultimul index al unui element dat
// daca elementul nu este în listă returnează un TPozitie nevalid
// TPozitie [nume_clasa]::ultimulIndex(TElem elem) const;
Obs: depinzând dacă aveți listă indexată sau cu poziție iterator, înlocuiți TPozitie cu int sau IteratorListă și  TPozitie nevalid cu indexul -1 sau iterator nevalid.
*/
/// Pre: elem: TElem , lista:Lista
/// Post: gasit: IteratorLP 
///			gasit = ultima pozitie pe care se afla elem
///			gasit = NIL daca nu exista elem
/// 
/// Subalgoritm ultimul_index(lista, elem, gasit)
///		it.curent <- lista.prim
///		gasit <- NIL
///		
///		cat timp it.curent != NIL atunci
///			daca [it.curent].element = elem atunci
///				gasit.curent = it.curent
///			sf_daca
///			it.urmator
///		sf_cat_timp
/// sf_subalgoritm
///
IteratorLP Lista::ultimul_index(TElem elem) const
//caz favorabil = caz defavorabil = caz general = θ(n)
{
	IteratorLP it = IteratorLP(*this);
	it.prim();

	IteratorLP gasit = IteratorLP(*this);
	gasit.curent = nullptr;

	while (it.curent != nullptr)
	{
		if (it.curent->element() == elem)
			gasit.curent = it.curent;
		it.urmator();
	}

	return gasit;
}

TElem Nod::element()
{
	//Complexitate θ(1)
	return e;
}

PNod Nod::urmator()
{
	//Complexitate θ(1)
	return urm;
}
