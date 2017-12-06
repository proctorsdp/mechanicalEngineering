#include <iostream>
#include "3_8_Simpsons.h"
#include "trpzMethod.h"
#include "Romberg.h"

using namespace std;

int main() {

    simpson3_8Method S;
    trpzMethod T1, T2;
    Romberg R;

    cout << S.integrate() << endl;

    cout << T1.integrate() << endl;

    cout << T2.integrate() << endl;

    cout << R.integrate() << endl;


    return 0;
}