//
// Created by Steven Proctor on 2/25/17.
//

#ifndef PROJECT2_GRADIENTSEARCH_H
#define PROJECT2_GRADIENTSEARCH_H

#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;

class GradientSearch {
public:
    string gradientSearch();    //returns the results of a gradient search to find the minimum

private:
    double k_a = 20;            //stiffness of spring a
    double k_b = 15;            //stiffness of spring b
    double F = 100;             //force pulling on the system
    double accError = .0001;    //the acceptable error that tells the program to stop
    double minPot = 999999;     //stores the lowest potential energy
    double minX1 = 0;           //stores the x1 value corresponding to the minimum potential energy
    double minX2 = 0;           //stores the x2 value corresponding to the minimum potential energy

    double potEnergy(double ,double);   //returns the potential energy of the system given x1 and x2
    double dPE_dx1(double);             //returns the partial derivative of potential energy with respect to x1
    double dPE_dx2(double);             //returns the partial derivative of potential energy with respect to x1
    string stringPE();                  //returns a string of the function
    void gradientMin();                 //locates the minimum of the function
    bool allowError();                  //checks to see if the error in the minimum is within acceptable bounds
};


/*
 * Returns the potential energy of the system given the position of carts 1 and 2
 */
double GradientSearch::potEnergy(double x1, double x2) {
    return 0.5 * k_a * pow(x1,2) + 0.5 * k_b * pow(x2,2) - F * (x1 + x2);
}


/*
 * returns the value of the partial derivative of PE with respect to x1, given a value for x1
 */
double GradientSearch::dPE_dx1(double x1) {
    return k_a * x1 - F;
}


/*
 * returns the value of the partial derivative of PE with respect to x2, given a value for x2
 */
double GradientSearch::dPE_dx2(double x2) {
    return k_b * x2 - F;
}


/*
 * returns a string of the potential energy function
 */
string GradientSearch::stringPE(){
    stringstream ss;
    ss << "0.5 * k_a * x1^2 + 0.5 * k_b * x2^2 - F * (x1 + x2)";
    return ss.str();
}


/*
 * Uses the gradient method to search for the minimum
 */
void GradientSearch::gradientMin() {
    double PE, partX1, partX2, x1Curr, x2Curr, h1, h2;

    x1Curr = minX1;
    x2Curr = minX2;

    while (!allowError()) {
        partX1 = dPE_dx1(x1Curr);
        partX2 = dPE_dx2(x2Curr);

        for (double i = 0; i < 5; i += .001) {
            h1 = x1Curr - partX1 * i;
            h2 = x2Curr - partX2 * i;
            PE = potEnergy(h1,h2);
            if (PE < minPot) {
                minPot = PE;
                minX1 = h1;
                minX2 = h2;
            }
        }

        x1Curr = minX1;
        x2Curr = minX2;
    }

}


/*
 * Returns true if the slope of the function is withing the acceptable error
 * Returns false otherwise
 */
bool GradientSearch::allowError() {
    double x1_slope = abs(dPE_dx1(minX1));
    double x2_slope = abs(dPE_dx2(minX2));

    if (x1_slope <= accError && x2_slope <= accError) {
        return true;
    }
    else {
        return false;
    }
}


/*
 * Calls the optimizeMin function and returns the results to the user
 */
string GradientSearch::gradientSearch() {
    stringstream ss;
    ss << "FINDING THE MINIMUM POTENTIAL ENERGY OF THE SYSTEM USING GRADIENT SEARCH METHOD\n";
    ss << "*******************************************************************************\n\n";
    ss << "Potential Energy Function: " << stringPE() << endl;
    ss << "Starting from x1 = " << minX1 << " and x2 = " << minX2 << endl << endl;
    gradientMin();
    ss << "===============================================================================\n";
    ss << "The potential energy of the system is at a minimum when x1 = " << minX1 << " and x2 = " << minX2 << endl;
    ss << "PE(" << minX1 << "," << minX2 << ") = " << minPot << endl;
    ss << "===============================================================================\n";
    return ss.str();
}

#endif //PROJECT2_GRADIENTSEARCH_H
