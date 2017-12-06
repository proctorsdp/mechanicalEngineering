//
// Created by Steven Proctor on 1/30/17.
//

#ifndef TEMPERATUREPOLY_TEMPPOLY_H
#define TEMPERATUREPOLY_TEMPPOLY_H

#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class rootSolver {
public:
    string biSectionalReport();

private:
    vector<double> root;
    double criteria;
    double absError = .000005;
    double Cp;

    double biSectionalRoot();
    double f(double);
    string fString();
    void getBounds(double &, double &);
    bool checkError(int);
    void clearRoots();
    void getCriteria();
    void setCp();
    void showWebsite();

};


/*
 * Returns the value of the function at a given x-value
 */
double rootSolver::f(double x) {
    return (((1.9520 * pow(10,-14)) * pow(x,4)) - ((9.5838 * pow(10,-11)) * pow(x,3)) +
            ((9.7215 * pow(10,-8)) * pow(x,2)) + ((1.671 * pow(10,-4)) * x) + (0.99403 - Cp));
}


/*
 * Returns the string of the function
 */
string rootSolver::fString() {
    stringstream ss;
    ss << "0 = 1.952*10^-14 * T^4 - 9.5838*10^-11 * T^3 + "
            "9.7215*10^-8 * T^2 + 1.671*10^-4 * T + 0.99403 - Cp";
    return ss.str();
}


/*
 * Obtains the left and right bounds for bracketing methods
 * Ensures that the left and right bounds are on opposite sides of the root
 * Will continue to ask for bounds until each the root is appropriately bounded
 */
void rootSolver::getBounds(double & r, double & l) {
    double fr, fl;

    cout << "Enter an x-value that is to the right of the root\n";
    cin >> r;
    cout << "Enter an x-value that is to the left of the root\n";
    cin >> l;
    fr = f(r);
    fl = f(l);

    while (fr * fl > 0) {
        cout << "Both x-values entered are on the same side of the root\n"
                "Please enter two values that are on opposite sides of the root\n"
             << endl;
        cout << "Enter an x-value that is to the right of the root\n";
        cin >> r;
        cout << "Enter an x-value that is to the left of the root\n";
        cin >> l;
        fr = f(r);
        fl = f(l);
    } ;
    cout << endl << endl;
}


/*
 * Ensures that the error of the calculation is within acceptable bounds
 * Takes in the desired error, vector of all iterations of the root, and the current iteration
 */
bool rootSolver::checkError(int i) {
    double error = ((root[i] - root[i - 1]) / root[i]) * 100;
    return abs(error) < criteria && abs(f(root[i])) < absError;
}


/*
 * Obtains the root of the equation using the bi-sectional method
 * Decreases the bounds by half, until the middle of the bounds falls within acceptable error
 */
double rootSolver::biSectionalRoot() {
    double right, left, middle;
    clearRoots();
    getCriteria();
    int i = 0;

    setCp();
    showWebsite();
    getBounds(right, left);
    middle = (right + left) / 2;
    root.push_back(middle);

    if (f(left) * f(root[i]) < 0) {
        root.push_back((left + middle) / 2);
        right = middle;
    } else {
        root.push_back((right + middle) / 2);
        left = middle;
    }

    middle = (left + right) / 2;
    i++;

    while (!checkError(i)) {
        if (f(left) * f(root[i]) < 0) {
            root.push_back((left + middle) / 2);
            right = middle;
        } else {
            root.push_back((right + middle) / 2);
            left = middle;
        }

        middle = (left + right) / 2;
        i++;
    }

    return middle;
}

/*
 * Executes the bi-sectional method and reports the results
 * Returns a string of the results
 */
string rootSolver::biSectionalReport() {
    stringstream ss;
    cout << "Equation: " << fString() << endl << endl;
    double root = biSectionalRoot();
    ss << "The root of the equation: " << fString() << "\n"
            "is approximately located at Cp = " << root << ", "
               "where y(" << root << ") = " << f(root) << endl;
    ss << endl << endl;

    ss << "-------------------------------------------------------------------------------\n"
       << "The Temperature corresponding to a specific heat of " << Cp << "kJ/(kg*K) is: " << root << " K\n"
       << "-------------------------------------------------------------------------------\n" << endl;
    return ss.str();
}

/*
 * Clears the data inside the root vector
 */
void rootSolver::clearRoots() {
    root.clear();
    if (!root.empty()) {exit(9);}
}


/*
 * Gets a Reynolds value from the user
 */
void rootSolver::setCp() {
    cout << "Enter the specific heat for the situation: [kJ/(kg*K)]\n";
    cin >> Cp;
    cout << endl << endl;
}


/*
 * Obtains the desired criteria of accuracy from the user
 */
void rootSolver::getCriteria() {
    cout << "Enter the stopping criteria for the algorithm in terms of a percentage\n"
            "(i.e. 1% = 1) (Must be <= .1)\n";
    cin >> criteria;
    cout << endl << endl;

    criteria /= 100;

    if (criteria > .001) {
        cout << "A stopping criteria of " << criteria << "% is not accurate enough. "
        "Stopping criteria should be less than 10%\n";
        getCriteria();
    }
}

void rootSolver::showWebsite() {
    cout << "See this website for the plot of the equation:\n"
            "https://www.wolframalpha.com/input/?i=solve+0+%3D+(1.952*10%5E-14)"
            "+*+x%5E4+-+(9.5838*10%5E-11)+*+x%5E3+%2B+(9.7215*10%5E-8)+*+x%5E2+%2B+"
            "(1.671*10%5E-4)+*+x+%2B+0.99403+-+" << Cp << endl << endl << endl;
};

#endif //TEMPERATUREPOLY_TEMPPOLY_H
