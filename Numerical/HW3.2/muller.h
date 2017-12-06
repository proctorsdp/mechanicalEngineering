//
// Created by Steven Proctor on 2/1/17.
//

#ifndef HW3_2_MULLER_H
#define HW3_2_MULLER_H

#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#include <string>
#include <complex>

using namespace std;

class muller {
public:
    void mullerSolver();

private:
    double step = 0.1;
    double criteria = .001;
    double stopPoint = .01;
    vector<float> root;

    float f(double);
    string fString();
    float mullerRoots();
    float getGuess();
    bool checkError();
};

float muller::f(double x) {
    return pow(x,3) - pow(x,2) + 2 * x - 2;
}

string muller::fString() {
    stringstream ss;
    ss << "f(x) = x^3 - x^2 + 2x - 2\n";
    return ss.str();
}

float muller::mullerRoots() {
    float h0, h1, d0, d1, a, b, c;
    root.push_back(getGuess());
    float x2 = root.back();
    float x1 = x2 + step * x2;
    float x0 = x2 - step * x2;
    float x3;
    complex<float> junk, rad, bottom;
    bool swap = false;

    do {
        if (swap) {
            x0 = x1;
            x1 = x2;
            x2 = root.back();
        }

        h0 = x1 - x0;
        h1 = x2 - x1;

        d0 = (f(x1) - f(x0)) / h0;
        d1 = (f(x2) - f(x1)) / h1;

        a = (d1 - d0) / (h1 + h0);
        b = a * h1 + d1;
        c = f(x2);

        junk = pow(b,2) - 4 * a * c;
        rad = sqrt(junk);

        if (abs(b + rad) > abs(b - rad)) {
            bottom = b + rad;
        }
        else {
            bottom = b - rad;
        }

        x3 = x2 - ((2 * c) / real(bottom));
        root.push_back(x3);
        swap = true;

    } while (!checkError());

    return root.back();
}

bool muller::checkError() {
    double error;
    error = abs((real(root.back()) - real(root[root.size() - 1])) / real(root.back())) * 100;
    return error < stopPoint && abs(f(real(root.back()))) < criteria;
}

float muller::getGuess() {
    double guess;
    cout << "Enter an initial guess for the root of the equation:\n";
    cin >> guess;
    cout << endl << endl;
    return guess;
}

void muller::mullerSolver() {
    cout << endl
         << "USING MULLER METHOD TO FIND ROOTS OF A FUNCTION\n"
         << "***********************************************\n"
         << endl << fString();

    float root = mullerRoots();

    cout << "-------------------------------------------------------------------\n";
    cout << "The root of the equation: " << fString();
    cout << "Is located at x = " << root << " where f(" << root << ") = " << f(root) << endl;
    cout << "-------------------------------------------------------------------\n" << endl << endl;
}

#endif //HW3_2_MULLER_H
