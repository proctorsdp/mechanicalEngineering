#include <iostream>
#include "muller.h"

using namespace std;

int main() {
    muller m;
    char again;

    m.mullerSolver();

    cout << "Would you like to find another root of the equation?\n"
            "'y' or 'n'?\n";
    cin >> again;

    if (again == 'y') {
        main();
    }

    return 0;
}