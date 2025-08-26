#include "provided.h"
    #include <iostream>
    #include <cassert>
    using namespace std;

    void doGameTests()
    {
        SmartPlayer bp1("Bart");
        HumanPlayer bp2("Homer");
        Game g(3, 4, 3, &bp1, &bp2);
        g.play();
    }

    int main()
    {
        doGameTests();
        cout << "Passed all tests" << endl;
    }
