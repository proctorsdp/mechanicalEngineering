#include <iostream>
#include "simpson3_8Method.h"

using namespace std;

int main() {

    simpson3_8Method S;

    cout << S.integrate() << endl;

    return 0;
}