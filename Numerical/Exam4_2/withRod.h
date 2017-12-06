//
// Created by Steven Proctor on 5/4/17.
//

#ifndef EXAM4_2_WITHROD_H
#define EXAM4_2_WITHROD_H

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class rodMethod {
public:
    void solve();

private:
    double T_U = 100;                                           //temperature of top side of plate
    double T_D = 10;                                            //temperature of bottom side of plate
    double T_L = 75;                                            //temperature of left side of plate
    double T_R = 50;                                            //temperature of right side of plate
    double dT_U = 0;                                            //derivative of top side of plate
    double dT_D = 0;                                            //derivative of bottom side of plate
    double dT_R = 0;                                            //derivative of right side of plate
    double dT_L = 0;                                            //derivative of left side of plate
    bool insulateU = false;                                     //true if side is insulated
    bool insulateD = true;                                      //true if side is insulated
    bool insulateL = false;                                     //true if side is insulated
    bool insulateR = false;                                     //true if side is insulated
    int rad = 1;                                                //radius of rod divided by step
    double rodTemp = 400;                                       //temperature of rod
    double T_init = 10;                                         //initial temp of plate
    double W = 100;                                             //length of bar
    double Time = 600;                                          //Duration of interest
    double k = 0.835;                                           //conduction coefficient
    double Lstep = 10;                                          //delta x, or the distance to step by (cm)
    double Tstep = .1;                                          //delta t, of the time to step by (s)
    double lamda = (k*Tstep)/pow(Lstep,2.0);                    //coefficient
    int iterations = (int)pow(int(((W-0) / Lstep) + 1),2.0);    //number of internal nodes
    vector<vector<double>> A, T, b;                             //contains the matrix A, T, and b
    string fileName = "rodMethod.csv";                          //file in which to store solution data

    void createMatrix();                        //creates matrix A, T, and b
    void fillB();                               //solves for matrix b
    void timeStep();                            //adds the next time step to T and b
    void solveMatrix();                         //solves for the temp at time t
    void reset();                               //clear the matrix
    void exportData();                          //saves data to file
    double f_L(int);                            //boundary function for left side of plate
    double f_R(int);                            //boundary function for right side of plate
    double f_D(int);                            //boundary function for bottom of plate
    double f_U(int);                            //boundary function for top of plate
};


/*
 * return boundary function for bottom of plate
 */
double rodMethod::f_D(int t) {
    t *= Tstep;
    return dT_D * t;
}


/*
 * return boundary function for top of plate
 */
double rodMethod::f_U(int t) {
    t *= Tstep;
    return dT_U * t;
}


/*
 * return boundary function for right side of plate
 */
double rodMethod::f_R(int t) {
    t *= Tstep;
    return dT_R * t;
}


/*
 * return boundary function for left side of plate
 */
double rodMethod::f_L(int t) {
    t *= Tstep;
    return dT_L * t;
}


/*
 * creates Matrix A and fills with zeros
 */
void rodMethod::createMatrix() {
    A.clear();

    for (int i = 0; i < iterations; i++) {
        vector<double> temp1;
        for (int j = 0; j < iterations; j++) {
            temp1.push_back(0);
        }
        A.push_back(temp1);
    }

    int center = (iterations / 2) +1;

    int l = 1;
    for (int i = 0; i < iterations; i++) {
        for (int j = 0; j < iterations; j++) {
            if (i < sqrt(iterations) && !insulateU) {
                if (i == j) { A[i][j] = 1; }
            }
            else if (i >= iterations - sqrt(iterations) && i == j && !insulateD) {
                if (i == j) { A[i][j] = 1; }
            }
            else if (i == sqrt(iterations) * l && !insulateL) {
                if (i == j) { A[i][j] = 1; }
                if (j == iterations - 1) {l++;}
            }
            else if (i == (sqrt(iterations) * l) - 1 && !insulateR) {
                if (i == j) { A[i][j] = 1; }
            }
            else if (i >= center - rad && i <= center + rad) {
                if (i == j) { A[i][j] = 1; }
            }
            else if (i == center - sqrt(iterations) || i == center + sqrt(iterations)) {
                if (i == j) { A[i][j] = 1; }
            }
            else {
                if (i == j) {
                    A[i][j] = (1 + 4 * lamda);
                }
                else if (j == i - sqrt(iterations) || j == i + sqrt(iterations)) {
                    A[i][j] = -lamda;
                    if (i >= iterations - sqrt(iterations) && insulateD) {
                        A[i][j] *= 2;
                    }
                }
                else if (j == i - 1 || j == i + 1) {
                    A[i][j] = -lamda;
                }
            }
        }
    }
}


/*
 * adds a new row to matrix T and b, fills with zeros
 */
void rodMethod::timeStep() {
    vector<double> temp1, temp2;
    for (int i = 0; i < iterations; i++) {
        temp2.push_back(T_init);
        temp1.push_back(0);
    }

    T.push_back(temp2);
    b.push_back(temp1);

    int l = 1;
    for (int j = 0; j < iterations; j++) {
        if (j < sqrt(iterations)) {
            T.back()[j] = T_U;
        }
        else if (j == sqrt(iterations) * l) {
            T.back()[j] = T_L;
            l++;
        }
        else if (j == (sqrt(iterations) * l) - 1) {
            T.back()[j] = T_R;
        }
        else if (j >= iterations - sqrt(iterations)) {
            T.back()[j] = T_D;
        }
    }

    int center = (iterations / 2) +1;
    for (int i = -rad; i <= rad; i++) {
        T.back()[center + i] = rodTemp;
    }
    T.back()[center - sqrt(iterations)] = rodTemp;
    T.back()[center + sqrt(iterations)] = rodTemp;
}


/*
 * fills the b vector with values
 */
void rodMethod::fillB() {
    int k = 0;
    int i = (int)b.size() - 1;
    if (b.size() > 1) {
        k = (int) b.size() - 2;
    }

    int l = 1;
    for (int j = 0; j < iterations; j++) {
        if (j < sqrt(iterations)) {
            b[i][j] = T[k][j] + lamda * f_U(k);
        }
        else if (j == sqrt(iterations) * l) {
            b[i][j] = T[k][j] + lamda * f_L(k);
            l++;
        }
        else if (j == (sqrt(iterations) * l) - 1) {
            b[i][j] = T[k][j] + lamda * f_R(k);
        }
        else if (j >= iterations - sqrt(iterations)) {
            b[i][j] = T[k][j] + lamda * f_D(k);
        }
        else {
            b[i][j] = T[k][j];
        }
    }
}


/*
 * naive gauss elimination
 */
void rodMethod::solveMatrix() {
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
void rodMethod::reset() {
    A.clear();
    b.clear();
    T.clear();
}


/*
 * runs the solver
 */
void rodMethod::solve() {
    reset();

    cout << "SOLVING TEMPERATURE OF A PLATE USING MIDPOINT METHOD\n";
    cout << "****************************************************\n";
    cout << "Please Wait...\n";

    for (double k = 0; k < Time; k += Tstep) {
        createMatrix();
        timeStep();
        fillB();
        solveMatrix();
    }

    exportData();
}


/*
 * saves data to a file
 */
void rodMethod::exportData() {
    fstream fout;
    fout.open(fileName);

    int incr = 150;
    int x1 = 10, x2 = 70, x3 = 30, x4 = 80;
    int y1 = 10, y2 = 30, y3 = 70, y4 = 90;
    int temp;

    cout << "Saving data to: " << fileName << endl;

    fout << "Point (x:y),";
    for (int i = incr; i <= Time / Tstep; i += incr) {
        fout << i * Tstep << ",";
    }
    fout << endl;

    for (int i = 0; i < 4; i ++) {
        if (i == 0) {
            fout << "(" << x1 << ":" << y1 << ")" << ",";
            temp = int(iterations - (((y1/Lstep) * sqrt(iterations)) + sqrt(iterations)) + (x1/Lstep));
        }
        else if (i == 1) {
            fout << "(" << x2 << ":" << y2 << ")" << ",";
            temp = int(iterations - (((y2/Lstep) * sqrt(iterations)) + sqrt(iterations)) + (x2/Lstep));
        }
        else if (i == 2) {
            fout << "(" << x3 << ":" << y3 << ")" << ",";
            temp = int(iterations - (((y3/Lstep) * sqrt(iterations)) + sqrt(iterations)) + (x3/Lstep));
        }
        else if (i == 3) {
            fout << "(" << x4 << ":" << y4 << ")" << ",";
            temp = int(iterations - (((y4/Lstep) * sqrt(iterations)) + sqrt(iterations)) + (x4/Lstep));
        }


        for (int j = incr; j <= Time / Tstep; j += incr) {
            fout << T[j-1][temp] << ",";
        }
        fout << endl;
    }

    fout.close();

    cout << "Data successfully saved!\n";
}


#endif //EXAM4_2_WITHROD_H
