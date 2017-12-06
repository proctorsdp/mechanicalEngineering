#include <iostream>
#include "frictionSolver.h"

using namespace std;

int main() {
    rootSolver f;
    char again;

    cout << endl << endl;
    cout << "SOLVING FOR THE FRICTION FACTOR USING BI-SECTION\n"
            "************************************************\n";
    cout << f.biSectionalReport();

    cout << "Would you like to find the friction factor for a different Reynolds number?\n"
            "'y' or 'n'?\n";
    cin >> again;

    if (again == 'y') {
        main();
    }

    return 0;
}