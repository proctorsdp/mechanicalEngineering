/*
 * 14.9 Develop a program using a programming or macro language
    to implement the random search method. Design the subprogram so
    that it is expressly designed to locate a maximum. Test the program
    with f(x, y) from Prob. 14.7. Use a range of -2 to 2 for both x and y.

    f(x,y) = 4 * x + 2 * y + x^2 - 2 * x^4 + 2 * x * y - 3 * y^2
 */


#include <iostream>
#include "randomSearch.h"

using namespace std;

int main() {

    randomSearch R;
    cout << R.randomMax() << endl << endl;


    return 0;
}