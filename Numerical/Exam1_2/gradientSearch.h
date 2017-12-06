//
// Created by Steven Proctor on 3/16/17.
//

#ifndef EXAM1_2_GRADIENTSEARCH_H
#define EXAM1_2_GRADIENTSEARCH_H

#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;

class GradientSearch {
public:
    string gradientSearch();    //returns the results of a gradient search to find the maxima

private:
    double accError = .000001;   //the acceptable error that tells the program to stop
    double maxF = -999999;      //stores the maxima
    double maxX1 = 1;           //stores the x1 value corresponding to the maxima
    double maxX2 = 1;           //stores the x2 value corresponding to the maxima
    double maxX3 = 1;           //stores the x3 value corresponding to the maxima
    double srchBnd = 5;         //The bounds across which the h-axis is traveled
    double incr = .5;           //The step sized used to increment across the h-axis
    double smallSlope = .00001;   //The criteria at which the srchBnd and incr are decreased.

    double f(double ,double, double);           //returns f(x) given x1, x2, and x3
    double df_dx1(double, double, double);      //returns the partial derivative of f with respect to x1
    double df_dx2(double, double, double);      //returns the partial derivative of f with respect to x1
    double df_dx3(double, double, double);      //returns the partial derivative of f with respect to x3
    string stringF();                           //returns a string of the function
    void gradientMax();                         //locates the maxima of the function
    bool allowError();                          //checks to see if the error in the minimum is within acceptable bounds
    void resetSearch();
};


/*
 * Returns the potential energy of the system given the position of carts 1 and 2
 */
double GradientSearch::f(double x1, double x2, double x3) {
    return (x1 + sqrt(abs(x2)) - x3) * exp(-sqrt(2 + pow(x1,2) + pow(x2,2) + pow(x3,2)));
}


/*
 * returns the value of the partial derivative of f(x) with respect to x1
 */
double GradientSearch::df_dx1(double x1, double x2, double x3) {
    return exp(-sqrt(2 + pow(x1,2) + pow(x2,2) + pow(x3,2))) -
            ((x1 * exp(-sqrt(2 + pow(x1,2) + pow(x2,2) + pow(x3,2))) * (sqrt(abs(x2)) + x1 - x3))/
                    (sqrt(pow(x1,2) + pow(x2,2) + pow(x3,2) + 2)));
}


/*
 * returns the value of the partial derivative of f(x) with respect to x2
 */
double GradientSearch::df_dx2(double x1, double x2, double x3) {
    return ((x2 * exp(-sqrt(2 + pow(x1,2) + pow(x2,2) + pow(x3,2))))/(2 * pow(abs(x2),(3/2)))) -
            ((x2 * exp(-sqrt(2 + pow(x1,2) + pow(x2,2) + pow(x3,2))) * (sqrt(abs(x2)) + x1 - x3))/
                    (sqrt(pow(x1,2) + pow(x2,2) + pow(x3,2) + 2)));
}

/*
 * returns the value of the partial derivative of f(x) with respect to x3
 */
double GradientSearch::df_dx3(double x1, double x2, double x3) {
    return -((x3 * exp(-sqrt(2 + pow(x1,2) + pow(x2,2) + pow(x3,2))) * (sqrt(abs(x2)) + x1 - x3))/
            (sqrt(pow(x1,2) + pow(x2,2) + pow(x3,2) + 2))) - exp(-sqrt(2 + pow(x1,2) + pow(x2,2) + pow(x3,2)));
}


/*
 * returns a string of the function
 */
string GradientSearch::stringF(){
    stringstream ss;
    ss << "(x1 + sqrt(abs(x2)) - x3) * exp(-sqrt(2 + x1^2 + x2^2 + x3^2))";
    return ss.str();
}


/*
 * Uses the gradient method to search for the maxima
 */
void GradientSearch::gradientMax() {
    double F, partX1, partX2, partX3, x1Curr, x2Curr, x3Curr, h1, h2, h3;

    x1Curr = maxX1;
    x2Curr = maxX2;
    x3Curr = maxX3;

    while (!allowError()) {
        partX1 = df_dx1(x1Curr, x2Curr, x3Curr);
        partX2 = df_dx2(x1Curr, x2Curr, x3Curr);
        partX3 = df_dx3(x1Curr, x2Curr, x3Curr);

        for (double i = -srchBnd; i < srchBnd; i += incr) {
            for (double j = -srchBnd; j < srchBnd; j += incr) {
                for (double k = -srchBnd; k < srchBnd; k+= incr) {
                    h1 = x1Curr + partX1 * i;
                    h2 = x2Curr + partX2 * j;
                    h3 = x3Curr + partX3 * k;
                    F = f(h1, h2, h3);
                    if (F > maxF) {
                        maxF = F;
                        maxX1 = h1;
                        maxX2 = h2;
                        maxX3 = h3;
                    }
                }
            }
        }

        x1Curr = maxX1;
        x2Curr = maxX2;
        x3Curr = maxX3;
    }

}


/*
 * Returns true if the slope of the function is withing the acceptable error
 * Returns false otherwise
 */
bool GradientSearch::allowError() {
    double x1_slope = abs(df_dx1(maxX1, maxX2, maxX3));
    double x2_slope = abs(df_dx2(maxX1, maxX2, maxX3));
    double x3_slope = abs(df_dx3(maxX1, maxX2, maxX3));

    if (x1_slope <= smallSlope && x3_slope <= smallSlope && incr > .005) {
        if (srchBnd > 1) {srchBnd -= 4;}
        else {srchBnd /= 10;}
        incr /= 10;
    }

    return x1_slope <= accError && x3_slope <= accError;
}


/*
 * Calls the optimizeMax function and returns the results to the user
 */
string GradientSearch::gradientSearch() {
    stringstream ss;
    ss << "FINDING THE MAXIMUM OF THE SYSTEM USING GRADIENT SEARCH METHOD\n";
    ss << "*****************************************************************************************\n";
    ss << "Function: " << stringF() << endl << endl;
    ss << "Starting from x1 = " << maxX1 << " and x2 = " << maxX2 << " and x3 = " << maxX3 << endl;
    gradientMax();
    ss << "=========================================================================================\n";
    ss << "The function is at a maximum when x1 = " << maxX1 << " and x2 = " << maxX2 << " and x3 = " << maxX3 << endl;
    ss << "f(" << maxX1 << "," << maxX2 << "," << maxX3 << ") = " << maxF << endl;
    ss << "=========================================================================================\n\n";
    resetSearch();
    ss << "Starting from x1 = " << maxX1 << " and x2 = " << maxX2 << " and x3 = " << maxX3 << endl;
    gradientMax();
    ss << "=========================================================================================\n";
    ss << "The function is at a maximum when x1 = " << maxX1 << " and x2 = " << maxX2 << " and x3 = " << maxX3 << endl;
    ss << "f(" << maxX1 << "," << maxX2 << "," << maxX3 << ") = " << maxF << endl;
    ss << "=========================================================================================\n";
    return ss.str();
}

/*
 * Resets the values used in the gradient search to the original values
 */
void GradientSearch::resetSearch() {
    maxX1 = -1;
    maxX2 = -1;
    maxX3 = -1;
    maxF = -999999;
    srchBnd = 5;
    incr = .5;
}

#endif //EXAM1_2_GRADIENTSEARCH_H
