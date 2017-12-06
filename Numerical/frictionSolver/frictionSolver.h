//
// Created by Steven Proctor on 1/27/17.
//

#ifndef FRICTIONSOLVER_FRICTIONSOLVER_H
#define FRICTIONSOLVER_FRICTIONSOLVER_H

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
    double Re;

    double biSectionalRoot();
    double f(double);
    string fString();
    void getBounds(double &, double &);
    bool checkError(int);
    void clearRoots();
    void getCriteria();
    void setReynolds();
    void showWebsite();

};


/*
 * Returns the value of the function at a given x-value
 */
double rootSolver::f(double x) {
    return ((1/sqrt(x)) - (4 * log10(Re * sqrt(x))) + 0.4);
}


/*
 * Returns the string of the function
 */
string rootSolver::fString() {
    stringstream ss;
    ss << "y(f) = 1/[f^(1/2)] - 4 * log(Re * f^(1/2)) + 0.4";
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

    setReynolds();
    showWebsite();
    //getBounds(right, left);
    right = 0.1;
    left = 0;
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
            "is approximately located at f = " << root << ", "
               "where y(" << root << ") = " << f(root) << endl;
    ss << endl << endl;

    ss << "------------------------------------------------------------------\n"
       << "The friction factor for a Reynolds number of " << Re << " is: " << root << endl
       << "------------------------------------------------------------------\n" << endl;
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
void rootSolver::setReynolds() {
    cout << "Enter the Reynolds value for the situation: (2,500 < Re < 1,000,000)\n";
    cin >> Re;
    cout << endl << endl;

    if (Re < 2500 || Re > 1000000) {
        cout << "The value " << Re << " is outside the appropriate range\n";
        setReynolds();
    }
}


/*
 * Obtains the desired criteria of accuracy from the user
 */
void rootSolver::getCriteria() {
    cout << "Enter the stopping criteria for the algorithm in terms of a percentage\n"
            "(i.e. 1% = 1) (Must be <= 10)\n";
    cin >> criteria;
    cout << endl << endl;

    criteria /= 100;

    if (criteria > .10) {
        cout << "A stopping criteria of " << criteria << "% is not accurate enough. "
        "Stopping criteria should be less than 10%\n";
        getCriteria();
    }
}

void rootSolver::showWebsite() {
    cout << "See this website for the plot of the equation:\n"
            "https://www.wolframalpha.com/input/?i=solve"
            "+0+%3D+1%2F%5Bf%5E(1%2F2)%5D+-+4+*+log(10,+"
         << Re << "+*+f%5E(1%2F2))+%2B+0.4\n"
         << endl << endl;
};

#endif //FRICTIONSOLVER_FRICTIONSOLVER_H
