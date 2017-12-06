//
// Created by Steven Proctor on 4/3/17.
//

#ifndef EXAM3_1_TRPZMETHOD_H
#define EXAM3_1_TRPZMETHOD_H


#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;

class trpzMethod {
public:
    string integrate();             //public function that begins the integration process

private:
    long double n = 10000;                  //number of intervals between the integration bounds
    long double step;                    //step size to move from one interval to the next
    long double accError = .000001;      //the acceptable error, program will finish when appError < accError
    long double lftBnd, rghtBnd;         //the left and right bound of the integral
    long double I = 0;                   //the area under the curve, i.e. the integral
    long double appError = 0;            //the approximate error of the integration
    bool skipError = false;

    long double f(long double);               //returns the value of f at a given location
    long double df2_d2x(long double);         //returns the value of df2_d2x at a given location
    string fstring();               //returns a string of the function f
    long double trpzArea();              //returns the area under the curve f using the trapezoid method
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

    cout << endl << endl << endl;
    cout << "\n**************************************";
    cout << "\nINTEGRATING USING THE TRAPEZOID METHOD";
    cout << "\n**************************************";

    getBounds();
    step = (rghtBnd - lftBnd) / n;
    I = trpzArea();

    while (checkError()) {
        n *= 2;
        step = (rghtBnd - lftBnd) / n;
        I = trpzArea();
    }

    ss << endl;
    ss << "\nFunction: " << fstring();
    ss << "\nBounds: " << lftBnd << " to " << rghtBnd;
    ss << "\nNumber of Intervals: " << n;
    if (!skipError) {ss << "\nDesired Accuracy: " << accError * 100 << "%";}
    ss << endl;
    ss << "\n==========================================";
    ss << "\nArea under the curve: " << setprecision(15) << I;
    ss << "\nApproximate Error: " << appError * 100 << "%";
    ss << "\n==========================================";

    return ss.str();
}



/*
 * returns the value of f(x) for a given x
 */
long double trpzMethod::f(long double x) {
    return x * exp(-2.0*x) * cos(2.0*x);
}



/*
 * returns the value of df4_d4x for a given x
 */
string trpzMethod::fstring() {
    stringstream ss;
    ss << "f(x) = x * e^(-2*x) * cos(2*x)";
    return ss.str();
}



/*
 * returns the value of df2_d2x for a given x
 */
long double trpzMethod::df2_d2x(long double x) {
    return -4.0 * exp(-2.0*x) * ((1.0 - 2.0*x) * sin(2.0*x) + cos(2.0*x));
}



/*
 * returns the area under the curve using trapezoid method
 */
long double trpzMethod::trpzArea() {
    long double area = 0;

    for (long double i = lftBnd; i < rghtBnd; i += step) {
        area += step * ((f(i) + f(i+step))/2.0);
    }

    return area;
}



/*
 * returns true if the approximate error of the integral is less than the acceptable error, false otherwise
 * computes the average value of df4_d4x over the integration bounds in calculating the approximate error
 */
bool trpzMethod::checkError() {
    long double eArea = 0;
    long double average = 0;
    appError = 0;

    for (long double i = lftBnd; i < rghtBnd; i += step) {
        eArea += step * ((df2_d2x(i) + df2_d2x(i+step))/2.0);
    }

    average = eArea/(rghtBnd-lftBnd);
    appError = -(1.0/(12.0*pow(n,2.0))) * average * pow((rghtBnd-lftBnd),3.0);
    appError /= I;

    if (skipError) {return false;}
    return abs(appError) > accError;
}



/*
 * obtains the integration bounds from the user
 */
void trpzMethod::getBounds() {
    char choice;
    cout << "\nEnter the left bound of the integral:\n";
    cin >> lftBnd;
    cout << "\nEnter the right bound of the integral:\n";
    cin >> rghtBnd;

    do {
        cout << "\nDo you want to integrate by step size, or accuracy? ('s' or 'a')\n";
        cin >> choice;
    } while (choice != 's' && choice != 'a');

    if (choice == 's') {
        cout << "\nEnter the desired number of intervals:\n";
        cin >> n;
        skipError = true;
    }
    else {
        cout << "\nEnter the desired accuracy: (Enter a percent %)\n";
        cin >> accError;
        accError /= 100.0;
        skipError = false;
    }
}


#endif //EXAM3_1_TRPZMETHOD_H
