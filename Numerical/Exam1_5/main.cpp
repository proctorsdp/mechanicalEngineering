#include <iostream>
#include "quadraticSpline.h"

using namespace std;

int main() {

    quadraticSpline q;

    q.build();

    double val = 0;

    while (val != -99) {
        cout << "Enter a value of x (between 0 and 2) for which you want to know fs(x) (Quadratic Spline Function)\n";
        cin >> val;
        if (val == -99) {break;}
        cout << "fs(" << val << ") = " << q.fs(val) << endl << endl << endl;
        cout << "(Enter '-99' to quit)\n";
    }

    return 0;
}