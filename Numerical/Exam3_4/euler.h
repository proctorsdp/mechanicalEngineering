//
// Created by Steven Proctor on 4/7/17.
//

#ifndef EXAM3_4_EULER_H
#define EXAM3_4_EULER_H

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>

using namespace std;

class Euler {
public:
    void solve();       //Initiates the Euler Solver

private:
    vector<double> y, y_ave, left_dy, right_dy, v, v_ave, left_dv, right_dv, t;     //contains the iterations of solution data
    double step = .00001;           //step size used to obtain accuracy
    double y_initial = 0;           //initial position at time t = 0;
    double dy_initial = 0;          //initial velocity at time t = 0;
    double start = 0;               //start solution at time t
    double stop = 10;               //end solution at time t
    string fileName = "eulerSolution.csv";

    double y_t(int);        //estimates y at a given time
    double dy_dx(int);      //estimates dy at a given time
    double dv_dx(int);      //returns d2y at a given time
    double ave_dv_dx(int);  //returns the average value of d2y over an interval
    string printY();        //prints solution data to the screen - NOT RECOMMENDED
    void exportY();         //saves solution data to file
    double trueY(double);   //returns y at a given time using the analytic solution
};


/*
 * returns an estimate of y(t) given a value t
 */
double Euler::y_t(int x) {
    return y[x] + step * left_dy[x+1];
}


/*
 * returns an estimate of dy(t) given a value t
 */
double Euler::dy_dx(int x) {
    return v[x] + step * left_dv[x+1];
}


/*
 * returns d2y(t) given a value t
 */
double Euler::dv_dx(int x) {
    return ((-2*v[x] - 10*y[x] + 3*cos(t[x])));
}


/*
 * returns the average of d2y(t) given a value t
 */
double Euler::ave_dv_dx(int x) {
    return ((-2*v_ave[x] - 10*y_ave[x] + 3*cos(t[x])));
}


/*
 * Initializes the values at time t = 0;
 * iterates through each variable solving for their value at time t
 * Repeats until end time, outputs final values and accuracy
 * Calls exportY()
 */
void Euler::solve() {
    y.push_back(y_initial);
    v.push_back(dy_initial);
    t.push_back(start);
    left_dy.push_back(-99);
    right_dy.push_back(-99);
    left_dv.push_back(-99);
    right_dv.push_back(-99);
    y_ave.push_back(-99);
    v_ave.push_back(-99);


    int j = 0;
    for (double i = start + step; i <= stop + step; i += step) {
        t.push_back(i);
        left_dy.push_back(v[j]);
        left_dv.push_back(dv_dx(j));
        y_ave.push_back(y_t(j));
        v_ave.push_back(dy_dx(j));
        right_dy.push_back(v_ave[j+1]);
        right_dv.push_back(ave_dv_dx(j+1));
        y.push_back(y[j] + (left_dy[j+1] + right_dy[j+1]) * step / 2);
        v.push_back(v[j] + (left_dv[j+1] + right_dv[j+1]) * step / 2);
        j++;
    }

    double trY = trueY(10);

    cout << endl << endl;
    cout << "Step size: " << step << endl;
    cout << "=======================\n";
    cout << "Euler(10) = " << y.back() << endl;
    cout << "TrueY(10) = " << trY << endl;
    cout << "=======================\n";
    cout << "Error: " << abs((y.back()-trY)/trY) * 100 << "%" << endl;
    cout << "=======================\n";
    cout << endl << endl;

    exportY();
}


/*
 * prints y(t) from start to finish
 * NOT RECOMMENDED, EATS UP MEMORY
 * USE EXPORTY()
 */
string Euler::printY() {
    stringstream ss;
    int width = 20;
    ss << "   Time:  " << setw(width) << "   y(t):  " << endl;
    ss << "----------" << setw(width) << "----------" << endl;
    for (int i = 0; i < y.size(); i++) {
        ss << t[i] << setw(width) << y[i] << endl;
    }
    return ss.str();
}


/*
 * returns the true value of y(t) at a given time
 */
double Euler::trueY(double x) {
    return (exp(-x))*((-27.0/85.0)*cos(3.0*x) - (11.0/85.0)*sin(3.0*x)) + (27.0/85.0)*cos(x) + (6.0/85.0)*sin(x);
}


/*
 * saves the solution y(t) to a .csv file to be accessed in excel
 */
void Euler::exportY() {
    fstream fout;

    cout << "Exporting to " << fileName << "....\n";
    cout << "Please wait....\n";

    fout.open(fileName);

    fout << "Time,Euler y(t),True y(t):,(e^-t)*[(-27/85)*cos(3*t) - (11/85)*sin(3*t)] + (27/85)*cos(t) + (6/85)*sin(t)\n";
    for (int i = 0; i < y.size(); i++) {
        fout << t[i] << "," << y[i] << "," << trueY(t[i]) << endl;
    }

    fout.close();

    cout << "\nData exported to " << fileName << "\n";
}

#endif //EXAM3_4_EULER_H
