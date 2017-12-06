#include <iostream>
#include "tempPoly.h"

using namespace std;

int main() {
    rootSolver t;
    char again;

    cout << endl << endl
         << "SOLVING FOR TEMPERATURE USING BI-SECTION\n"
            "****************************************\n"
         << t.biSectionalReport();

    cout << "Would you like to find another Temperature for a different specific heat?\n"
            "'y' or 'n'?\n";
    cin >> again;

    if (again == 'y') {
        main();
    }

    return 0;
}