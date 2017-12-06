//
// Created by Steven Proctor on 4/3/17.
//

#ifndef EXAM3_1_3_8_SIMPSONS_H
#define EXAM3_1_3_8_SIMPSONS_H


#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;

class simpson3_8Method {
public:
    string integrate();             //public function that begins the integration process

private:
    long double n = 3;                   //number of intervals between the integration bounds
    long double step;                    //step size to move from one interval to the next
    long double accError = .000001;      //the acceptable error, program will finish when appError < accError
    long double lftBnd, rghtBnd;         //the left and right bound of the integral
    vector<long double> I;                   //the area under the curve, i.e. the integral
    long double appError = 0;            //the approximate error of the integration

    long double f(long double);               //returns the value of f at a given location
    long double df4_d4x(long double);         //returns the value of d4f_d4x at a given location
    string fstring();               //returns a string of the function f
    long double simp3_8Area();           //returns the area under the curve f using the simpsons 3/8 method
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

    cout << endl << endl << endl;
    cout << "\n******************************************";
    cout << "\nINTEGRATING USING THE SIMPSON'S 3/8 METHOD";
    cout << "\n******************************************";

    getBounds();
    step = (rghtBnd - lftBnd) / n;
    I.push_back(simp3_8Area());

    do{
        n *= 2;
        step = (rghtBnd - lftBnd) / n;
        I.push_back(simp3_8Area());
    } while (checkError());

    ss << endl;
    ss << "\nFunction: " << fstring();
    ss << "\nBounds: " << lftBnd << " to " << rghtBnd;
    ss << "\nNumber of Intervals: " << n;
    ss << "\nDesired Accuracy: " << accError * 100 << "%";
    ss << endl;
    ss << "\n==============================================";
    ss << "\nArea under the curve: " << setprecision(15) << I.back();
    ss << "\nApproximate Error: " << (appError) * 100<< "%";
    ss << "\n==============================================";

    return ss.str();
}



/*
 * returns the value of f(x) for a given x
 */
long double simpson3_8Method::f(long double x) {
    return x * exp(-2.0*x) * cos(2.0*x);
}



/*
 * returns the value of df4_d4x for a given x
 */
string simpson3_8Method::fstring() {
    stringstream ss;
    ss << "f(x) = x * e^(-2*x) * cos(2*x)";
    return ss.str();
}



/*
 * returns the value of df4_d4x for a given x
 */
long double simpson3_8Method::df4_d4x(long double x) {
    return -64.0 * exp(-2.0 * x) * (sin(2.0 * x) + (x - 1.0) * cos(2.0 * x));
}



/*
 * returns the area under the curve using simpson's 3/8 method
 */
long double simpson3_8Method::simp3_8Area() {
    long double area = 0;

    for (long double i = lftBnd; i < rghtBnd; i += (3.0 * step)) {
        area += 3.0 * step * ((f(i) + 3.0 * f(i+step) + 3.0 * f(i+(2.0*step)) + f(i+(3.0*step)))/8.0);
    }

    return area;
}



/*
 * returns true if the approximate error of the integral is less than the acceptable error, false otherwise
 * computes the average value of df4_d4x over the integration bounds in calculating the approximate error
 */
bool simpson3_8Method::checkError() {
    long double eArea = 0;
    long double average = 0;
    appError = 0;

    for (long double i = lftBnd; i < rghtBnd; i += (3.0*step)) {
        eArea += 3.0*step * ((df4_d4x(i) + 3.0*df4_d4x(i+step) + 3.0*df4_d4x(i+(2.0*step)) + df4_d4x(i+(3.0*step)))/8.0);
    }

    average = eArea/(rghtBnd-lftBnd);
    appError = -(1.0/(6480.0 * pow(n,2.0))) * average * pow((rghtBnd-lftBnd),5.0);

    return abs(appError) > accError * I.back();
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


#endif //EXAM3_1_3_8_SIMPSONS_H
