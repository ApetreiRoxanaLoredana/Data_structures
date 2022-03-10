#include <assert.h>

#include "DO.h"
#include "Iterator.h"

#include <exception>
using namespace std;

bool relatie1(TCheie cheie1, TCheie cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	DO dictOrd = DO(relatie1);
	assert(dictOrd.dim() == 0);
	assert(dictOrd.vid());
    dictOrd.adauga(1,2);
    assert(dictOrd.dim() == 1);
    assert(!dictOrd.vid());
    assert(dictOrd.cauta(1)!=NULL_TVALOARE);
    TValoare v =dictOrd.adauga(1,3);
    assert(v == 2);
    assert(dictOrd.cauta(1) == 3);
    Iterator it = dictOrd.iterator();
    it.prim();
    while (it.valid()){
    	TElem e = it.element();
    	assert(e.second != NULL_TVALOARE);
    	it.urmator();
    }
    assert(dictOrd.sterge(1) == 3);
    assert(dictOrd.vid());

    //test functionalitate
    DO dic = DO(relatie1);
    dic.adauga(1, 2);
    dic.adauga(4, 6);
    dic.adauga(3, 7);
    dic.adauga(9, 2);
    dic.adauga(8, 4);
    //1 3 4 8 9
    Iterator it1 = dic.iterator();
    it1.prim();
    TElem e1 = it1.element();
    assert(e1.first = 1);
    assert(e1.second == 2);

    it1.avanseazaKPasi(3);
    TElem e2 = it1.element();
    assert(e2.first = 8);
    assert(e2.second == 4);

    try {
        it1.avanseazaKPasi(-1);
        assert(false);
    }
    catch (std::exception ex) {
        assert(true);
    }

    try {
        it1.avanseazaKPasi(2);
        assert(false);
    }
    catch (std::exception ex) {
        assert(true);
    }
}


