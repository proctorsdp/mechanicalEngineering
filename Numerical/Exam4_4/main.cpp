#include <iostream>
#include "shootingMethod.h"
#include "finiteDifference.h"

using namespace std;

int main() {

    shootingMethod S;
    finiteDifference F;

    cout << endl;
    S.shoot();
    cout << endl << endl;

    cout << endl;
    F.solve();
    cout << endl << endl;

    return 0;
}