//
// Created by Steven Proctor on 2/13/17.
//

#ifndef HW5_PARABOLICINTERP_H
#define HW5_PARABOLICINTERP_H

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class parabolicInterp {
public:
    string parabolaMax();

private:
    double x0, x1, x2;
    vector<double> max;
    int iter = 1000;
    double error = .00001;
    double breakPoint = pow(10,-20);

    void getBounds();
    bool checkError(int);
    void findMax();
    double f(double);
    string parabolaTitle();
};

double parabolicInterp::f(double x) {
    return -pow(x,4) - 2 * pow(x,3) - 8 * pow(x,2) - 5 * x;
}

void parabolicInterp::getBounds() {
    cout << "Enter an x-value for an initial guess\n";
    cin >> x0;
    cout << endl;

    cout << "Enter an x-value for a second initial guess\n";
    cin >> x1;
    cout << endl;

    cout << "Enter an x-value for a third initial guess\n";
    cin >> x2;
    cout << endl;

    if (x0 == x1 || x0 == x2 || x1 == x2) {
        cout << "None of the initial guesses can have the same value. Please enter new guesses.\n";
        getBounds();
    }
}

bool parabolicInterp::checkError(int i) {
    if (i >= iter) {
        return true;
    }
    else {
        return  abs((max[max.size()] - max[max.size() - 1]) / max[max.size()]) < error;
    }
}

void parabolicInterp::findMax() {
    getBounds();
    int i = 1;
    double top = f(x0) * (pow(x1,2) - pow(x2,2)) + f(x1) * (pow(x2,2) - pow(x0,2)) + f(x2) * (pow(x0,2) - pow(x1,2));
    double bottom = 2 * f(x0) * (x1 - x2) + 2 * f(x1) * (x2 - x0) + 2 * f(x2) * (x0 - x1);
    max.push_back(top/bottom);

    do {
        if (max.back() > x1) { x0 = x1; }
        else { x2 = x1; }
        x1 = max.back();

        top = f(x0) * (pow(x1, 2) - pow(x2, 2)) + f(x1) * (pow(x2, 2) - pow(x0, 2)) + f(x2) * (pow(x0, 2) - pow(x1, 2));
        bottom = 2 * f(x0) * (x1 - x2) + 2 * f(x1) * (x2 - x0) + 2 * f(x2) * (x0 - x1);
        //if (abs(bottom) < breakPoint) {break;}
        max.push_back(top / bottom);
        i++;
    } while (!checkError(i));
}

string parabolicInterp::parabolaTitle() {
    stringstream ss;

    ss << endl;
    ss << "FINDING THE MAXIMUM VALUE OF A FUNCTION USING PARABOLIC-INTERPOLATION\n";
    ss << "*********************************************************************\n" << endl;

    ss << "Function: f(x) = -x^4 - 2 * x^3 - 8 * x^2 - 5 * x\n";
    ss << "Acceptable Error: .001%\n" << endl;

    return ss.str();
}

string parabolicInterp::parabolaMax() {
    stringstream ss;

    cout << parabolaTitle() << endl;
    findMax();

    ss << "=========================================================\n";
    ss << "The max value for the function occurs at x = " << max.back() << endl;
    ss << "Where f(" << max.back() << ") = " << f(max.back()) << endl;
    ss << "=========================================================\n";

    return ss.str();
}

#endif //HW5_PARABOLICINTERP_H
