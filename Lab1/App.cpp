#include <iostream>
#include "Matrice.h"
#include "TestExtins.h"
#include "TestScurt.h"

#define _CRTDBG_MAP_ALLOC 
#include <stdio.h>
#include <crtdbg.h>

using namespace std;

/*
* . TAD Matrice - reprezentare sub forma unei matrice rare, folosind un vector dinamic de
triplete de forma <linie, coloană, valoare> (valoare≠0), memorate în ordine lexicografică după
(linie, coloană).
*/
int main() {

	testAll();
	testAllExtins();

	_CrtDumpMemoryLeaks();

	cout << "End";
}
