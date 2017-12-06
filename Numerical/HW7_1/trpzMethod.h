//
// Created by Steven Proctor on 3/26/17.
//

#ifndef HW7_1_TRPZMETHOD_H
#define HW7_1_TRPZMETHOD_H

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;

class trpzMethod {
public:
    string integrate();             //public function that begins the integration process

private:
    double n = 64;                  //number of intervals between the integration bounds
    double step;                    //step size to move from one interval to the next
    double accError = .001;         //the acceptable error, program will finish when appError < accError
    double lftBnd, rghtBnd;         //the left and right bound of the integral
    double I = 0;                   //the area under the curve, i.e. the integral
    double appError = 0;            //the approximate error of the integration

    double f(double);               //returns the value of f at a given location
    double df2_d2x(double);         //returns the value of df2_d2x at a given location
    string fstring();               //returns a string of the function f
    double trpzArea();              //returns the area under the curve f using the trapezoid method
    void getBounds();               //obtains the bounds for the integral from the user
    bool checkError();              //checks to see if appError < accError
};


/*
 * call getBounds();
 * solves for the area under the curve until the accError is met
 * returns the area under the curve and the error of the solution
 */
string trpzMethod::integrate() {
    stringstream ss;

    getBounds();
    step = (rghtBnd - lftBnd) / n;
    I = trpzArea();

    while (checkError()) {
        n *= 2;
        step = (rghtBnd - lftBnd) / n;
        I = trpzArea();
    }

    ss << endl << endl << endl;
    ss << "\nINTEGRATING USING THE TRAPEZOID METHOD";
    ss << "\n**************************************";
    ss << endl;
    ss << "\nFunction: " << fstring();
    ss << "\nBounds: " << lftBnd << " to " << rghtBnd;
    ss << "\nNumber of Intervals: " << n;
    ss << endl;
    ss << "\n======================================";
    ss << "\nArea under the curve: " << I;
    ss << "\nApproximate Error: " << appError << "%";
    ss << "\n======================================";

    return ss.str();
}



/*
 * returns the value of f(x) for a given x
 */
double trpzMethod::f(double x) {
    return x * exp(-2*x) * exp(-pow(x,2)) * cos(3*x);
}



/*
 * returns the value of df4_d4x for a given x
 */
string trpzMethod::fstring() {
    stringstream ss;
    ss << "f(x) = x * e^(-2*x) * e^(-x^2) * cos(3*x)";
    return ss.str();
}



/*
 * returns the value of df2_d2x for a given x
 */
double trpzMethod::df2_d2x(double x) {
    return exp(-x * (x + 2)) * (6 * (2 * x * (x + 1) - 1) * sin(3 * x) + (x * (4 * x * (x + 2) - 11) - 4) * cos(3 * x));
}



/*
 * returns the area under the curve using trapezoid method
 */
double trpzMethod::trpzArea() {
    double area = 0;

    for (double i = lftBnd; i <= rghtBnd; i += step) {
        area += step * ((f(i) + f(i+step))/2);
    }

    return area;
}



/*
 * returns true if the approximate error of the integral is less than the acceptable error, false otherwise
 * computes the average value of df4_d4x over the integration bounds in calculating the approximate error
 */
bool trpzMethod::checkError() {
    double eArea = 0;
    double average = 0;
    appError = 0;

    for (double i = lftBnd; i <= rghtBnd; i += step) {
        eArea += step * ((df2_d2x(i) + df2_d2x(i+step))/2);
    }

    average = eArea/(rghtBnd-lftBnd);
    appError = -(100/12) * average * pow(step,3);

    return appError > accError;
}



/*
 * obtains the integration bounds from the user
 */
void trpzMethod::getBounds() {
    cout << "\nEnter the left bound of the integral:\n";
    cin >> lftBnd;
    cout << "\nEnter the right bound of the integral:\n";
    cin >> rghtBnd;
}

#endif //HW7_1_TRPZMETHOD_H
