#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>

#include <iostream>
#include "ui.h"
#include "teste.h"
using std::cout;

void main_run() {
    parcare p;
    service srv{ p };
    service lst{ p };
    UI ui{ srv, lst };
    //ui.run();
}


int main() {
    test_all();
    system("cls");
    main_run();
    _CrtDumpMemoryLeaks();
}

