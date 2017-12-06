#include <iostream>
#include "midMethod.h"
#include "derivCond.h"

using namespace std;

int main() {

    midMethod M;
    derivCond D;

    cout << endl;
    M.solve();
    cout << endl << endl << endl;
    D.solve();

    return 0;
}