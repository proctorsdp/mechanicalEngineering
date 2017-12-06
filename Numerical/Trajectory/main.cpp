#include <iostream>
#include "trajectory.h"

using namespace std;

int main() {
    rootSolver t;
    char again;

    cout << endl << endl;
    cout << "SOLVING FOR THE ANGLE OF DEPARTURE USING GRAPHICAL AND BI-SECTIONAL METHODS\n"
            "***************************************************************************\n";
    t.setupEq();
    t.graphicalReport();
    cout << t.biSectionalReport();

    cout << "Would you like to find another angle using different conditions?\n"
            "'y' or 'n'?\n";
    cin >> again;

    if (again == 'y') {
        main();
    }

    return 0;
}