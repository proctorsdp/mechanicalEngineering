//
// Created by Steven Proctor on 4/5/17.
//

#ifndef EXAM3_3_DOUBLETRPZ_H
#define EXAM3_3_DOUBLETRPZ_H

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

class trpzMethod {
public:
    string integrate();                                 //public function that begins the integration process

private:
    long double n = 1000;                               //number of intervals between the integration bounds
    long double step;                                   //step size to move from one interval to the next
    long double lftBnd, rghtBnd, btmBnd, topBnd;        //the left and right bound of the integral
    long double I = 0;                                  //the area under the curve, i.e. the integral
    long double trueI = 64.0/3.0;                       //true value of integral;

    long double f(long double, long double);            //returns the value of f at a given location
    string fstring();                                   //returns a string of the function f
    long double trpzArea();                             //returns the area under the curve f using the trapezoid method
    void getBounds();                                   //obtains the bounds for the integral from the user

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

    ss << endl;
    ss << "\nFunction: " << fstring();
    ss << "\nx-Bounds: " << lftBnd << " to " << rghtBnd;
    ss << "\ny-Bounds: " << btmBnd << " to " << topBnd;
    ss << "\nNumber of Intervals: " << n;
    ss << endl;
    ss << "\nIntegrating with respect to x and then y";
    ss << "\n==========================================";
    ss << "\nArea under the curve: " << setprecision(8) << I;
    if (lftBnd == 0 && rghtBnd == 4 && topBnd == 2 && btmBnd == -2) {
        ss << "\nAccuracy: " << abs((I-trueI)/trueI) * 100 << "%";
    }
    ss << "\n==========================================";

    return ss.str();
}



/*
 * returns the value of f(x) for a given x
 */
long double trpzMethod::f(long double x, long double y) {
    return pow(x,2) - 3 * pow(y,2) + x * pow(y,3);
}



/*
 * returns the value of f for a given x
 */
string trpzMethod::fstring() {
    stringstream ss;
    ss << "f(x,y) = x^2 - 2y^2 + xy^3";
    return ss.str();
}



/*
 * returns the area under the curve using trapezoid method
 */
long double trpzMethod::trpzArea() {
    long double area = 0;
    long double totArea = 0;

    for (long double j = btmBnd; j < topBnd; j += step) {
        area = 0;
        for (long double i = lftBnd; i < rghtBnd; i += step) {
            area += step * ((f(i,j) + f(i+step,j)) / 2.0);
        }
        totArea += (area * step);
    }

    return totArea;
}




/*
 * obtains the integration bounds from the user
 */
void trpzMethod::getBounds() {
    cout << "\nEnter the left x-bound of the integral:\n";
    cin >> lftBnd;
    cout << "\nEnter the right x-bound of the integral:\n";
    cin >> rghtBnd;
    cout << "\nEnter the bottom y-bound of the integral:\n";
    cin >> btmBnd;
    cout << "\nEnter the top y-bound of the integral:\n";
    cin >> topBnd;

}


#endif //EXAM3_3_DOUBLETRPZ_H
