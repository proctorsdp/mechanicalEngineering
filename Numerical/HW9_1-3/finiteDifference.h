//
// Created by Steven Proctor on 4/19/17.
//

#ifndef HW9_1_3_FINITEDIFFERENCE_H
#define HW9_1_3_FINITEDIFFERENCE_H

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

class finiteDifference {
public:
    void solve();                   //public function to solve ODE

private:
    double T_0 = 5;           //temperature at location x = 0;
    double T_L = 8;           //temperature at location x = L
    double L = 20;              //length of bar
    double h = .15;               //coefficient for convection
    double Ta = 0;              //ambient temperature
    double step = .5;            //delta x, or the amount to step by
    int iterations = int(((L-0) / step)-1);  //number of iterations required to solve
    vector<vector<double>> A;   //contains the matrix A
    vector<double> T, b;        //Contains the matrix b and T (temperature)
    string fileName = "finiteDifference.csv";   //file in which to store solution data

    void emptyArrays();         //empties the matricies
    void solveMatrix();         //gauss elimination
    void outputT();             //save to file
    double actual(double);      //actual T(x)
};



/*
 * actual T(x)
 */
double finiteDifference::actual(double x) {
    return (-0.00002 * exp(0.55196*x) + 5.75002 * exp(-0.30196*x) + (x/2.0) - 0.75);
}



/*
 * fill the matricies with zeros
 */
void finiteDifference::emptyArrays() {
    T.clear();
    b.clear();
    A.clear();

    for (int i = 0; i < iterations; i++) {
        vector<double> temp;
        T.push_back(0);
        b.push_back(0);
        for (int j = 0; j < iterations; j++) {
            temp.push_back(0);
        }
        A.push_back(temp);
    }
}

/*
 * creates the finite difference matrix for a bar
 */
void finiteDifference::solve() {
    emptyArrays();

    int j = 0;
    for (int i = 0; i < iterations; i++) {
        if (i > 0) {
            A[i][j - 1] = -((12/pow(step,2.0)) + (3/(2*step)));
        }
        A[i][j] = (24 / pow(step,2.0)) + 2;
        if (i < iterations - 1) {
            A[i][j + 1] = ((3/(2*step)) - (12/pow(step,2.0)));
        }
        b[i] = (step * i) + step;
        j++;
    }

    b[0] += ((12/pow(step,2.0)) + (3/(2*step))) * T_0;
    b[iterations-1] += -((3/(2*step)) - (12 / pow(step,2.0))) * T_L;

    solveMatrix();

    outputT();
}

/*
 * naive gauss elimination
 */
void finiteDifference::solveMatrix() {
    for (int i = 0; i < iterations; i++) {
        for (int j = i + 1; j < iterations; j++) {
            double factor = A[j][i] / A[i][i];
            for (int k = i; k < iterations; k++) {
                A[j][k] = A[j][k] - factor * A[i][k];
            }
            b[j] = b[j] - factor * b[i];
        }
    }

    T[iterations-1] = b[iterations-1] / A[iterations-1][iterations-1];
    for (int i = iterations-1; i >= 0; i--) {
        double sum = b[i];
        for (int j = i + 1; j < iterations; j++) {
            sum = sum - A[i][j] * T[j];
        }
        T[i] = sum / A[i][i];
    }
}

/*
 * output temperature data to .csv file
 */
void finiteDifference::outputT() {
    fstream fout;

    cout << "Exporting to " << fileName << "....\n";
    cout << "Please wait....\n";

    fout.open(fileName);

    fout << "Distance,Finite Diff.,True T(x),% Error\n";
    fout << 0 << "," << T_0 << "," << actual(0) << endl;
    for (int i = 0; i < iterations; i++) {
        double err = abs((actual(step * i + step) - T[i]) / actual(step * i + step)) * 100;
        fout << step * i + step << "," << T[i] << "," << actual(step * i + step) << "," << err << endl;
    }
    fout << L << "," << T_L << "," << actual(L) << endl;

    fout.close();

    cout << "\nData exported to " << fileName << "\n";
}


#endif //HW9_1_3_FINITEDIFFERENCE_H
