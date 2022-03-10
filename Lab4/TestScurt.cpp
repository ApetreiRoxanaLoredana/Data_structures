#include <assert.h>

#include "Iterator.h"
#include "LO.h"

using namespace std;

bool relatie1(TElement cheie1, TElement cheie2) {
    if (cheie1 <= cheie2) {
        return true;
    }
    else {
        return false;
    }
}

void testAll() {
    LO lo = LO(relatie1);
    assert(lo.dim() == 0);
    assert(lo.vida());
    lo.adauga(1);
    assert(lo.dim() == 1);
    assert(!lo.vida());
    Iterator iterator = lo.iterator();
    assert(iterator.valid());
    iterator.prim();
    assert(iterator.element() == 1);
    iterator.urmator();
    assert(!iterator.valid());
    iterator.prim();
    assert(iterator.valid());
    assert(lo.cauta(1) == 0);
    assert(lo.sterge(0) == 1);
    assert(lo.dim() == 0);
    assert(lo.vida());

    //my test
    LO list = LO(relatie1);
    for (int i = 1; i <= 10; i++)
        list.adauga(i);
    assert(list.dim() == 10);

    LO list2 = LO(relatie1);
    for (int i = 1; i <= 5; i++)
        list2.adauga(i);
    assert(list2.dim() == 5);
    
    assert(list.eliminaToate(list2) == 5);

    Iterator it = list.iterator();
   
    for (int i = 1; i < 5; ++i)
    {
        assert(it.element() == i + 5);
        it.urmator();
    }

    LO list3 = LO(relatie1);

    for (int i = 11; i < 22; ++i)
        list3.adauga(i);
    assert(list.eliminaToate(list3) == 0);

    LO list4 = LO(relatie1);
    for (int i = 6; i <= 10; i++)
        list4.adauga(i);
    assert(list.eliminaToate(list4) == 5);

    assert(list.dim() == 0);
}

