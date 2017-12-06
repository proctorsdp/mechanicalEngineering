//
// Created by Steven Proctor on 3/26/17.
//

#ifndef HW7_2_SIMPSON3_8METHOD_H
#define HW7_2_SIMPSON3_8METHOD_H

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;

class simpson3_8Method {
public:
    string integrate();             //public function that begins the integration process

private:
    double n = 3;                   //number of intervals between the integration bounds
    double step;                    //step size to move from one interval to the next
    double accError = .001;         //the acceptable error, program will finish when appError < accError
    double lftBnd, rghtBnd;         //the left and right bound of the integral
    double I = 0;                   //the area under the curve, i.e. the integral
    double appError = 0;            //the approximate error of the integration

    double f(double);               //returns the value of f at a given location
    double df4_d4x(double);         //returns the value of d4f_d4x at a given location
    string fstring();               //returns a string of the function f
    double simp3_8Area();           //returns the area under the curve f using the simpsons 3/8 method
    void getBounds();               //obtains the bounds for the integral from the user
    bool checkError();              //checks to see if appError < accError
};


/*
 * call getBounds();
 * solves for the area under the curve until the accError is met
 * returns the area under the curve and the error of the solution
 */
string simpson3_8Method::integrate() {
    stringstream ss;

    getBounds();
    step = (rghtBnd - lftBnd) / n;
    I = simp3_8Area();

    while (checkError()) {
        n *= 2;
        step = (rghtBnd - lftBnd) / n;
        I = simp3_8Area();
    }

    ss << endl << endl << endl;
    ss << "\nINTEGRATING USING THE SIMPSON'S 3/8 METHOD";
    ss << "\n******************************************";
    ss << endl;
    ss << "\nFunction: " << fstring();
    ss << "\nBounds: " << lftBnd << " to " << rghtBnd;
    ss << "\nNumber of Intervals: " << n;
    ss << endl;
    ss << "\n==========================================";
    ss << "\nArea under the curve: " << I;
    ss << "\nApproximate Error: " << appError << "%";
    ss << "\n==========================================";

    return ss.str();
}



/*
 * returns the value of f(x) for a given x
 */
double simpson3_8Method::f(double x) {
    return x * exp(-2*x) * exp(-pow(x,2)) * cos(3*x);
}



/*
 * returns the value of df4_d4x for a given x
 */
string simpson3_8Method::fstring() {
    stringstream ss;
    ss << "f(x) = x * e^(-2*x) * e^(-x^2) * cos(3*x)";
    return ss.str();
}



/*
 * returns the value of df4_d4x for a given x
 */
double simpson3_8Method::df4_d4x(double x) {
    return exp(-x*(x+2)) * (12*(2*x*(x*(4*x*(x+3)-9)-23)+3)*sin(3*x) + (x*(8*x*(x*(2*x*(x+4)-25)-70)+121)+232)*cos(3*x));
}



/*
 * returns the area under the curve using simpson's 3/8 method
 */
double simpson3_8Method::simp3_8Area() {
    double area = 0;

    for (double i = lftBnd; i < rghtBnd; i += (3*step)) {
        area += 3*step * ((f(i) + 3*f(i+step) + 3*f(i+(2*step)) + f(i+(3*step)))/8);
    }

    return area;
}



/*
 * returns true if the approximate error of the integral is less than the acceptable error, false otherwise
 * computes the average value of df4_d4x over the integration bounds in calculating the approximate error
 */
bool simpson3_8Method::checkError() {
    double eArea = 0;
    double average = 0;
    appError = 0;

    for (double i = lftBnd; i < rghtBnd; i += (3*step)) {
        eArea += 3*step * ((df4_d4x(i) + 3*df4_d4x(i+step) + 3*df4_d4x(i+(2*step)) + df4_d4x(i+(3*step)))/8);
    }

    average = eArea/(rghtBnd-lftBnd);
    appError = -(300/80) * average * pow((3*step),5);

    return abs(appError) > accError;
}



/*
 * obtains the integration bounds from the user
 */
void simpson3_8Method::getBounds() {
    cout << "\nEnter the left bound of the integral:\n";
    cin >> lftBnd;
    cout << "\nEnter the right bound of the integral:\n";
    cin >> rghtBnd;
}

#endif //HW7_2_SIMPSON3_8METHOD_H
