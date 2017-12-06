/*
 * 13.8 Employ the following methods to fi nd the maximum of the function from Prob. 13.7:
    (a) Golden-section search (xl = -2, xu = 1, es = 1%).
    (b) Parabolic interpolation (x0 = -2, x1 = -1, x2 = 1, iterations = 4). Select new points sequentially as in the secant method.
    (c) Newton’s method (x0 = -1, es = 1%).

    f (x) = -x^4 - 2 * x^3 - 8 * x^2 - 5 * x
 */


#include <iostream>
#include "goldenSection.h"
#include "parabolicInterp.h"
#include "newtonMethod.h"

using namespace std;

int main() {

    goldenSection G;
    cout << G.goldMax() << endl << endl << endl << endl;

    parabolicInterp P;
    cout << P.parabolaMax() << endl << endl << endl << endl;

    newtonMethod N;
    cout << N.newtonMax() << endl << endl << endl << endl;

    return 0;
}