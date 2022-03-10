#include "IteratorLP.h"
#include "Lista.h"
#include <exception>

IteratorLP::IteratorLP(const Lista& l) :lista(l) {
	/* de adaugat */
	//Complexitate θ(1)
	curent = l.primul;
}

void IteratorLP::prim() {
	/* de adaugat */
	//Complexitate θ(1)
	curent = lista.primul;
}

void IteratorLP::urmator() {
	/* de adaugat */
	//Complexitate θ(1)
	if (!valid())
		throw std::exception();
	curent = curent->urmator();
}

bool IteratorLP::valid() const {
	/* de adaugat */
	//Complexitate θ(1)
	return curent != nullptr;
}

TElem IteratorLP::element() const {
	/* de adaugat */
	//Complexitate θ(1)
	if (!valid())
		throw std::exception();
	return curent->element();
}


