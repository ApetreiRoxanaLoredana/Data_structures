#pragma once
#define NULL_TELEMENT 0
typedef int TElem;

typedef struct {
	int linie;
	int coloana;
	TElem valoare;
} TElement;

typedef struct {
	int cp; // capacitate
	int n; // lungimea
	TElement* e;
} VectorDinamic;

class Matrice {

private:
	/* aici e reprezentarea */
	VectorDinamic* v;
	int nr_linii;
	int nr_coloane;

	//verifica daca TElement are pozitia mai mica, egala sau mai mare 
	//ca pozitiile i si j
	//Return: 1 daca are pozitia mai mare
	//        0 daca are pozitia egala
	//        -1 daca are pozitia mai mica
	int compara(TElement a, int i, int j) const;

	// verifica daca (i,j) nu e o pozitie valida in Matrice
	// returneaza true daca pozitia e valida sau false altfel
	bool valideaza(int i, int j) const;

	// cauta elementul care se afla pe linia i si coloana j
	// returneaza pozitia la care se afla elementul in lista dinamica sau la care trebuie inserat
	int cautare_binara(int i, int j) const;

public:

	//constructor
	//se arunca exceptie daca nrLinii<=0 sau nrColoane<=0
	Matrice(int nrLinii, int nrColoane);

	//destructor
	~Matrice();

	//returnare element de pe o linie si o coloana
	//se arunca exceptie daca (i,j) nu e pozitie valida in Matrice
	//indicii se considera incepand de la 0
	TElem element(int i, int j) const;

	// returnare numar linii
	int nrLinii() const;

	// returnare numar coloane
	int nrColoane() const;

	// modificare element de pe o linie si o coloana si returnarea vechii valori
	// se arunca exceptie daca (i,j) nu e o pozitie valida in Matrice
	TElem modifica(int i, int j, TElem);

};