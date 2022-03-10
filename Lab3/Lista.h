#pragma once

typedef int TElem;

class IteratorLP;

//referire a clasei Nod
class Nod;

//se defineste tipul PNod ca fiind adresa unui Nod
typedef Nod* PNod;

class Nod {
public:
	friend class Lista;

	//constructor
	Nod(TElem e, PNod urm) : e{ e }, urm{ urm }{};

	//returneaza TElementul e
	TElem element();

	//returneaza un pointer la urmatorul nod
	PNod urmator();

private:
	TElem e; //elementul
	PNod urm; //pointer la urmatorul nod
};

class Lista {
	friend class IteratorLP;
private:
	/* aici e reprezentarea */
	PNod primul; //pointer la primul nod
	PNod ultimul; //pointer la ultimul nod
	int dimensiune; //dimensiunea listei

public:

	// constructor
	Lista();

	// returnare dimensiune
	int dim() const;

	// verifica daca lista e vida
	bool vida() const;

	// prima pozitie din lista
	IteratorLP prim() const;

	// returnare element de pe pozitia curenta
	//arunca exceptie daca poz nu e valid
	TElem element(IteratorLP poz) const;

	// modifica element de pe pozitia poz si returneaza vechea valoare
	//arunca exceptie daca poz nu e valid
	TElem modifica(IteratorLP poz, TElem e);

	// adaugare element la inceput
	void adaugaInceput(TElem e);

	// adaugare element la sfarsit
	void adaugaSfarsit(TElem e);

	// adaugare element dupa o pozitie poz
	//dupa adaugare poz este pozitionat pe elementul adaugat
	//arunca exceptie daca poz nu e valid
	void adauga(IteratorLP& poz, TElem e);

	// sterge element de pe o pozitie poz si returneaza elementul sters
	//dupa stergere poz este pozitionat pe elementul de dupa cel sters
	//arunca exceptia daca poz nu e valid
	TElem sterge(IteratorLP& poz);

	// cauta element si returneaza prima pozitie pe care apare (sau iterator invalid)
	IteratorLP cauta(TElem e) const;

	//destructor

	~Lista();

	/*
	* Cerinta
	//Listă (indiferent dacă este ordonată sau nu)
	// returnează ultimul index al unui element dat
	// daca elementul nu este în listă returnează un TPozitie nevalid
	// TPozitie [nume_clasa]::ultimulIndex(TElem elem) const;
	Obs: depinzând dacă aveți listă indexată sau cu poziție iterator, înlocuiți TPozitie cu int sau IteratorListă și  TPozitie nevalid cu indexul -1 sau iterator nevalid.
	*/
	IteratorLP ultimul_index(TElem elem) const;
};
