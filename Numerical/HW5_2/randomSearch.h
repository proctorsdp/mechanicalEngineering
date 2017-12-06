//
// Created by Steven Proctor on 2/13/17.
//

#ifndef HW5_2_RANDOMSEARCH_H
#define HW5_2_RANDOMSEARCH_H

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <time.h>

using namespace std;

class randomSearch {
public:
    string randomMax();

private:
    vector<double> xMax, yMax;
    int iter = 1000000;
    double left, right, top, bottom;

    double f(double, double);
    void findMax();
    void getBounds();
    string randomTitle();
};

double randomSearch::f(double x, double y) {
    return 4 * x + 2 * y + pow(x,2) - 2 * pow(x,4) + 2 * x * y - 3 * pow(y,2);
}

void randomSearch::getBounds() {
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

void randomSearch::findMax() {
    getBounds();
    int i = 1;
    double fMax, fCurr, x, y;
    srand(time(NULL));
    //double test = ((double(rand()%100)) / 100);

    x = (left + (right - left) * ((double(rand()%100)) / 100));
    y = (bottom + (top - bottom) * ((double(rand()%100)) / 100));
    fMax = f(x, y);

    do {
        x = (left + (right - left) * ((double(rand()%100)) / 100));
        y = (bottom + (top - bottom) * ((double(rand()%100)) / 100));
        fCurr = f(x, y);

        if (fCurr > fMax) {
            fMax = fCurr;
            xMax.push_back(x);
            yMax.push_back(y);
        }
        i++;

    } while(i < iter);
}

string randomSearch::randomMax() {
    stringstream ss;

    cout << randomTitle() << endl;
    findMax();

    ss << "=================================================================\n";
    ss << "The max value for the function occurs at x = " << xMax.back() << " & y = " << yMax.back() << endl;
    ss << "Where f(" << xMax.back() << "," << yMax.back() << ") = " << f(xMax.back(),yMax.back()) << endl;
    ss << "=================================================================\n";

    return ss.str();
}

string randomSearch::randomTitle() {
    stringstream ss;

    ss << endl;
    ss << "FINDING THE MAXIMUM VALUE OF A 2-D FUNCTION USING RANDOM SEARCH METHOD\n";
    ss << "**********************************************************************\n" << endl;

    ss << "Function: f(x,y) = 4 * x + 2 * y + x^2 - 2 * x^4 + 2 * x * y - 3 * y^2\n" << endl;

    return ss.str();
}




#endif //HW5_2_RANDOMSEARCH_H
