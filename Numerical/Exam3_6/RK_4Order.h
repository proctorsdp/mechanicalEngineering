//
// Created by Steven Proctor on 4/9/17.
//

#ifndef EXAM3_6_RK_4ORDER_H
#define EXAM3_6_RK_4ORDER_H

#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

const int NUM_VAR = 3;
const int D_SIZE = 2;

struct data {
    //stores the pos and velocity data for each variable x, y and z
    double a[NUM_VAR][D_SIZE];

    //default constructor
    data() {}

    //initilize with position and velocity for x, y, and z
    data(double one, double two, double three, double four, double five, double six) {
        a[0][0] = one;
        a[0][1] = two;
        a[1][0] = three;
        a[1][1] = four;
        a[2][0] = five;
        a[2][1] = six;
    }

    //allows for multiplication of matrix
    data times(double num) {
        data newD(a[0][0]*num, a[0][1]*num, a[1][0]*num, a[1][1]*num, a[2][0]*num, a[2][1]*num);
        return newD;
    }

    //allows for division of matrix
    data divide(double num) {
        data newD(a[0][0]/num, a[0][1]/num, a[1][0]/num, a[1][1]/num, a[2][0]/num, a[2][1]/num);
        return newD;
    }

    //allows for addition of matrix
    data add(data num) {
        data newD(a[0][0]+num.a[0][0], a[0][1]+num.a[0][1], a[1][0]+num.a[1][0],
                  a[1][1]+num.a[1][1], a[2][0]+num.a[2][0], a[2][1]+num.a[2][1]);
        return newD;
    }
};


class RungeKutta {
public:
    void solve();

private:
    string fileName = "RK_4th_System_Solution.csv";     //filename where data is stored
    double y_initial = -10122.0;                        //initial y position value
    double dy_initial = 3.750;                          //initial y velocity value
    double x_initial = 0.0;                             //initial x position value
    double dx_initial = 5.879;                          //initial x velocity value
    double z_initial = -55192.0;                        //initial z position value
    double dz_initial = 2.044;                          //initial z velocity value
    double mew = 398600.0;                              //constant
    double start = 0;                                   //start time
    double end = 1200;                                  //end time
    double step = .5;                                   //step size for iterations
    double iterations = (end-start) / step;             //number of intervals
    vector<data> u;                                     //stores the x, y, and z solution data
    vector<double> t;                                   //stores the timestamp for each iteration
    data k1, k2, k3, k4, u_mid;                         //stores the slope and midpoint in each direction x, y, and z

    data f(double, data);                               //returns an estimate of the position in each direction
    double r(data);                                     //returns the denominator r for a given x, y, and z position
    void exportU();                                     //exports solution data to a .csv file
};


/*
 * returns the x, y, and z position for a given time and previous position
 */
data RungeKutta::f(double t, data pos) {
    double rad = pow(r(pos),3.0);
    data newU;
    newU.a[0][0] = pos.a[0][1];
    newU.a[1][0] = pos.a[1][1];
    newU.a[2][0] = pos.a[2][1];
    newU.a[0][1] = (-mew * pos.a[0][0])/rad;
    newU.a[1][1] = (-mew * pos.a[1][0])/rad;
    newU.a[2][1] = (-mew * pos.a[2][0])/rad;
    return newU;
}


/*
 * returns the denomonator r for a given position
 */
double RungeKutta::r(data p) {
    return sqrt(pow(p.a[0][0],2.0) + pow(p.a[1][0],2.0) + pow(p.a[2][0],2.0));
}


/*
 * solves the 2nd order, 3 dimensional ODE using 4th order Runge Kutta method
 * outputs the final position in the x, y, and z directions
 */
void RungeKutta::solve() {
    t.push_back(start);
    data firstU(x_initial, dx_initial, y_initial, dy_initial, z_initial, dz_initial);
    u.push_back(firstU);

    for (int i = start; i < iterations; i++) {
        double t_mid = t[i] + step/2.0;
        k1 = f(t[i], u[i]).times(step);
        u_mid = u[i].add(k1.divide(2.0));
        k2 = f(t_mid, u_mid).times(step);
        u_mid = u[i].add(k2.divide(2.0));
        k3 = f(t_mid, u_mid).times(step);
        data newU(u[i].add(k3));
        u.push_back(newU);
        t.push_back(t[i] + step);
        k4 = f(t[i+1], u[i+1]).times(step);
        u[i+1] = u[i].add((((k1.add((k2.times(2.0)).add((k3.times(2.0)).add(k4)))).divide(6.0))));
    }

    cout << endl << endl;
    cout << "Step size: " << step << endl;
    cout << setprecision(10);
    cout << "==============================\n";
    cout << "x(" << end << "s) = " << u.back().a[0][0] << " km\n";
    cout << "vx(" << end << "s) = " << u.back().a[0][1] << " km/s\n";
    cout << "y(" << end << "s) = " << u.back().a[1][0] << " km\n";
    cout << "vy(" << end << "s) = " << u.back().a[1][1] << " km/s\n";
    cout << "z(" << end << "s) = " << u.back().a[2][0] << " km\n";
    cout << "vz(" << end << "s) = " << u.back().a[2][1] << " km/s\n";
    cout << "==============================\n";
    cout << endl << endl;

    exportU();
}


/*
 * exports the position and acceleration data to a .csv for plotting
 */
void RungeKutta::exportU() {
    fstream fout;

    cout << "Exporting to " << fileName << "....\n";
    cout << "Please wait....\n";

    fout.open(fileName);

    fout << "Time,,x(t),vx(t),,y(t),vy(t),,z(t),vz(t)\n";
    for (int i = 0; i < iterations; i++) {
        fout << t[i]
             << ",," << u[i].a[0][0] << "," << u[i].a[0][1]
             << ",," << u[i].a[1][0] << "," << u[i].a[1][1]
             << ",," << u[i].a[2][0] << "," << u[i].a[2][1]
             << endl;
    }

    fout.close();

    cout << "\nData exported to " << fileName << "\n";
}


#endif //EXAM3_6_RK_4ORDER_H
