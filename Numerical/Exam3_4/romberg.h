//
// Created by Steven Proctor on 4/6/17.
//

#ifndef EXAM3_4_ROMBERG_H
#define EXAM3_4_ROMBERG_H


#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>

const int ARR = 15;

using namespace std;

class Romberg {
public:
    string integrate();

private:
    long double I[ARR][ARR];
    long double step;
    long double accError = .000001;
    long double aprxError;
    long double lftBnd, rghtBnd;
    long double n = 1;
    long double rom_I;

    long double f(long double);
    long double trpzArea();
    string fstring();
    void getBounds();
    bool checkError(int);
};


string Romberg::integrate() {
    stringstream ss;

    cout << endl << endl << endl;
    cout << "\nINTEGRATING USING THE ROMBERG METHOD";
    cout << "\n************************************";

    getBounds();
    I[0][0] = trpzArea();

    int i = 0;
    while (checkError(i)) {
        i++;
        n = pow(2,i);
        I[i][0] = trpzArea();
        for (int j = 1; j < i + 1; j++) {
            int k = i - j;
            I[k][j] = (pow(4,j) * I[k+1][j-1] - I[k][j-1])/(pow(4,j) - 1);
        }
    }

    rom_I = I[0][i];

    ss << endl;
    ss << "\nFunction: " << fstring();
    ss << "\nBounds: " << lftBnd << " to " << rghtBnd;
    ss << "\nNumber of Intervals: " << n;
    ss << "\nDesired Accuracy: " << accError * 100 << "%";
    ss << endl;
    ss << "\n==========================================";
    ss << "\nArea under the curve: " << setprecision(15) << rom_I;
    ss << "\nApproximate Error: " << aprxError * 100 << "%";
    ss << "\n==========================================";

    return ss.str();
}


/*
 * returns the value of f(x) for a given x
 */
long double Romberg::f(long double x) {
    return x * exp(-2.0*x) * cos(2.0*x);
}


/*
 * returns the value of df4_d4x for a given x
 */
string Romberg::fstring() {
    stringstream ss;
    ss << "f(x) = x * e^(-2*x) * cos(2*x)";
    return ss.str();
}


/*
 * obtains the integration bounds from the user
 */
void Romberg::getBounds() {
    cout << "\nEnter the left bound of the integral:\n";
    cin >> lftBnd;
    cout << "\nEnter the right bound of the integral:\n";
    cin >> rghtBnd;
}


/*
 * returns true if the approximate error of the integral is less than the acceptable error, false otherwise
 * computes the average value of df4_d4x over the integration bounds in calculating the approximate error
 */
bool Romberg::checkError(int i) {
    aprxError = 0;

    aprxError = (I[0][i] - I[1][i-1]) / (I[0][i]);

    return abs(aprxError) > accError;
}



long double Romberg::trpzArea() {
    long double area = 0;
    step = (rghtBnd - lftBnd) / n;

    for (long double i = lftBnd; i < rghtBnd; i += step) {
        area += step * ((f(i) + f(i+step))/2.0);
    }

    return area;
}


#endif //EXAM3_4_ROMBERG_H
