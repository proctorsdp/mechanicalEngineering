//
// Created by Steven Proctor on 5/4/17.
//

#ifndef EXAM4_3_FINITEELEMENT_H
#define EXAM4_3_FINITEELEMENT_H

#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class finiteElement {
public:
    void solve();

private:
    double P = 2000;                        //distributed load (N/m)
    double Ar = .20;                        //Cross-section of bar (m^2)
    double E = 200 * pow(10.0,9.0);         //Modulus (Pa)
    double L = 12;                          //Length (m)
    double step = 2;                        //step size (m)
    double du_0 = 0;                        //boundary condition at x = 0
    double du_L = 0;                        //boundary condition at x = L
    double u_0 = 0;                         //boundary condition at x = 0
    double u_L = 0;                         //boundary condition at x = L
    int iterations = int(L/step) + 1;       //number of iterations required to solve
    vector<double> u, b;                    //contains vector u (deflection) and b (A*u)
    vector<vector<double>> A;               //contains matrix A
    string fileName = "finiteElement.csv";

    void buildMatrix();     //builds matrix A and vectors u and b
    void fillMatrix();      //fills the matrix and vectors
    void solveMatrix();     //solves for vector u
    void saveToFile();      //saves data to file
    double trueD(double);   //analytic solution
};


/*
 * return the analytic or true solution
 */
double finiteElement::trueD(double x) {
    return (P / (2 * Ar * E)) * pow(x,2.0) + (((u_L - u_0)/ L) - ((P * L) / (2 * Ar * E))) * x + u_0;
}


/*
 * builds matrix A and vector u and b, fills with zeros
 */
void finiteElement::buildMatrix() {
    for (int j = 0; j < iterations; j++) {
        vector<double> temp;
        for (int i = 0; i < iterations; i++) {
            temp.push_back(0);
        }
        A.push_back(temp);
        u.push_back(0);
        b.push_back(0);
    }
}


/*
 * fills the matrix according to the differential equation
 */
void finiteElement::fillMatrix() {
    for (int i = 0; i < iterations; i++) {
        for (int j = 0; j < iterations; j++) {
            if (i == j) {
                A[i][j] = -2 / step;
            }
            else if (i == j - 1 || i == j + 1) {
                A[i][j] = 1 / step;
            }
        }
    }

    A[0][0] = 1;
    A[1][0] = 0;
    A[iterations - 1][iterations - 1] = 1;
    A[iterations - 2][iterations - 1] = 0;

    for (int i = 1; i < iterations - 1; i++) {
        b[i] = 2 * (P * step) / (2 * E * Ar);
    }

    b[0] = -du_0 + ((P * step) / (2 * E * Ar));
    b[1] += u_0;
    b[iterations - 1] = du_L + ((P * step) / (2 * E * Ar));
    b[iterations - 2] += u_L;
}


/*
 * naive gauss elimination
 */
void finiteElement::solveMatrix() {
    for (int i = 0; i < iterations; i++) {
        for (int j = i + 1; j < iterations; j++) {
            double factor = A[j][i] / A[i][i];
            for (int k = i; k < iterations; k++) {
                A[j][k] = A[j][k] - factor * A[i][k];
            }
            b[j] = b[j] - factor * b[i];
        }
    }

    u[iterations-1] = b[iterations-1] / A[iterations-1][iterations-1];
    for (int i = iterations-1; i >= 0; i--) {
        double sum = b[i];
        for (int j = i + 1; j < iterations; j++) {
            sum = sum - A[i][j] * u[j];
        }
        u[i] = sum / A[i][i];
    }
}


/*
 * saves the solution to a .csv file to plot in excel
 */
void finiteElement::saveToFile() {
    fstream fout;
    fout.open(fileName);

    cout << "Saving data to: " << fileName << endl;

    u[0] = 0;
    u[iterations-1] = 0;
    fout << "Point (m), Est. Deflection (mm), True Deflection (mm), Error (%)\n";

    for (int i = 0; i < iterations; i++) {
        double tDef = trueD(i * step) * 1000;
        fout << i * step << "," << u[i] * 1000 << "," << tDef << "," << abs((tDef - u[i] * 1000) / tDef) * 100 << endl;
    }

    fout.close();

    cout << "Data successfully saved!\n";
}


/*
 * runs the finite element solver
 */
void finiteElement::solve() {

    cout << "SOLVING FOR DEFLECTION OF A BEAM USING FINITE ELEMENT\n";
    cout << "*****************************************************\n";

    buildMatrix();
    fillMatrix();
    solveMatrix();
    saveToFile();
}

#endif //EXAM4_3_FINITEELEMENT_H
