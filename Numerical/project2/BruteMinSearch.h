//
// Created by Steven Proctor on 2/25/17.
//

#ifndef PROJECT2_BRUTEMINSEARCH_H
#define PROJECT2_BRUTEMINSEARCH_H

#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;

class BruteMinSearch {
public:
    string bruteSearch();   //find the optimized minimum and returns information to user

private:
    double k_a = 20;        //stiffness of spring a
    double k_b = 15;        //stiffness of spring b
    double F = 100;         //force pulling on the system
    double incr = .001;     //step size for incrementing the brute search
    double strtPt = 0;      //the value at which the brute search begins
    double stopPt = 10;     //the limit to which the brute search reaches
    double minPot = 999999; //stores the lowest potential energy
    double minX1, minX2;    //stores the x1 and x2 values corresponding to the minimum potential energy

    double potEnergy(double, double);   //returns the potential energy of the system
    void optimizeMin();                 //find the minimum potential energy of the system
    string stringPE();                  //returns string of the potential energy function
};

/*
 * Returns the potential energy of the system given the position of carts 1 and 2
 */
double BruteMinSearch::potEnergy(double x1, double x2) {
    return 0.5 * k_a * pow(x1,2) + 0.5 * k_b * pow(x2,2) - F * (x1 + x2);
}


/*
 * returns a string of the potential energy function
 */
string BruteMinSearch::stringPE(){
    stringstream ss;
    ss << "0.5 * k_a * x1^2 + 0.5 * k_b * x2^2 - F * (x1 + x2)";
    return ss.str();
}



/*
 * Uses a brute force method to find the minimum potential energy for the system
 */
void BruteMinSearch::optimizeMin() {
    double PE;
    for (double i = strtPt; i < stopPt; i += incr) {
        for (double j = strtPt; j < stopPt; j += incr) {
            PE = potEnergy(i,j);
            if (PE < minPot) {
                minPot = PE;
                minX1 = i;
                minX2 = j;
            }
        }
    }
}


/*
 * Calls the optimizeMin function and returns the results to the user
 */
string BruteMinSearch::bruteSearch() {
    stringstream ss;
    optimizeMin();
    ss << "FINDING THE MINIMUM POTENTIAL ENERGY OF THE SYSTEM USING BRUTE FORCE SEARCH\n";
    ss << "*****************************************************************************\n\n";
    ss << "Potential Energy Function: " << stringPE() << endl;
    ss << "Incrementing from " << strtPt << " - " << stopPt << " by steps of " << incr << endl << endl;
    ss << "=============================================================================\n";
    ss << "The potential energy of the system is at a minimum when x1 = " << minX1 << " and x2 = " << minX2 << endl;
    ss << "PE(" << minX1 << "," << minX2 << ") = " << minPot << endl;
    ss << "=============================================================================\n";
    return ss.str();
}

#endif //PROJECT2_BRUTEMINSEARCH_H
