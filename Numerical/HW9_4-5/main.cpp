#include <iostream>
#include "Liebmann.h"

using namespace std;

int main() {

    Liebmann L;
    char entry;

    do {
        L.solve();
        cout << endl << endl;
        cout << "\nWould you like to run the Liebmann solver again? ('y' or 'n')\n";
        do { cin >> entry; } while (entry != 'y' && entry !='n');
    } while (entry == 'y');

    return 0;
}