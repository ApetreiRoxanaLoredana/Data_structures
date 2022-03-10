#include <iostream>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <assert.h>

#include "TestScurt.h"
#include "TestExtins.h"
#include "Lista.h"
#include "IteratorLP.h"

/*
* 13.TAD Lista(interfața cu TPoziție=Iterator) –reprezentare folosind o LSI.
*/

void test();

int main() {
    testAll();
    testAllExtins();
    test();
    std::cout << "Finished LP Tests!" << std::endl;
    _CrtDumpMemoryLeaks();
}

void test()
{
    Lista lista = Lista();
    lista.adaugaSfarsit(1);
    lista.adaugaSfarsit(2);
    lista.adaugaSfarsit(1);
    lista.adaugaSfarsit(3);
    lista.adaugaSfarsit(1);
    lista.adaugaSfarsit(4);
    lista.adaugaSfarsit(3);

    //lista: 1 2 1 3 1 4 3

    IteratorLP it = lista.ultimul_index(1);
    assert(it.valid());
    assert(it.element() == 1);
    it.urmator();
    assert(it.element() == 4);
    it.urmator();
    assert(it.element() == 3);
    it.urmator();
    assert(!it.valid());

    //lista: 1 2 1 3 1 4 3

    IteratorLP it2 = lista.cauta(5);
    assert(!it2.valid());

    lista.adaugaInceput(10);
    lista.adaugaInceput(13);

    //lista: 13 10 1 2 1 3 1 4 3

    IteratorLP it3 = lista.ultimul_index(13);
    assert(it3.element() == 13);
    it3.urmator();
    assert(it3.element() == 10);

    IteratorLP it4 = lista.ultimul_index(30);
    assert(!it4.valid());

    lista.adaugaSfarsit(13);

    //lista: 13 10 1 2 1 3 1 4 3 13

    IteratorLP it5 = lista.ultimul_index(13);
    assert(it5.element() == 13);
    it5.urmator();
    assert(!it5.valid());

    IteratorLP it6 = lista.ultimul_index(4);
    lista.sterge(it6);

    //lista: 13 10 1 2 1 3 1 3 13
    assert(it6.element() == 3);
    IteratorLP it7 = lista.ultimul_index(4);
    assert(!it7.valid());


}