//
// Created by Steven Proctor on 1/27/17.
//

#ifndef ROOTSOLVER_ROOTSOLVER_H
#define ROOTSOLVER_ROOTSOLVER_H

#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class rootSolver {
public:
    void guessRoot();
    string biSectionalReport();
    string falsePositionReport();
    string newtonRaphsonReport();
    string secantReport();

private:
    vector<double> root;
    double criteria;

    bool graphicalRoot();
    double falsePositionRoot();
    double biSectionalRoot();
    double newtonRaphsonRoot();
    double secantRoot();
    double f(double);
    double f_deriv(double);
    string fString();
    void getBounds(double &, double &);
    bool checkError(int);
    double cross(double, double);
    void clearRoots();
    void getCriteria();
    double singleGuess();
};


/*
 * Returns the value of the function at a given x-value
 */
double rootSolver::f(double x) {
    return (9.81 * x / 15) * (1 - exp(-15 * 10 / x)) - 36;
}


/*
 * Returns the value of the function's derivative at a given x-value
 */
double rootSolver::f_deriv(double x) {
    return -21 + 36 * x - 7.2 * pow (x,2);
}


/*
 * Returns the string of the function
 */
string rootSolver::fString() {
    stringstream ss;
    ss << "f(m) = 9.81 * m / 15 * (1 - e^(-15 * 10 / m)) - 36";
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
    return abs(error) < criteria && abs(f(root[i])) < .1;
}


/*
 * Returns the location at which a linear interpolation cross the x-axis
 * Takes the left and right x-values of the interpolation
 */
double rootSolver::cross(double l, double r) {
    return r - ((f(r) * (l - r)) / (f(l) - f(r)));
}


/*
 * Runs the function the graphicalRoot function until the root is found
 */
void rootSolver::guessRoot() {
    while (!graphicalRoot()) {};
}


/*
 * Returns true if the user's guess is an accurate estimate of the root of the function
 * Requires the user to view the graph of the function and make an educated guess about the location of the root
 * Will continue to ask for guesses until the guess falls within the desired range of accuracy
 */
bool rootSolver::graphicalRoot() {
    double x, y;

    cout << "Enter an approximate value for the root based on the graph of the function:\n";
    cout << fString() << endl;
    cin >> x;

    y = f(x);

    if (abs(y) < 1) {
        cout << endl << x << " is an appropriate estimate for a root of the function\n"
                "f(" << x << ") = " << y << endl;
        cout << endl << endl;
        return true;
    }

    else {
        cout << endl << x << " is not close enough to the actual root\n"
                "f(" << x << ") = " << y << endl;
        cout << endl << endl;
        return false;
    }
}


/*
 * Obtains the root of the equation using the bi-sectional method
 * Performs a linear interpolation between bounds and uses the intersection with the x-axis as a new bound
 * Repeats interpolation until the intersection falls within acceptable error
 */
double rootSolver::falsePositionRoot() {
    double right, left;
    clearRoots();
    getCriteria();
    int i = 0;

    getBounds(right, left);
    root.push_back(cross(left, right));

    if (f(left) * f(root[i]) < 0) {
        root.push_back(cross(left, root[i]));
        right = root[i];
    }
    else {
        root.push_back(cross(root[i], right));
        left = root[i];
    }

    i++;

    while (!checkError(i)) {
        if (f(left) * f(root[i]) < 0) {
            root.push_back(cross(left, root[i]));
            right = root[i];
        }
        else {
            root.push_back(cross(root[i], right));
            left = root[i];
        }

        i++;
    }

    return root[i];
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
 * Returns the root of the function using the Newton-Raphson Method
 * Uses the derivative of the function to find the slopes intersection with the x-axis
 * The obtained intersection point is used as the new guess
 * Process is repeated until the guessed root is within the desired error
 */
double rootSolver::newtonRaphsonRoot() {
    clearRoots();
    getCriteria();
    int i = 0;

    root.push_back(singleGuess());

    while (!checkError(i)) {
        root.push_back(root[i] - (f(root[i]) / f_deriv(root[i])));
        i++;
    }

    return root[i];
}


/*
 * Returns the root of the function using the Secant Method
 * Uses an approximation of the derivative and substitutes it into Newton-Raphson
 * The intersection point with the x-axis is used as the new guess
 * Process is repeated until the root is within the desired error
 */
double rootSolver::secantRoot() {
    vector<double> root;
    int i = 1;
    double guess;

    guess = singleGuess();
    root.push_back(guess - 1);
    root.push_back(guess);

    while (!checkError(i)) {
        root.push_back(root[i] - ((f(root[i]) * (root[i - 1] - root[i])) / (f(root[i - 1]) - f(root[i]))));
        i++;
    }

    return root[i];
}


/*
 * Obtains and returns an initial guess for the location of the function's root
 */
double rootSolver::singleGuess() {
    double root;
    cout << "Enter an initial guess for the root of the function: " << fString() << endl;
    cin >> root;
    cout << endl << endl;
    return root;
}


/*
 * Executes the bi-sectional method and reports the results
 * Returns a string of the results
 */
string rootSolver::biSectionalReport() {
    stringstream ss;
    double root = biSectionalRoot();
    ss << "The root of the equation: " << fString() << "\n"
            "is approximately located at x = " << root << ", "
               "where f(" << root << ") = " << f(root) << endl;
    ss << endl << endl;
    return ss.str();
}


/*
 * Executes the false-position method and reports the results
 * Returns a string of the results
 */
string rootSolver::falsePositionReport() {
    stringstream ss;
    double root = falsePositionRoot();
    ss << "The root of the equation: " << fString() << "\n"
            "is approximately located at x = " << root << ", "
               "where f(" << root << ") = " << f(root) << endl;
    ss << endl << endl;
    return ss.str();
}


/*
 * Executes the newton-raphson method and reports the results
 * Returns a string of the results
 */
string rootSolver::newtonRaphsonReport() {
    stringstream ss;
    double root = newtonRaphsonRoot();
    ss << "The root of the equation: " << fString() << "\n"
            "is approximately located at x = " << root << ", "
               "where f(" << root << ") = " << f(root) << endl;
    ss << endl << endl;
    return ss.str();
}


/*
 * Executes the secant method and reports the results
 * Returns a string of the results
 */
string rootSolver::secantReport() {
    stringstream ss;
    double root = secantRoot();
    ss << "The root of the equation: " << fString() << "\n"
            "is approximately located at x = " << root << ", "
               "where f(" << root << ") = " << f(root) << endl;
    ss << endl << endl;
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
 * Obtains the desired criteria of accuracy from the user
 */
void rootSolver::getCriteria() {
    cout << "Enter the stopping criteria for the algorithm in terms of a percentage\n"
            "(i.e. 1% = 1)\n";
    cin >> criteria;

    criteria /= 100;

    if (criteria > 10) {
        cout << "A stopping criteria of " << criteria << "% is not accurate enough\n"
                "Stopping criteria should be less than 10%\n";
        getCriteria();
    }
}

#endif //ROOTSOLVER_ROOTSOLVER_H
