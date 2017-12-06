//
// Created by Steven Proctor on 2/13/17.
//

#ifndef HW5_NEWTONMETHOD_H
#define HW5_NEWTONMETHOD_H


#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class newtonMethod {
public:
    string newtonMax();

private:
    double x0;
    vector<double> max;
    int iter = 1000;
    double error = .00001;

    void getBounds();
    bool checkError(int);
    void findMax();
    double f(double);
    double df(double);
    double d2f(double);
    string newtonTitle();
};

double newtonMethod::f(double x) {
    return -pow(x,4) - 2 * pow(x,3) - 8 * pow(x,2) - 5 * x;
}

double newtonMethod::df(double x) {
    return - 4 * pow(x,3) - 6 * pow(x,2) - 16 * x - 5;
}

double newtonMethod::d2f(double x) {
    return - 12 * pow(x,2) - 12 * x - 16;
}

void newtonMethod::getBounds() {
    cout << "Enter an x-value for an initial guess\n";
    cin >> x0;
    cout << endl;
}

bool newtonMethod::checkError(int i) {
    if (i >= iter) {
        return true;
    }
    else {
        return  abs((max[max.size()] - max[max.size() - 1]) / max[max.size()]) < error;
    }
}

void newtonMethod::findMax() {
    getBounds();
    int i = 1;
    max.push_back(x0 - (df(x0)/d2f(x0)));

    do {
        max.push_back(max.back() - (df(max.back()) / d2f(max.back())));
        i++;
    } while (!checkError(i));
}

string newtonMethod::newtonTitle() {
    stringstream ss;

    ss << endl;
    ss << "FINDING THE MAXIMUM VALUE OF A FUNCTION USING NEWTON METHOD\n";
    ss << "***********************************************************\n" << endl;

    ss << "Function: f(x) = -x^4 - 2 * x^3 - 8 * x^2 - 5 * x\n";
    ss << "Acceptable Error: .001%\n" << endl;

    return ss.str();
}

string newtonMethod::newtonMax() {
    stringstream ss;

    cout << newtonTitle() << endl;
    findMax();

    ss << "=========================================================\n";
    ss << "The max value for the function occurs at x = " << max.back() << endl;
    ss << "Where f(" << max.back() << ") = " << f(max.back()) << endl;
    ss << "=========================================================\n";

    return ss.str();
}


#endif //HW5_NEWTONMETHOD_H
