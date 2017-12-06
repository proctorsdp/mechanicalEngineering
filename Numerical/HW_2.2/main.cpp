/*
 * MAE 3210, HW 2, Problem 5.4
 * Created by Steven Proctor on 1/23/17.
 *

 5.4
 (a) Determine the roots of f(x) = -12 - 21x + 18x2 - 2.75x3 graphically.
 In addition, determine the first root of the function with (b) bisection, and (c) false position.
 For (b) and (c) use initial guesses of xl = -1 and xu = 0, and a stopping criterion of 1%.

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
    return -12 - 21 * x + 18 * pow(x,2) - 2.75 * pow(x,3);
}


/*
 * Returns the string of the function
 */
string fString() {
    stringstream ss;
    ss << "f(x) = -12 - 21x + 18x^2 - 2.75x^3";
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
 * Obtains the root of the equation using the bi-sectional method
 * Decreases the bounds by half, until the middle of the bounds falls within acceptable error
 */
double biSectionalRoot() {
    double right, left, middle;
    vector<double> root;
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

    while (!checkError(1, root, i)) {
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

    while (!checkError(1, root, i)) {
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
 * Executes the bi-sectional method and reports the results
 * Returns a string of the results
 */
string biReport() {
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
string fpReport() {
    stringstream ss;
    double root = falsePositionRoot();
    ss << "The root of the equation: " << fString() << "\n"
            "is approximately located at x = " << root << ", "
               "where f(" << root << ") = " << f(root) << endl;
    ss << endl << endl;
    return ss.str();
}



int main() {

    cout << endl << endl;

    cout << "5.4 \n"
            "(a) Determine the roots of f(x) = -12 - 21x + 18x2 - 2.75x3 graphically. \n"
            "In addition, determine the first root of the function with (b) bisection, and (c) false position. \n"
            "For (b) and (c) use initial guesses of xl = -1 and xu = 0, and a stopping criterion of 1%.\n";

    cout << endl << endl;

    cout << "FINDING THE ROOT OF A FUNCTION GRAPHICALLY\n"
            "******************************************\n"
            "(Acceptable range: ABS[f(x)] < 1)\n" << endl;
    while (!graphicalRoot()) {}

    cout << endl << endl;

    cout << "FINDING THE ROOT OF A FUNCTION USING BI-SECTIONAL METHOD\n"
            "********************************************************\n"
            "(Acceptable error for solution: 1%)\n" << endl;
    cout << biReport();

    cout << endl << endl;

    cout << "FINDING THE ROOT OF A FUNCTION USING FALSE-POSITION METHOD\n"
            "**********************************************************\n"
            "(Acceptable error for solution: 1%)\n" << endl;
    cout << fpReport();

    return 0;
}


