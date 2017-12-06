//
// Created by Steven Proctor on 4/18/17.
//

#ifndef HW9_1_3_SHOOTINGMETHOD_H
#define HW9_1_3_SHOOTINGMETHOD_H

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#include <fstream>

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

class shootingMethod {
public:
    void shoot();           //calls the shooting method solver

private:
    double T_0 = 5;       //temperature at location x = 0
    double T_L = 8;       //temperature at location x = L
    double Ta = 0;          //Ambient Temperature
    double h = .15;         //convection coefficient
    double L = 20;          //length of bar
    double z_0;             //initial "velocity"
    double step = .5;        //step size
    int iterations = int((L-0) / step);   //number of iterations
    vector<data> u;         //stores position and velcity data
    vector<double> x;       //stores time data
    string fileName = "shooting.csv";   //file to save solution to

    data f(double, data);   //system of differential equations
    void RKsolver();        //4th order Runge Kutta method
    void emptyVectors();    //clears content of vectors
    void exportY();         //saves solution to file
    double actual(double);  //
};


/*
 * actual T(x)
 */
double shootingMethod::actual(double x) {
    return (-0.00002 * exp(0.55196*x) + 5.75002 * exp(-0.30196*x) + (x/2.0) - 0.75);
}



/*
 * system of differential equations
 */
data shootingMethod::f(double x, data pos) {
    data newU;
    newU.a[0] = pos.a[1];
    newU.a[1] = (3 * pos.a[1] + 2 * pos.a[0] - x) / 12;
    return newU;
}


/*
 * 4th order Runge Kutta method
 */
void shootingMethod::RKsolver() {
    data k1, k2, k3, k4, u_mid;

    x.push_back(0);
    data firstU(T_0, z_0);
    u.push_back(firstU);

    for (int i = 0; i < iterations; i++) {
        double t_mid = x[i] + (step/2.0);
        k1 = f(x[i], u[i]).times(step);
        u_mid = u[i].add(k1.divide(2.0));
        k2 = f(t_mid, u_mid).times(step);
        u_mid = u[i].add(k2.divide(2.0));
        k3 = f(t_mid, u_mid).times(step);
        data newData(u[i].add(k3));
        u.push_back(newData);
        x.push_back(x[i] + step);
        k4 = f(x[i+1], u[i+1]).times(step);
        u[i+1] = u[i].add(((k1.add((k2.times(2.0)).add((k3.times(2.0)).add(k4)))).divide(6.0)));
    }
}


/*
 * empties the vectors
 */
void shootingMethod::emptyVectors() {
    x.clear();
    u.clear();
}


/*
 * shooting method to solve ODE
 */
void shootingMethod::shoot() {
    data low, high;
    double z_low, z_high;

    z_0 = 10;
    RKsolver();

    while (u.back().a[0] > T_L) {
        emptyVectors();
        z_0 -= 10;
        RKsolver();
    }

    low.a[0] = u.back().a[0];
    low.a[1] = u.back().a[1];
    z_low = z_0;

    emptyVectors();
    z_0 += 10;
    RKsolver();

    while (u.back().a[0] < T_L) {
        emptyVectors();
        z_0 += 10;
        RKsolver();
    }

    high.a[0] = u.back().a[0];
    high.a[1] = u.back().a[1];
    z_high = z_0;

    z_0 = z_low + ((z_high - z_low) / (high.a[0] - low.a[0])) * (T_L - low.a[0]);

    emptyVectors();
    RKsolver();
    exportY();
}


/*
 * outputs solution of y(t) to .csv file to be plotted in excel
 */
void shootingMethod::exportY() {
    fstream fout;

    cout << "Exporting to " << fileName << "....\n";
    cout << "Please wait....\n";

    fout.open(fileName);

    fout << "Distance,RK_4th T(x),True T(x),% Error\n";
    for (int i = 0; i <= iterations; i++) {
        double err = abs((actual(x[i]) - u[i].a[0]) / actual(x[i])) * 100;
        fout << x[i] << "," << u[i].a[0] << "," << actual(x[i]) << "," << err << endl;
    }

    fout.close();

    cout << "\nData exported to " << fileName << "\n";
}

#endif //HW9_1_3_SHOOTINGMETHOD_H
