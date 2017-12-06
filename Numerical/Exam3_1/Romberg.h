//
// Created by Steven Proctor on 4/3/17.
//

#ifndef EXAM3_1_ROMBERG_H
#define EXAM3_1_ROMBERG_H

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>

const int ARR = 15;

using namespace std;

class Romberg {
public:
    string integrate();                 //initiates integration process

private:
    long double I[ARR][ARR];            //Matrix of the integral of the function based on different step sizes using trapezoidal method
    long double step;                   //step size for to integrate by
    long double accError = .000001;     //the acceptable error, or desired accuracy for the integral
    long double aprxError;              //the approximate error for the given integral
    long double lftBnd, rghtBnd;        //left and right bounds of the integral
    long double n = 1;                  //number of intervals to integrate by
    long double rom_I;                  //the final area under the curve

    long double f(long double);         //function to be integrated
    long double trpzArea();             //determines the area based on trapezoidal method
    string fstring();                   //returns a string of the function
    void getBounds();                   //get the left and right integral bounds from user
    bool checkError(int);               //checks if the error is within desired accuracy
};

/*
 * initiates integration process
 * calls getBounds() and loops the integration process until desired accuracy is achieved
 * outputs the results of the integration
 */
string Romberg::integrate() {
    stringstream ss;

    cout << endl << endl << endl;
    cout << "\n************************************";
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
 */
bool Romberg::checkError(int i) {
    aprxError = 0;

    aprxError = (I[0][i] - I[1][i-1]) / (I[0][i]);

    return abs(aprxError) > accError;
}


/*
 * returns the area under the curve based on the trapezoidal method
 */
long double Romberg::trpzArea() {
    long double area = 0;
    step = (rghtBnd - lftBnd) / n;

    for (long double i = lftBnd; i < rghtBnd; i += step) {
        area += step * ((f(i) + f(i+step))/2.0);
    }

    return area;
}

#endif //EXAM3_1_ROMBERG_H
