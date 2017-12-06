//
// Created by Steven Proctor on 4/6/17.
//

#ifndef EXAM3_5_CENTRALDERIVATION_H
#define EXAM3_5_CENTRALDERIVATION_H


#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <fstream>

using namespace std;

class centralDerivation {
public:
    void centralDerive();               //Allows the user to obtain the derivative at a specific point
    void tabulateDerivative();          //Outputs the derivate over a given range

private:
    long double step = .05;             //step size of iterations
    long double u = 1800;               //velocity of expelled fuel
    long double m = 160000;             //initial mass of rocket
    long double q = 2500;               //fuel consumption rate
    long double g = 9.81;               //gravitational acceleration

    long double f(long double);         //contains function for upward velocity
    long double fPrime(long double);    //contains true derivative of f
    long double df_dx(long double);     //estimates the derivative of f
    string fString();                   //returns string of function f

};


/*
 * returns the upward velocity of the rocket given a time t
 */
long double centralDerivation::f(long double t) {
    return u * log(m/(m-q*t)) - g*t;
}


/*
 * returns the true acceleration of the rocket given time t
 */
long double centralDerivation::fPrime(long double x) {
    return (-9.81*x - 1172.16) / (x - 64);
}


/*
 * returns the central derivative estimate of the acceleration given time t
 */
long double centralDerivation::df_dx(long double x) {
    return (-f(x+(2*step)) + 8 * f(x+step) - 8 * f(x-step) + f(x-(2*step))) / (12*step);
}


/*
 * returns a text string of the function for upward velocity
 */
string centralDerivation::fString() {
    stringstream ss;
    ss << "v(t) = u * ln(m/(m-q*t)) - g*t";
    return ss.str();
}


/*
 * saves the acceleration data to a .csv file
 */
void centralDerivation::tabulateDerivative() {
    //cout << "Time:" << setw(20) << "Acceleration:" << endl;
    //cout << "-----" << setw(20) << "-------------" << endl;
    fstream fout;
    fout.open("rocketAcceleration.csv");
    fout << "Time (s),Acc. (m/s^2), True Acc.,% Error" << endl;
    for (double x = 0; x <= 30 + step; x += step) {
        //cout << setprecision(5) << x << setw(20) << df_dx(x) << endl;
        fout << x << "," << df_dx(x) << "," << fPrime(x) << "," << abs((fPrime(x) - df_dx(x)) / fPrime(x)) * 100 << endl;
    }
    fout.close();
}


/*
 * allows the user to enter any time t to obtain the acceleration at the time
 * NOT USED FOR THIS PROBLEM
 */
void centralDerivation::centralDerive() {
    cout << "\n****************************************************************";
    cout << "\nDERIVATION USING CENTRAL DIFFERENCE 2ND-ORDER TAYLOR'S EXPANSION";
    cout << "\n****************************************************************";
    cout << endl;
    cout << "\nFunction: " << fString() << endl;
    cout << endl;

    long double x;

        cout << "\nEnter a x-value between 0 to 30:\n";
        cin >> x;


    while (x != -1) {
        cout << "\n================================================================";
        cout << "\ndf_dx(" << x << ") = " << df_dx(x);
        cout << "\nStep Size: " << step;
        cout << "\nAccuracy: " << abs((fPrime(x) - df_dx(x)) / fPrime(x)) * 100 << "%";
        cout << "\n================================================================";
        cout << endl << endl;

        x = -1;

        while (x > 30 || x < 0) {
            cout << "\nEnter a x-value between 0 to 1: (-1 to quit)\n";
            cin >> x;
            if (x == -1) {break;}
        }
    }
}



#endif //EXAM3_5_CENTRALDERIVATION_H
