#pragma once
#include <iostream>
class Iterator;

typedef int TComparabil;
typedef TComparabil TElement;
typedef bool (*Relatie)(TElement, TElement);

#define NULL_TELEMENT -1

class LO {
private:
	friend class Iterator;
private:
	/* aici e reprezentarea */

	int cp; // capacitateade memorare a celor 3 vectori
	int dimensiune; // dimensiunea celor 3 vectori
	Relatie rel; // relatia dintre obiecte

	TElement* e; //vector de TElemente
	int* urm; //vector de legaturi
	int* prec; //vector de legaturi

	int prim; //referinta catre primul element al listei
	int prim_liber; //referinta catre primul element liber al listei
	int ultim; //referinta catre ultimul element al listei
	
	//functii pentru alocarea/dezalocarea unui spatiu liber
	int aloca(); //se returneaza pozitia unui spatiu liber din lista
	void dealoca(int i); //dealoca spatiul de indice i
	void init_spatiu_liber(); //initializeaza spatiile libere
	int creeaza_nod(TElement e); //creeaza un nod in lista inlantuita
	void redim(); //redimensionarea vectorilor

public:
	// constructor
	LO(Relatie r);

	// returnare dimensiune
	int dim() const;

	// verifica daca LO e vida
	bool vida() const;

	// returnare element
	//arunca exceptie daca i nu e valid
	TElement element(int i) const;

	// adaugare element in LO a.i. sa se pastreze ordinea intre elemente
	void adauga(TElement e);

	// sterge element de pe o pozitie i si returneaza elementul sters
	//arunca exceptie daca i nu e valid
	TElement sterge(int i);

	// cauta element si returneaza prima pozitie pe care apare (sau -1)
	int cauta(TElement e) const;

	// returnare iterator
	Iterator iterator();

	//destructor
	~LO();

	int eliminaToate(LO& lista);

	int eliminaToate2(LO& lista);

};
