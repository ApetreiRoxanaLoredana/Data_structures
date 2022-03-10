#include "IteratorMultime.h"
#include "Multime.h"
#include <exception>


IteratorMultime::IteratorMultime(const Multime& m) : mult(m), curent{mult.radacina} {
	/* de adaugat */
	// Complexitate: θ(1)
}

TElem IteratorMultime::element() const {
	/* de adaugat */
	// Complexitate: θ(1)
	if (!valid())
		throw std::exception();
	return mult.element[curent];
}

bool IteratorMultime::valid() const {
	/* de adaugat */
	// Complexitate: θ(1)
	return curent != NULL_TELEM;
}

void IteratorMultime::urmator() {
	/* de adaugat */
	// Complexitate: O(h)
	if (!valid())
		throw std::exception();

	//daca are un subarbore in dreapta
	if (mult.dreapta[curent] != NULL_TELEM) 
	{
		curent = mult.dreapta[curent];
		//merge pana la cel mai mic element din subarbore
		while (mult.stanga[curent] != NULL_TELEM)
			curent = mult.stanga[curent];
	}
	else
	{
		int prec = mult.parinti[curent];
		while (prec != NULL_TELEM && curent == mult.dreapta[prec])
		{
			curent = prec;
			prec = mult.parinti[curent];
		}
		curent = prec;
	}
}

void IteratorMultime::prim() {
	/* de adaugat */
	// Complexitate: O(h)
	curent = mult.radacina;
	//merge catre elementul cel mai din stanga
	while (mult.stanga[curent] != NULL_TELEM)
		curent = mult.stanga[curent];
}

int IteratorMultime::prim_el() 
{
	/* de adaugat */
	// Complexitate: O(h)
	int el_curent = mult.radacina;
	//merge catre elementul cel mai din stanga
	while (mult.stanga[el_curent] != NULL_TELEM)
		el_curent = mult.stanga[el_curent];
	return el_curent;
}


/// <summary>
/// Preconditii: iteratorMultime: it
/// Postconditii: curent - indica spre elementul anterior
/// Subalgoritm
///		Daca it.prim_elem() = curent atunci
///			curent <- NIL
///			SfSubalgoritm
///		SfDaca
/// 
///		Daca !it.valid() atunci
///			arunca exceptie
///		SfDaca
/// 
///		Daca mult.stang[curent] != NIL atunci
///			curent <- mult.stanga[curent]
///			Cat timp mult.dreapta[curent] != NIL executa
///				curent <- mult.dreapta[curent]
///			SfCatTimp
///		Altfel
///			Daca rel(mult.element[curent], mult.element[mult.parinti[curent]]) atunci
///				prec <- mult.parinti[curent]
///				Cat timp prec != NIL si curen = mult.stanga[prec] executa
///					curent <- prec
///					prec <- mult.parinti[curent]
///				SfCatTimp
///			Altfel
///				curent <- multi.parinti[curent]
///			SfDaca
///		SfDaca
/// SfSubalgoritm
/// </summary>
/// 
/// Complexitate:
/// Caz favorabil = defavorabil = mediu = O(h)
/// Caz general = O(h)
void IteratorMultime::anterior() {

	int prim_elem = prim_el(); //O(h)
	if (curent == prim_elem)
	{
		curent = NULL_TELEM;
		throw std::exception();
	}

	//daca are fiu stang - valoare mai mica
	//cauta cea mai mare valoare a fiului stang, in fii din dreapta
	if (mult.stanga[curent] != NULL_TELEM)
	{
		curent = mult.stanga[curent];
		while (mult.dreapta[curent] != NULL_TELEM)
			curent = mult.dreapta[curent];
	}
	else
		//daca nu are fiu stang
		if (rel(mult.element[curent], mult.element[mult.parinti[curent]]))
		{
			//daca curent e fiu stang
			//merge in sus pe parinti cat timp gaseste un parinte care sa fie fiu drept
			int prec = mult.parinti[curent];
			while (prec != NULL_TELEM && curent == mult.stanga[prec])
			{
				curent = prec;
				prec = mult.parinti[curent];
			}
			curent = prec;
		}
		else
			//daca curent e fiul drept merge la parinte
			curent = mult.parinti[curent];
}

	