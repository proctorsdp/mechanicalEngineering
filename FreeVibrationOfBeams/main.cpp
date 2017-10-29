// // main.cpp // Beam Theory // // Created by Steven Proctor on 12/4/16.

// Copyright © 2016 Steven Proctor. All rights reserved. //

#include <iostream> 
#include "PinnedPinned.h" 
#include "FreeFree.h" 
#include "FixedFixed.h" 
#include "FixedFree.h"

using namespace std;

int main() {

    double E, row, L, h, b;
    char choice = 'y';

    cout << "Welcome to the Euler-Bernoulli Beam Solver!\n";
    cout << "*******************************************\n\n";
    cout << "First: Enter the properites of the beam\n";
    cout << "Second: Select a beam configuration\n\n\n";

    while (choice != 'n') {

        cout << "Enter Young's Modulus: (GPa)\n";
        cin >> E;
        cout << endl;

        cout << "Enter density: (kg/m^3)\n";
        cin >> row;
        cout << endl;

        cout << "Enter length: (m)\n";
        cin >> L;
        cout << endl;

        cout << "Enter thickness: (m)\n";
        cin >> h;
        cout << endl;

        cout << "Enter width: (m)\n";
        cin >> b;
        cout << endl;

        cout << "Select a type of Beam:\n";
        cout << "a: Pinned-Pinned\n";
        cout << "b: Free-Free\n";
        cout << "c: Fixed-Fixed\n";
        cout << "d: Fixed-Free\n";
        cin >> choice;

        while (choice != 'a' && choice != 'b' && choice != 'c' && choice != 'd') {
            cout << "Please enter 'a', 'b', 'c', or 'd'\n";
            cin >> choice;
        }

        cout << endl << endl;

        if (choice == 'a') { PinnedPinned PP(E, row, L, h, b); }
        else if (choice == 'b') {

            FreeFree FF(E, row, L, h, b);
        } else if (choice == 'c') {

            FixedFixed XX(E, row, L, h, b);
        } else {

            FixedFree XF(E, row, L, h, b);
        }

        cout << "Would you like to analyze another beam? 'y' or 'n'?\n";
        cin >> choice;
        cout << endl << endl << endl;

    }

    return 0;
}