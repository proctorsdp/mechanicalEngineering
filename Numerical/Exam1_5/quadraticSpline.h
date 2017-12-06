//
// Created by Steven Proctor on 3/18/17.
//

#ifndef EXAM1_5_QUADRATICSPLINE_H
#define EXAM1_5_QUADRATICSPLINE_H

#include <cmath>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

const int intervals = 4;
const int spline = 3;

class quadraticSpline {
public:
    void build();
    string printMatrix();
    double fs(double);

private:
    double x[intervals+1] = {0, .5, 1, 1.5, 2};
    double f[intervals+1] = {2, 2.1639, 1.7595, 1.6950, 1.7408};
    double coeff[intervals * spline];
    double ans[intervals * spline];
    double m[intervals * spline][intervals * spline];

    void fillMatrix();
    void emptyMatrix();
    void solveMatrix();
    void pivot(int);
    void toFile();
};

void quadraticSpline::build() {
    emptyMatrix();
    fillMatrix();
    solveMatrix();
    cout << printMatrix() << endl;
    cout << "Quadratic Spline Function Built!\n\n\n" << endl;
    toFile();
}


double quadraticSpline::fs(double x) {
    if (x < 0 || x > 2) {
        cout << "x = " << x << " is outside the appropriate range.\n"
                "Please enter a value between 0 <= x <= 2.\n";
    }
    else if (x <= 0.5) {
        return coeff[0] * pow(x,2) + coeff[1] * x + coeff[2];
    }
    else if (x <= 1) {
        return coeff[3] * pow(x,2) + coeff[4] * x + coeff[5];
    }
    else if (x <= 1.5) {
        return coeff[6] * pow(x,2) + coeff[7] * x + coeff[8];
    }
    else if (x <= 2) {
        return coeff[9] * pow(x,2) + coeff[10] * x + coeff[11];
    }

    return 0;
}


string quadraticSpline::printMatrix() {
    stringstream ss;
    for (int i = 0; i < intervals * spline; i++) {
        ss << "[";
        for (int j = 0; j < intervals * spline; j++) {
            if (j > 0) {ss << setw(10);}
            ss << m[i][j];
        }
        ss << "]" << setw(10) << "[" << setw(8) << coeff[i] << "]" << setw(20) << "[" << setw(8) << ans[i] << "]" << endl;
    }
    return ss.str();
}


void quadraticSpline::emptyMatrix() {
    for (int i = 0; i < intervals * spline; i++) {
        for (int j = 0; j < intervals * spline; j++) {
            m[i][j] = 0;
        }
        ans[i] = 0;
        coeff[i] = 0;
    }
}


void quadraticSpline::fillMatrix() {

    int k = 0;
    int l = 1;
    bool skip = false;
    for (int i = 0; i < (intervals-1) * 2; i++) {
        for (int j = 0; j < 3; j++) {
            if (j == 0) {m[i][j+k*3] = pow(x[l],2);}
            else if (j == 1) {m[i][j+k*3] = x[l];}
            else {m[i][j+k*3] = 1;}
        }

        ans[i+1] = f[l];
        if ((i+2)%2 && i > 0) {l++; skip = true;}
        if (!skip) {k++;}
        skip = false;
    }

    k = 0;
    for (int i = 0; i <=1; i++) {
        for (int j = 0; j < 3; j++) {
            if (j == 2) {m[(intervals-1) * 2 + i][j+k*3] = 1;}
            else if (j ==1) {m[(intervals-1) * 2 + i][j+k*3] = x[i*intervals];}
            else {m[(intervals-1) * 2 + i][j+k*3] = pow(x[i*intervals],2);}
        }
        ans[(intervals-1)*2+i+1] = f[i*intervals];
        k = intervals - 1;
    }

    k = 0;
    for (int i = 1; i < intervals; i++) {
        for (int j = 0; j < 6; j++) {
            if (j == 2 || j == 5) {m[(intervals*2)-1+i][j+k*3] = 0;}
            else if (j == 1 || j == 4) {m[(intervals*2)-1+i][j+k*3] = x[i];}
            else {m[(intervals*2)-1+i][j+k*3] = x[i] * 2;}
        }
        ans[(intervals*2)+i] = 0;
        k++;
    }

    for (int i = intervals*spline-1; i > 0; i--) {
        for (int j = 0; j < intervals*spline; j++) {
            m[i][j] = m[i-1][j];
        }
    }

    for (int i = 0; i < intervals * spline; i++) {
        m[0][i] = 0;
        m[i][0] = 0;
    }
}


void quadraticSpline::solveMatrix() {
    for (int i = 1; i < spline * intervals; i++) {
        if (m[i][i] == 0) {
            pivot(i);
        }
        for (int j = i + 1; j < spline * intervals; j++) {
            double factor = m[j][i]/m[i][i];
            for (int k = i; k < spline * intervals; k++) {
                m[j][k] = m[j][k] - factor * m[i][k];
            }
            ans[j] = ans[j] - factor * ans[i];
        }
    }


    coeff[spline*intervals-1] = ans[spline*intervals-1] / m[spline*intervals-1][spline*intervals-1];
    for (int i = spline*intervals-1; i > 0; i--) {
        double sum = ans[i];
        for (int j = i + 1; j < spline*intervals; j++) {
            sum = sum - m[i][j] * coeff[j];
        }
        coeff[i] = sum / m[i][i];
    }
}




void quadraticSpline::pivot(int location) {
    double tempM[spline*intervals];
    double tempAns;
    double tempCoeff;
    double tempNum;

    for (int i = location + 1; i < spline * intervals; i++) {
        if (m[i][location] != 0) {
            for (int j = 0; j < spline * intervals; j++) {
                tempM[j] = m[i][j];
                m[i][j] = m[location][j];
                m[location][j] = tempM[j];
            }
            tempAns = ans[i];
            ans[i] = ans[location];
            ans[location] = tempAns;

            tempCoeff = coeff[i];
            coeff[i] = coeff[location];
            coeff[location] = tempCoeff;

            return;
        }
    }
}


void quadraticSpline::toFile() {
    fstream fout;
    fout.open("spline.csv");

    if (!fout.is_open()) {exit(8);}

    int j = 1;
    int k = 1;
    int l = 1;

    for (int i = 0; i < intervals*spline; i++) {
        if (i == 0 || i == 3 || i == 6 || i == 9) {
            fout << "a" << j << ",";
            j++;
        }
        else if (i == 1 || i == 4 || i == 7  || i == 10) {
            fout << "b" << k << ",";
            k++;
        }
        else {
            fout << "c" << l << ",";
            l++;
        }
        fout << coeff[i] << endl;
    }

    fout << endl << endl << endl;

    for (double i = 0; i <= 2.0; i+=.01) {
        fout << i << "," << fs(i) << endl;
    }

    fout.close();
}


#endif //EXAM1_5_QUADRATICSPLINE_H
