//
// Created by Steven Proctor on 4/23/17.
//

#ifndef HW9_6_7_DERIVCOND_H
#define HW9_6_7_DERIVCOND_H


#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class derivCond {
public:
    void solve();

private:
    int dT_L = 0;                        //derivative at x = L
    int dT_0 = 1;                        //derivative at x = 0;
    double L = 10;                          //length of bar
    double T_bar = 50.0;                      //initial temperature of the bar
    double Time = 12.0;                       //duration of interest
    double k = 0.835;                       //conduction coefficient
    double Lstep = 2.0;                      //delta x, or the amount to step by
    double Tstep = .1;                      //the amount of time to step by (s)
    double lamda = (k*Tstep)/pow(Lstep,2.0);    //coefficient
    int iterations = int(((L-0) / Lstep)) + 1;  //number of internal nodes
    vector<vector<double>> A, T, b;             //contains the matrix A, T and b
    string fileName = "derivCond.csv";          //file in which to store solution data

    void createMatrix();                        //creates matrix A, T, and b
    void timeStep();                            //adds the next time step to T and b
    void reset();                               //clear the matrix
    void exportData();                          //saves data to file
    void findTemp();
};


/*
 * creates matrix A, fills with zeros
 */
void derivCond::createMatrix() {
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
 * adds a row to matrix T and b, fills with initial bar temp and zeros
 */
void derivCond::timeStep() {
    vector<double> temp1, temp2;
    for (int i = 0; i < iterations; i++) {
        temp1.push_back(0);
        temp2.push_back(T_bar);
    }

    T.push_back(temp2);
    b.push_back(temp1);
}


/*
 * empties the matrix
 */
void derivCond::reset() {
    A.clear();
    b.clear();
    T.clear();
}

/*
 * runs the solver
 */
void derivCond::solve() {
    reset();

    cout << "SOLVING TEMPERATURE OF A BAR USING MIDPOINT METHOD AND INITIAL DERIVATIVE CONDITIONS\n";
    cout << "************************************************************************************\n";

    for (double k = 0; k <= Time+1; k += Tstep) {
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
        findTemp();
    }

    exportData();
}


/*
 * saves data to a file
 */
void derivCond::exportData() {
    fstream fout;
    fout.open(fileName);

    int incr = 10;

    cout << "Saving data to: " << fileName << endl;

    fout << "Distance,";
    for (int i = incr; i <= Time * 10; i += incr) {
        fout << "T(t = " << i * Tstep << "s),";
    }
    fout << endl;

    for (int i = 0; i < iterations; i ++) {
        fout << i * Lstep << ",";

        for (int j = incr; j <= Time * 10; j += incr) {
            fout << T[j][i] << ",";
        }
        fout << endl;
    }

    fout.close();

    cout << "Data successfully saved!\n";
}


void derivCond::findTemp() {
    if (T.size() == 1) {
        return;
    }

    int k = (int)T.size() - 2;
    int i = (int)T.size() - 1;

    for (int j = 0; j < iterations; j++) {
        if (j == 0) {
            T[i][j] = lamda * ((2.0 * T[k][j + 1]) - (2.0 * T[k][j]) - (2.0 * Lstep * dT_0)) + T[k][j];
        }
        else if (j == iterations - 1) {
            T[i][j] = lamda * ((2.0 * T[k][j - 1]) - (2.0 * T[k][j]) + (2.0 * Lstep * dT_L)) + T[k][j];
        }
        else {
            T[i][j] = lamda * (T[k][j - 1] + T[k][j + 1] - (2.0 * T[k][j])) + T[k][j];
        }
    }
}


#endif //HW9_6_7_DERIVCOND_H
