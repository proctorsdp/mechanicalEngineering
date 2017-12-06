//
// Created by Steven Proctor on 4/5/17.
//

#ifndef EXAM3_2_CENTRALDERIVATION_H
#define EXAM3_2_CENTRALDERIVATION_H

#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <fstream>

using namespace std;

class centralDerivation {
public:
    void centralDerive();       //initiates the derivation using central derivative method
    void richardDerive();       //initiates the derivation using richardson extrapolation method
    void ouputCentral();        //outputs the derivative from 0 to .78 for central derivation
    void outputRichard();       //outputs the derivative from 0 to .78 for richardson extrapolation

private:
    long double step = .000001;     //step size to differentiate by to acheive desired accuracy at ends bounds
    string filenameC = "centralDerivative.csv";
    string filenameR = "richardDerivative.csv";

    long double f(long double);         //function to be derived
    long double fPrime(long double);    //the derivative of the function
    long double df_dx(long double);     //the central derivation of the function at a point
    string fString();                   //returns a string of the function
    long double richardExtrap(long double);     //the richard derivation of the function at a point
};


/*
 * returns the value of the function at a given value x
 */
long double centralDerivation::f(long double x) {
    return sqrt(pow(x,3) * exp(-2*x) * cos(2*x));
}


/*
 * returns the true derivative of the function at a given value x
 */
long double centralDerivation::fPrime(long double x) {
    return - sqrt(pow(x,3) * exp(-2*x) * cos(2*x)) * (2*x + 2*x*tan(2*x) - 3) / (2*x);
}


/*
 * returns the central derivative of the function at a given value x
 */
long double centralDerivation::df_dx(long double x) {
    return (-f(x+(2*step)) + 8 * f(x+step) - 8 * f(x-step) + f(x-(2*step))) / (12*step);
}


/*
 * returns a text string of the function
 */
string centralDerivation::fString() {
    stringstream ss;
    ss << "f(x) = sqrt( x^3 * e^-2x * cos(2x) )";
    return ss.str();
}


/*
 * returns the richard derivative of the function given a value x
 */
long double centralDerivation::richardExtrap(long double x) {
    return ((4/3) * ((f(x+step) - f(x-step))/(2*step))) - ((1/3) * ((f(x+(step/2)) - f(x-(step/2)))/(2*(step/2))));
}


/*
 * allows the user to obtain the central derivative of the function at any value between 0 and .8
 */
void centralDerivation::centralDerive() {
    cout << "\n****************************************************************";
    cout << "\nDERIVATION USING CENTRAL DIFFERENCE 2ND-ORDER TAYLOR'S EXPANSION";
    cout << "\n****************************************************************";
    cout << endl;
    cout << "\nFunction: " << fString() << endl;
    cout << endl;

    long double x = -1;

    while (x > .8 || x < 0) {
        cout << "\nEnter a x-value between 0 to .8:\n";
        cin >> x;
    }

    while (x != -1) {
        cout << "\n================================================================";
        cout << "\ndf_dx(" << x << ") = " << df_dx(x);
        cout << "\nStep Size: " << step;
        cout << "\nAccuracy: " << abs((fPrime(x) - df_dx(x)) / fPrime(x)) * 100 << "%";
        cout << "\n================================================================";
        cout << endl << endl;

        x = -1;

        while (x > .8 || x < 0) {
            cout << "\nEnter a x-value between 0 to .8: (-1 to quit)\n";
            cin >> x;
            if (x == -1) {break;}
        }
    }
}


/*
 * allows the user to obtain the richard derivative of the function at any value between 0 and .8
 */
void centralDerivation::richardDerive() {
    cout << "\n**************************************************";
    cout << "\nDERIVATION USING RICHARDSON'S EXTRAPOLATION METHOD";
    cout << "\n**************************************************";
    cout << endl;
    cout << "\nFunction: " << fString() << endl;
    cout << endl;

    step /= 10;

    long double x = -1;

    while (x > .8 || x < 0) {
        cout << "\nEnter a x-value between 0 to .8:\n";
        cin >> x;
    }

    while (x != -1) {
        cout << "\n==================================================";
        cout << "\ndf_dx(" << x << ") = " << richardExtrap(x);
        cout << "\nStep 1 Size: " << step;
        cout << "\nStep 2 Size: " << step/2;
        cout << "\nAccuracy: " << abs((fPrime(x) - richardExtrap(x)) / fPrime(x)) * 100 << "%";
        cout << "\n==================================================";
        cout << endl << endl;

        x = -1;

        while (x > .8 || x < 0) {
            cout << "\nEnter a x-value between 0 to .8: (-1 to quit)\n";
            cin >> x;
            if (x == -1) { break; }
        }
    }
}



/*
 * saves the central derivative of the function from 0 to .8 to a file
 */
void centralDerivation::ouputCentral() {
    fstream fout;
    fout.open(filenameC);

    cout << "Writing data to file " << filenameC << "...\n";
    fout << "x,df/dx,True f',Accuracy\n";

    for (double i = .1; i < .79; i += .01) {
        fout << i << "," << df_dx(i) << "," << fPrime(i) << "," << abs((fPrime(i) - df_dx(i)) / fPrime(i)) * 100 << endl;
    }

    fout.close();
    cout << "Data saved to file " << filenameC << endl;
}


/*
 * saves the richard derivative of the function from 0 to .8 to a file
 */
void centralDerivation::outputRichard() {
    fstream fout;
    fout.open(filenameR);

    cout << "Writing data to file " << filenameR << "...\n";
    fout << "x,df/dx,True f',Accuracy\n";

    for (double i = .1; i < .79; i += .01) {
        fout << i << "," << richardExtrap(i) << "," << fPrime(i) << "," << abs((fPrime(i) - richardExtrap(i)) / fPrime(i)) * 100  << endl;
    }

    fout.close();
    cout << "Data saved to file " << filenameR << endl;
}


#endif //EXAM3_2_CENTRALDERIVATION_H
