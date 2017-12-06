/*
 * MAE 3210, HW 2, Problem 6.6
 * Created by Steven Proctor on 1/23/17.
 *

6.6 Determine the lowest real root of f(x) = -12 - 21x + 18x2 - 2.4x3:
(a) graphically and
(b) using the secant method to a value of es corresponding to three significant figures.

 */

#include <iostream>
#include <cmath>
#include <sstream>
#include <vector>

using namespace std;


/*
 * Returns the value of the function at a given x-value
 */
double f(double x) {
    return -12 - 21 * x + 18 * pow(x,2) - 2.4 * pow(x,3);
}


/*
 * Returns the value of the function's derivative at a given x-value
 */
double f_deriv(double x) {
    return -21 + 36 * x - 7.2 * pow (x,2);
}


/*
 * Returns the string of the function
 */
string fString() {
    stringstream ss;
    ss << "f(x) = -12 - 21x + 18x^2 - 2.4x^3";
    return ss.str();
}


/*
 * Returns true if the user's guess is an accurate estimate of the root of the function
 * Requires the user to view the graph of the function and make an educated guess about the location of the root
 * Will continue to ask for guesses until the guess falls within the desired range of accuracy
 */
bool graphicalRoot() {
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
 * Ensures that the error of the calculation is within acceptable bounds
 * Takes in the desired error, vector of all iterations of the root, and the current iteration
 */
bool checkError(double crit, vector<double> root, int i) {
    double error = ((root[i] - root[i - 1]) / root[i]) * 100;
    return abs(error) < crit && abs(f(root[i])) < .1;
}


/*
 * Obtains and returns an initial guess for the location of the function's root
 */
double newtonGuess() {
    double root;
    cout << "Enter an initial guess for the root of the function: " << fString() << endl;
    cin >> root;
    cout << endl << endl;
    return root;
}


/*
 * Returns the root of the function using the Secant Method
 * Uses an approximation of the derivative and substitutes it into Newton-Raphson
 * The intersection point with the x-axis is used as the new guess
 * Process is repeated until the root is within the desired error
 */
double secantRoot() {
    vector<double> root;
    int i = 1;
    double guess;

    guess = newtonGuess();
    root.push_back(guess - 1);
    root.push_back(guess);

    while (!checkError(.001, root, i)) {
        root.push_back(root[i] - ((f(root[i]) * (root[i - 1] - root[i])) / (f(root[i - 1]) - f(root[i]))));
        i++;
    }

    return root[i];
}


/*
 * Executes the secant method and reports the results
 * Returns a string of the results
 */
string sReport() {
    stringstream ss;
    double root = secantRoot();
    ss << "The root of the equation: " << fString() << "\n"
            "is approximately located at x = " << root << ", "
               "where f(" << root << ") = " << f(root) << endl;
    ss << endl << endl;
    return ss.str();
}




int main() {

    cout << endl << endl;

    cout << "6.6 Determine the lowest real root of f(x) = -12 - 21x + 18x2 - 2.4x3:\n"
            "(a) graphically and\n"
            "(b) using the secant method to a value of es corresponding to three significant figures.\n";

    cout << endl << endl;

    cout << "FINDING THE ROOT OF A FUNCTION GRAPHICALLY\n"
            "******************************************\n"
            "(Acceptable range: ABS[f(x)] < 1)\n" << endl;
    while (!graphicalRoot()) {}

    cout << endl << endl;

    cout << "FINDING THE ROOT OF A FUNCTION USING SECANT METHOD\n"
            "**************************************************\n"
            "(Acceptable error for solution: 0.001%)\n" << endl;
    cout << sReport();

    return 0;
}