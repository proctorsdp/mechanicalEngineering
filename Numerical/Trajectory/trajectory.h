//
// Created by Steven Proctor on 1/30/17.
//

#ifndef TRAJECTORY_TRAJECTORY_H
#define TRAJECTORY_TRAJECTORY_H

#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class rootSolver {
public:
    string biSectionalReport();
    void graphicalReport();
    void setupEq();

private:
    vector<double> root;
    double criteria;
    double absError = .000005;
    const double pi = 3.1415926535897;
    double x, y, h, v;

    double biSectionalRoot();
    double f(double);
    string fString();
    void getBounds(double &, double &);
    bool checkError(int);
    void clearRoots();
    void getCriteria();
    void setDistance();
    void setInitialHeight();
    void setFinalHeight();
    void setVelocity();
    void showWebsite();
    bool graphicalRoot();
};


/*
 * Returns the value of the function at a given x-value
 */
double rootSolver::f(double w) {
    return ((tan(w) * x) - ((9.81 * pow(x,2)) / (2 * pow(v,2) * pow(cos(w), 2))) + h - y);
}


/*
 * Returns the string of the function
 */
string rootSolver::fString() {
    stringstream ss;
    ss << "y = tan(Theta) * x - (g * x^2)/(2 * v_0^2 * cos^2(Theta)) + y_0";
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

    while (fr * fl > 0 && ((r < 0 || r > (45*pi/180)) || (l < 0 || l > (45*pi/180)))) {
        cout << "Both x-values entered are on the same side of the root or out of bounds\n"
                "Please enter two values that are on opposite sides of the root and between 0 and pi/4\n"
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


void rootSolver::graphicalReport() {
    while(!graphicalRoot()) {};
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

    if (abs(y) < 2 && x < (45*pi/180) && x > 0) {
        cout << endl
             << "---------------------------------------------------------\n"
             << x << " is an appropriate estimate for a root of the function\n"
                "f(" << x << ") = " << y << endl
             << "---------------------------------------------------------\n";
        cout << endl << endl;
        return true;
    }

    else {
        cout << endl << x << " is not close enough to the actual root or is out of bounds (i.e. 0 < x < pi/4)\n"
                "f(" << x << ") = " << y << endl;
        cout << endl << endl;
        return false;
    }
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
 * Executes the bi-sectional method and reports the results
 * Returns a string of the results
 */
string rootSolver::biSectionalReport() {
    stringstream ss;
    cout << "Equation: " << fString() << endl << endl;
    double root = biSectionalRoot();
    ss << "The root of the equation: " << fString() << "\n"
            "is approximately located at Theta = " << root << ", "
               "where y(" << root << ") = " << f(root) << endl;
    ss << endl << endl;

    ss << "---------------------------------------------------------------------\n"
       << "The angle of departure angle for the given input is: " << root * 180 / pi << " degrees\n"
       << "---------------------------------------------------------------------\n" << endl;
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
 * Gets a distance value from the user
 */
void rootSolver::setDistance() {
    cout << "Enter the distance traveled by the object: [meters]\n";
    cin >> x;
    cout << endl << endl;
}


/*
 * Gets an initial height value from the user
 */
void rootSolver::setInitialHeight() {
    cout << "Enter the initial height of the object: [meters]\n";
    cin >> h;
    cout << endl << endl;
}


/*
 * Gets an final height value from the user
 */
void rootSolver::setFinalHeight() {
    cout << "Enter the final height of the object: [meters]\n";
    cin >> y;
    cout << endl << endl;
}


/*
 * Gets an initial velocity value from the user
 */
void rootSolver::setVelocity() {
    cout << "Enter the initial velocity of the object: [m/s]\n";
    cin >> v;
    cout << endl << endl;
}


void rootSolver::setupEq() {
    setDistance();
    setInitialHeight();
    setFinalHeight();
    setVelocity();
    showWebsite();
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

/*
 * Give the URL for Wolfram Alpha which will display the graph of the equation
 */
void rootSolver::showWebsite() {
    cout << "See the following website for a graph of the function:\n"
            "https://www.wolframalpha.com/input/?i=plot+%5B0+%3D+tan(x)+*+" << x << "+-+(9.81+*+" << x
         << "%5E2)%2F(2+*+" << v << "%5E2+*+cos%5E2(x))+%2B+" << h << "+-+" << y << ",+%7Bx,0,pi%2F4%7D%5D"
         << endl << endl << endl;
};

#endif //TRAJECTORY_TRAJECTORY_H
