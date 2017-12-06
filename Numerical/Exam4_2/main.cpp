#include <iostream>
#include "midMethod.h"
#include "withRod.h"

using namespace std;

int main() {

    midMethod M;
    rodMethod R;

    cout << endl;
    M.solve();
    cout << endl;

    cout << endl;
    R.solve();
    cout << endl;

    return 0;
}