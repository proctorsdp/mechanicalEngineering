//
// Created by Steven Proctor on 4/6/17.
//

#ifndef EXAM3_4_CENTRALDERIVATION_H
#define EXAM3_4_CENTRALDERIVATION_H


#include <iostream>
#include <string>
#include <cmath>
#include <sstream>

using namespace std;

class centralDerivation {
public:
    void centralDerive();

private:
    long double step = .000001;

    long double f(long double);
    long double fPrime(long double);
    long double df_dx(long double);
    string fString();

};


long double centralDerivation::f(long double x) {
    return sqrt(pow(x,3) * exp(-2*x) * cos(2*x));
}

long double centralDerivation::fPrime(long double x) {
    return - sqrt(pow(x,3) * exp(-2*x) * cos(2*x)) * (2*x + 2*x*tan(2*x) - 3) / (2*x);
}


long double centralDerivation::df_dx(long double x) {
    return (-f(x+(2*step)) + 8 * f(x+step) - 8 * f(x-step) + f(x-(2*step))) / (12*step);
}


string centralDerivation::fString() {
    stringstream ss;
    ss << "f(x) = sqrt( x^3 * e^-2x * cos(2x) )";
    return ss.str();
}


void centralDerivation::centralDerive() {
    cout << "\nDERIVATION USING CENTRAL DIFFERENCE 2ND-ORDER TAYLOR'S EXPANSION";
    cout << "\n****************************************************************";
    cout << endl;
    cout << "\nFunction: " << fString() << endl;
    cout << endl;

    long double x = -1;

    while (x > 1 || x < 0) {
        cout << "\nEnter a x-value between 0 to 1:\n";
        cin >> x;
    }

    while (x != -1) {
        cout << "\n================================================================";
        cout << "\ndf_dx(" << x << ") = " << df_dx(x);
        cout << "\nStep Size: " << step;
        cout << "\nAccuracy: " << abs((fPrime(x) - df_dx(x)) / fPrime(x)) * 100 << "%";
        cout << "\n================================================================";
        cout << endl << endl;

        x = -1;

        while (x > 1 || x < 0) {
            cout << "\nEnter a x-value between 0 to 1: (-1 to quit)\n";
            cin >> x;
            if (x == -1) {break;}
        }
    }
}



#endif //EXAM3_4_CENTRALDERIVATION_H
