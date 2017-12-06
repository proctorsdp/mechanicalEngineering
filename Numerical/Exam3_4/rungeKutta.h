//
// Created by Steven Proctor on 4/8/17.
//

#ifndef EXAM3_4_RUNGEKUTTA_H
#define EXAM3_4_RUNGEKUTTA_H

#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

const int D_SIZE = 2;

struct data {
    double a[D_SIZE];           //stores the solution for y(t) and dy(t)

    //default constructor
    data() {}

    //initialize y(t) and dy(t)
    data(double one, double two) {
        a[0] = one;
        a[1] = two;
    }

    //allows for multiplication of arrays
    data times(double num) {
        data newD(a[0]*num, a[1]*num);
        return newD;
    }

    //allow for division of arrays
    data divide(double num) {
        data newD(a[0]/num, a[1]/num);
        return newD;
    }

    //allows for addition of arrays
    data add(data num) {
        data newD(a[0]+num.a[0], a[1]+num.a[1]);
        return newD;
    }
};


class RungeKutta {
public:
    void solve();                               //initialize the runge kutta solution

private:
    string fileName = "RK_4th_Solution.csv";
    double y_initial = 0;                       //initial position value
    double dy_initial = 0;                      //initial velocity value
    double start = 0;                           //start time t
    double end = 10;                            //end time t
    double step = 2;                            //step size to achieve desired accuracy
    double iterations = (end-start) / step;     //number of iterations required
    vector<data> u;                             //contains the solution data for y and dy
    vector<double> t;                           //stores the timestamp for each data point
    data k1, k2, k3, k4, u_mid;                 //stores the k values (slopes) and midpoint between steps

    data f(double, data);                       //returns y and dy for a given time t
    double trueY(double);                       //returns the true y for a given time t
    void exportY();                             //saves solution data to .csv file
};


/*
 * returns an estimate y and dy for a given time t and the previous y and dy
 */
data RungeKutta::f(double time, data pos) {
    data newU;
    newU.a[0] = pos.a[1];
    newU.a[1] = -2*pos.a[1] - 10*pos.a[0] + 3*cos(time);
    return newU;
}


/*
 * returns the true value at y for a given time t
 */
double RungeKutta::trueY(double x) {
    return (exp(-x))*((-27.0/85.0)*cos(3.0*x) - (11.0/85.0)*sin(3.0*x)) + (27.0/85.0)*cos(x) + (6.0/85.0)*sin(x);
}


/*
 * initializes y and dy and t
 * steps through each variable solving for the solution at each time t
 * iterates process until end time
 * outputs results and error. Calls exportY()
 */
void RungeKutta::solve() {
    t.push_back(start);
    data firstU(y_initial, dy_initial);
    u.push_back(firstU);

    for (int i = start; i < iterations; i++) {
        double t_mid = t[i] + step/2;
        k1 = f(t[i], u[i]).times(step);
        u_mid = u[i].add(k1.divide(2));
        k2 = f(t_mid, u_mid).times(step);
        u_mid = u[i].add(k2.divide(2));
        k3 = f(t_mid, u_mid).times(step);
        data newData(u[i].add(k3));
        u.push_back(newData);
        t.push_back(t[i] + step);
        k4 = f(t[i+1], u[i+1]).times(step);
        u[i+1] = u[i].add(((k1.add((k2.times(2)).add((k3.times(2)).add(k4)))).divide(6)));
    }

    double trY = trueY(10);

    cout << endl << endl;
    cout << "Step size: " << step << endl;
    cout << "=======================\n";
    cout << "RK_4th(10) = " << u.back().a[0] << endl;
    cout << "TrueY(10) = " << trY << endl;
    cout << "=======================\n";
    cout << "Error: " << abs((u.back().a[0]-trY)/trY) * 100 << "%" << endl;
    cout << "=======================\n";
    cout << endl << endl;

    exportY();
}


/*
 * outputs solution of y(t) to .csv file to be plotted in excel
 */
void RungeKutta::exportY() {
    fstream fout;

    cout << "Exporting to " << fileName << "....\n";
    cout << "Please wait....\n";

    fout.open(fileName);

    fout << "Time,RK_4th y(t),True y(t):,(e^-t)*[(-27/85)*cos(3*t) - (11/85)*sin(3*t)] + (27/85)*cos(t) + (6/85)*sin(t)\n";
    for (int i = 0; i < iterations; i++) {
        fout << t[i] << "," << u[i].a[0] << "," << trueY(t[i]) << endl;
    }

    fout.close();

    cout << "\nData exported to " << fileName << "\n";
}

#endif //EXAM3_4_RUNGEKUTTA_H
