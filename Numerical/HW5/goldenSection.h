//
// Created by Steven Proctor on 2/13/17.
//

#ifndef HW5_GOLDENSECTION_H
#define HW5_GOLDENSECTION_H

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;

class goldenSection {
public:
    string goldMax();

private:
    float left, right, max;
    float iter = 1000;
    float error = .00001;
    float goldR = (sqrt(5) - 1) / 2;

    void getBounds();
    bool checkError(int);
    void findMax();
    float f(float);
    string goldTitle();
};

float goldenSection::f(float x) {
    return -pow(x,4) - 2 * pow(x,3) - 8 * pow(x,2) - 5 * x;
}

void goldenSection::findMax() {
    getBounds();
    float step = goldR * (right - left);
    float x1 = left + step;
    float x2 = right - step;
    float f1 = f(x1);
    float f2 = f(x2);
    int i = 1;

    if (f1 > f2) {max = x1;}
    else {max = x2;}

    while (!checkError(i)) {
        step = goldR * step;
        if (f1 > f2) {
            max = x1;
            left = x2;
            x2 = x1;
            x1 = left + step;
            f2 = f1;
            f1 = f(x1);
        } else {
            max = x2;
            right = x1;
            x1 = x2;
            x2 = right - step;
            f1 = f2;
            f2 = f(x2);
        }
        i++;
    }
}

bool goldenSection::checkError(int i) {
    if (i >= iter) {
        return true;
    }
    else if (max != 0) {
        return ((1-goldR) * abs((right-left)/max)) < error;
    }
    else {
        return false;
    }
}

void goldenSection::getBounds() {
    cout << "Enter an x-value that is to the left of the maxima\n";
    cin >> left;
    cout << endl;

    cout << "Enter an x-value that is to the right of the maxima\n";
    cin >> right;
    cout << endl;

    if (left >= right) {
        cout << "Those values do not correctly bound the maxima. Please enter new values\n";
        getBounds();
    }
}

string goldenSection::goldTitle() {
    stringstream ss;

    ss << endl;
    ss << "FINDING THE MAXIMUM VALUE OF A FUNCTION USING GOLDEN-SECTION\n";
    ss << "************************************************************\n" << endl;

    ss << "Function: f(x) = -x^4 - 2 * x^3 - 8 * x^2 - 5 * x\n";
    ss << "Acceptable Error: .001%\n" << endl;

    return ss.str();
}

string goldenSection::goldMax() {
    stringstream ss;

    cout << goldTitle() << endl;
    findMax();

    ss << "=========================================================\n";
    ss << "The max value for the function occurs at x = " << max << endl;
    ss << "Where f(" << max << ") = " << f(max) << endl;
    ss << "=========================================================\n";

    return ss.str();
}

#endif //HW5_GOLDENSECTION_H
