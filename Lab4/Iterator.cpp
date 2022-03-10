#include "Iterator.h"
#include "LO.h"
#include <exception>

Iterator::Iterator(const LO& lo) : lista(lo) {
	/* de adaugat */
	// Complexitate: θ(1)
	this->curent = lista.prim;
}

void Iterator::prim() {
	/* de adaugat */
	// Complexitate: θ(1)
	this->curent = lista.prim;
}

void Iterator::urmator() {
	/* de adaugat */
	// Complexitate: θ(1)
	if (!valid())
		throw std::exception();

	this->curent = lista.urm[this->curent];
}

bool Iterator::valid() const {
	/* de adaugat */
	// Complexitate: θ(1)
	return curent != -1;
}

TElement Iterator::element() const {
	/* de adaugat */
	// Complexitate: θ(1)
	if (!valid())
		throw std::exception();
	return lista.e[this->curent];
}


