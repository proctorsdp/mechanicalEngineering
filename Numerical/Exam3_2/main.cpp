#include <iostream>
#include "centralDerivation.h"

using namespace std;

int main() {

    centralDerivation D;

    D.centralDerive();

    cout << endl << endl;

    D.ouputCentral();

    cout << endl << endl << endl << endl;

    D.richardDerive();

    cout << endl << endl;

    D.outputRichard();

    return 0;
}