#include <iostream>
#include "doubleTrpz.h"

using namespace std;

int main() {

    trpzMethod T;

    cout << T.integrate() << endl;

    return 0;
}