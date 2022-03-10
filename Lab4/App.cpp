#include <iostream>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "LO.h"
#include <assert.h>
#include "TestScurt.h"
#include "TestExtins.h"

int main() {
    testAll();
    testAllExtins();
    std::cout << "Finished LI Tests!" << std::endl;

    _CrtDumpMemoryLeaks();
}