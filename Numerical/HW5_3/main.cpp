/*
 * 14.10 The grid search is another brute force approach to optimization.
    The two-dimensional version is depicted in Fig. P14.10. The x
    and y dimensions are divided into increments to create a grid. The
    function is then evaluated at each node of the grid. The denser the
    grid, the more likely it would be to locate the optimum.
    Develop a program using a programming or macro language to
    implement the grid search method. Design the program so that it is
    expressly designed to locate a maximum. Test it with the same
    problem as Example 14.1.

    f(x,y) = y - x - 2 * x^2 - 2 * x * y - y^2
 */

#include <iostream>
#include "gridSearch.h"

using namespace std;

int main() {

    gridSearch G;
    cout << G.gridMax() << endl << endl;

    return 0;
}