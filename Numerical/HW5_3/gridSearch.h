//
// Created by Steven Proctor on 2/13/17.
//

#ifndef HW5_3_GRIDSEARCH_H
#define HW5_3_GRIDSEARCH_H


#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

class gridSearch {
public:
    string gridMax();

private:
    double xMax, yMax, fMax = -999;
    double step = 0.001;
    double left, right, top, bottom;

    double f(double, double);
    void findMax();
    void getBounds();
    string gridTitle();
};

double gridSearch::f(double x, double y) {
    return y - x - 2 * pow(x,2) - 2 * x * y - pow(y,2);
}

void gridSearch::getBounds() {
    cout << "Please enter an x-value to the right of the maxima.\n";
    cin >> right;
    cout << endl;

    cout << "Please enter an x-value to the left of the maxima.\n";
    cin >> left;
    cout << endl;

    cout << "Please enter an y-value that is above the maxima.\n";
    cin >> top;
    cout << endl;

    cout << "Please enter an y-value that is below the maxima.\n";
    cin >> bottom;
    cout << endl;
}

void gridSearch::findMax() {
    getBounds();
    double curr;

    for (double x = left; x <= right; x += step) {
        for (double y = bottom; y <= top; y += step) {
            curr = f(x, y);
            if (curr > fMax) {
                fMax = curr;
                xMax = x;
                yMax = y;
            }
        }
    }
}

string gridSearch::gridMax() {
    stringstream ss;

    cout << gridTitle() << endl;
    findMax();

    ss << "=================================================================\n";
    ss << "The max value for the function occurs at x = " << xMax << " & y = " << yMax << endl;
    ss << "Where f(" << xMax << "," << yMax << ") = " << f(xMax,yMax) << endl;
    ss << "=================================================================\n";

    return ss.str();
}

string gridSearch::gridTitle() {
    stringstream ss;

    ss << endl;
    ss << "FINDING THE MAXIMUM VALUE OF A 2-D FUNCTION USING GRID SEARCH METHOD\n";
    ss << "********************************************************************\n" << endl;

    ss << "Function: f(x,y) = y - x - 2 * x^2 - 2 * x * y - y^2\n";
    ss << "Accuracy: 0.001" << endl;

    return ss.str();
}


#endif //HW5_3_GRIDSEARCH_H
