#include <iostream>
#include "BruteMinSearch.h"
#include "GradientSearch.h"

using namespace std;

int main() {
    cout << endl;

    BruteMinSearch B;
    cout << B.bruteSearch() << endl;

    cout << endl << endl;

    GradientSearch G;
    cout << G.gradientSearch() << endl;


    return 0;
}