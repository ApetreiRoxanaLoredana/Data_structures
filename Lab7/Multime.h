#pragma once

typedef int TElem;

typedef bool(*Relatie)(TElem, TElem);
#define NULL_TELEM -1

//in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);

class IteratorMultime;

class Multime {

	friend class IteratorMultime;

private:
	/* aici e reprezentarea */
	TElem* element; //elementele
	int* stanga; //fii stangi
	int* dreapta; //fii drepti
	int* parinti; 
	int radacina;

	int prim_liber;

	int capacitate;
	int dimensiune;
	
	int aloca(); //se returneaza pozitia unui spatiu liber din lista
	void dealoca(int i); //dealoca spatiul de indice i
	void init_spatiu_liber(); //initializeaza spatiile libere
	int cauta_poz(TElem e); //returneaza pozitia elementului e 
	void refa_legatura(int fiu, int parinte, int val); //leaga parintele de nepot

public:
		//constructorul implicit
		Multime();

		//adauga un element in multime
		//returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
		bool adauga(TElem e);

		//sterge un element din multime
		//returneaza adevarat daca elementul a existat si a fost sters
		bool sterge(TElem e);

		//verifica daca un element se afla in multime
		bool cauta(TElem elem) const;


		//intoarce numarul de elemente din multime;
		int dim() const;

		//verifica daca multimea e vida;
		bool vida() const;

		//returneaza un iterator pe multime
		IteratorMultime iterator() const;

		// destructorul multimii
		~Multime();

};

