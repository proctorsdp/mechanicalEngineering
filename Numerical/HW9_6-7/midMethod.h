//
// Created by Steven Proctor on 4/20/17.
//

#ifndef HW9_6_7_MIDMETHOD_H
#define HW9_6_7_MIDMETHOD_H

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class midMethod {
public:
    void solve();

private:
    double T_0 = 100;                           //temperature at location x = 0;
    double T_L = 50;                            //temperature at location x = L
    double L = 10;                              //length of bar
    double Time = 12;                           //Duration of interest
    double k = 0.835;                           //conduction coefficient
    double Lstep = 2;                          //delta x, or the distance to step by (cm)
    double Tstep = .1;                          //delta t, of the time to step by (s)
    double lamda = (k*Tstep)/pow(Lstep,2.0);    //coefficient
    int iterations = int(((L-0) / Lstep)-1);    //number of internal nodes
    vector<vector<double>> A, T, b;             //contains the matrix A, T, and b
    string fileName = "midpointMethod.csv";     //file in which to store solution data

    void createMatrix();                        //creates matrix A, T, and b
    void fillB();                               //solves for matrix b
    void timeStep();                            //adds the next time step to T and b
    void solveMatrix();                         //solves for the temp at time t
    void reset();                               //clear the matrix
    void exportData();                          //saves data to file
};


/*
 * creates Matrix A and fills with zeros
 */
void midMethod::createMatrix() {
    A.clear();

    for (int i = 0; i < iterations; i++) {
        vector<double> temp;
        for (int j = 0; j < iterations; j++) {
            temp.push_back(0);
        }
        A.push_back(temp);
    }
}


/*
 * adds a new row to matrix T and b, fills with zeros
 */
void midMethod::timeStep() {
    vector<double> temp;
    for (int i = 0; i < iterations; i++) {
        temp.push_back(0);
    }

    T.push_back(temp);
    b.push_back(temp);
}


/*
 * fills the b vector with values
 */
void midMethod::fillB() {
    int k = 0;
    int i = (int)b.size() - 1;
    if (b.size() > 1) {
        k = (int) b.size() - 2;
    }

    for (int j = 0; j < iterations; j++) {
        if (j == 0) {
            b[i][j] = lamda * (2 * T_0 + T[k][j + 1]) + 2 * (1 - lamda) * T[k][j];
        }
        else if (j == iterations - 1) {
            b[i][j] = lamda * (T[k][j - 1] + 2 * T_L) + 2 * (1 - lamda) * T[k][j];
        }
        else {
            b[i][j] = lamda * (T[k][j - 1] + T[k][j + 1]) + 2 * (1 - lamda) * T[k][j];
        }
    }
}


/*
 * naive gauss elimination
 */
void midMethod::solveMatrix() {
    int l = (int)b.size() - 1;
    for (int i = 0; i < iterations; i++) {
        for (int j = i + 1; j < iterations; j++) {
            double factor = A[j][i] / A[i][i];
            for (int k = i; k < iterations; k++) {
                A[j][k] = A[j][k] - factor * A[i][k];
            }
            b[l][j] = b[l][j] - factor * b[l][i];
        }
    }

    T[l][iterations-1] = b[l][iterations-1] / A[iterations-1][iterations-1];
    for (int i = iterations-1; i >= 0; i--) {
        double sum = b[l][i];
        for (int j = i + 1; j < iterations; j++) {
            sum = sum - A[i][j] * T[l][j];
        }
        T[l][i] = sum / A[i][i];
    }
}

/*
 * empties the matrix
 */
void midMethod::reset() {
    A.clear();
    b.clear();
    T.clear();
}

/*
 * runs the solver
 */
void midMethod::solve() {
    reset();

    cout << "SOLVING TEMPERATURE OF A BAR USING MIDPOINT METHOD\n";
    cout << "**************************************************\n";

    for (double k = 0; k < Time; k += Tstep) {
        createMatrix();

        int i = 0;
        for (int j = 0; j < iterations; j++) {
            if (i > 0) {
                A[i][j - 1] = -lamda;
            }
            A[i][j] = 2 * (1 + lamda);
            if (i < iterations - 1) {
                A[i][j + 1] = -lamda;
            }
            i++;
        }

        timeStep();
        fillB();
        solveMatrix();
    }

    exportData();
}

/*
 * saves data to a file
 */
void midMethod::exportData() {
    fstream fout;
    fout.open(fileName);

    int incr = 10;

    cout << "Saving data to: " << fileName << endl;

    fout << "Distance,";
    for (int i = incr; i <= Time * incr; i += incr) {
        fout << "T(t = " << i * Tstep << "s),";
    }
    fout << endl;

    for (int i = 0; i < iterations + 2; i ++) {
        fout << i * Lstep << ",";

        for (int j = incr; j <= Time * incr; j += incr) {
            if (i == 0) {
                fout << T_0 << ",";
            }
            else if (i == iterations + 1) {
                fout << T_L << ",";
            }
            else {
                fout << T[j-1][i-1] << ",";
            }
        }
        fout << endl;
    }

    fout.close();

    cout << "Data successfully saved!\n";
}


#endif //HW9_6_7_MIDMETHOD_H
