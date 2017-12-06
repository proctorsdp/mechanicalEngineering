#include <iostream>
#include "romberg.h"
#include "centralDerivation.h"

using namespace std;

int main() {

    Romberg R;
    centralDerivation D;

    cout << R.integrate() << endl;

    cout << endl << endl << endl;
    cout << endl << endl << endl;

    cout << "\n********************************************";
    cout << "\nDERIVING USING THE CENTRAL DERIVATION METHOD";
    cout << "\n********************************************";
    cout << endl << endl;

    D.tabulateDerivative();

    cout << endl << endl;
    cout << "Data saved to file rocketAcceleration.csv\n";
    cout << endl;

    return 0;
}