/*
 * MAE 3210, HW 2, Problem 5.13
 * Created by Steven Proctor on 1/23/17.
 *

5.13 The velocity y of a falling parachutist is given by v = g*m/c * (1 - e^(-(c/m)t))
where g = 9.81 m/s2. For a parachutist with a drag coefficient c = 15 kg/s,
compute the mass m so that the velocity is v = 36 m/s at t = 10 s.
Use the false-position method to determine m to a level of es = 0.1%.

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
    return (9.81 * x / 15) * (1 - exp(-15 * 10 / x)) - 36;
}


/*
 * Returns the string of the function
 */
string fString() {
    stringstream ss;
    ss << "f(m) = 9.81 * m / 15 * (1 - e^(-15 * 10 / m)) - 36";
    return ss.str();
}


/*
 * Obtains the left and right bounds for bracketing methods
 * Ensures that the left and right bounds are on opposite sides of the root
 * Will continue to ask for bounds until each the root is appropriately bounded
 */
void getBounds(double & r, double & l) {
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
bool checkError(double crit, vector<double> root, int i) {
    double error = ((root[i] - root[i - 1]) / root[i]) * 100;
    return abs(error) < crit && abs(f(root[i])) < .1;
}


/*
 * Returns the location at which a linear interpolation cross the x-axis
 * Takes the left and right x-values of the interpolation
 */
double cross(double l, double r) {
    return r - ((f(r) * (l - r)) / (f(l) - f(r)));
}


/*
 * Obtains the root of the equation using the bi-sectional method
 * Performs a linear interpolation between bounds and uses the intersection with the x-axis as a new bound
 * Repeats interpolation until the intersection falls within acceptable error
 */
double falsePositionRoot() {
    double right, left;
    vector<double> root;
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

    while (!checkError(0.1, root, i)) {
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
 * Executes the false-position method and reports the results
 * Returns a string of the results
 */
string fpReport() {
    stringstream ss;
    double root = falsePositionRoot();
    ss << "The root of the equation: " << fString() << "\n"
            "is approximately located at x = " << root << ", "
               "where f(" << root << ") = " << f(root) << endl;
    ss << endl << "The parachutist needs a mass of about " << root
         << "kg in order to reach a velocity of 36m/s at time t = 10s\n";
    ss << endl << endl;
    return ss.str();
}



int main() {

    cout << endl << endl;

    cout << "5.13 The velocity y of a falling parachutist is given by v = g*m/c * (1 - e^(-(c/m)t))\n"
            "where g = 9.81 m/s2. For a parachutist with a drag coefficient c = 15 kg/s, \n"
            "compute the mass m so that the velocity is v = 36 m/s at t = 10 s. \n"
            "Use the false-position method to determine m to a level of es = 0.1%.\n";

    cout << endl << endl;

    cout << "FINDING THE ROOT OF A FUNCTION USING FALSE-POSITION METHOD\n"
            "**********************************************************\n"
            "(Acceptable error for solution: 0.1%)\n" << endl;
    cout << fpReport();


    return 0;
}