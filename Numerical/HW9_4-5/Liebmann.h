//
// Created by Steven Proctor on 4/19/17.
//

#ifndef HW9_4_5_LIEBMANN_H
#define HW9_4_5_LIEBMANN_H

#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

//const int NODES = 11;

class Liebmann {
public:
    void solve();

private:
    vector<vector<double>> T;           //store the temperature at each node
    double top = 0.00;                  //boundary temp of the top of the plate
    double left = 0.00;                 //boundary temp of the left of the plate
    double right = 0.00;                //boundary temp of the right of the plate
    double bottom = 0.00;               //boundary temp of the bottom of the plate
    double relax = 1.2;                 //relaxation factor
    double accError = 1;                //acceptable error
    bool insulateL = false;             //true if left side is insulated
    bool insulateR = false;             //true if right side is insulated
    bool insulateB = false;             //true if bottom side is insulated
    bool insulateT = false;             //true if top side is insulated
    double step, centerTemp;
    int rad;
    bool xtrHt = false;
    int NODES;
    int numRows, numCols;   //number of rows and columns in the matrix

    void setBoundaries();               //creates the matrix based on initial conditions
    void printTemp();                   //prints the temperature matrix
    void getInfo();                     //get boundary conditions from the user
    void reset();                       //clears the matrix
    void extraHeat();
    void fixCenter();
    void getCoordinate();
};

/*
 * clears the matrix and sets insulation to false
 */
void Liebmann::reset() {
    insulateL = false;
    insulateR = false;
    insulateB = false;
    insulateT = false;
    T.clear();
    numRows = 0;
    numCols = 0;
}


/*
 * obtains boundary conditions from the user
 */
void Liebmann::getInfo() {
    char entry;
    double x;

    cout << "\nEnter the square dimension of the plate (cm)\n";
    cin >> x;
    cout << "\nEnter the step size (cm)\n";
    cin >> step;

    NODES = (int)(x / step) + 1;
    numCols = NODES;
    numRows = NODES;

    cout << "\nEnter the boundary condition for the top of the plate\n";
    cin >> top;
    cout << "\nEnter the boundary condition for the right of the plate\n";
    cin >> right;
    cout << "\nEnter the boundary condition for the bottom of the plate\n";
    cin >> bottom;
    cout << "\nEnter the boundary condition for the left of the plate\n";
    cin >> left;

    cout << "\nAre any of the sides insulated? ('y' or 'n')\n";
    do { cin >> entry; } while (entry != 'y' && entry != 'n');

    if (entry == 'y') {
        do {
            cout << "\nWhich side is insulated? ('l', 'r', 'u', 'd')\n";
            do { cin >> entry; } while (entry != 'l' && entry != 'r' && entry != 'u' && entry != 'd');

            if (entry == 'l') { insulateL = true; }
            if (entry == 'r') { insulateR = true; }
            if (entry == 'u') { insulateT = true; }
            if (entry == 'd') { insulateB = true; }

            cout << "\nAre any other sides insulated? ('y' or 'n')\n";
            do { cin >> entry; } while (entry != 'y' && entry != 'n');

        } while (entry == 'y');
    }

    setBoundaries();

    cout << "\nWould you like to add a heated rod to the center of the plate? ('y' or 'n')\n";
    do { cin >> entry; } while (entry != 'y' && entry != 'n');

    if (entry == 'y') { extraHeat(); }

    cout << "\nEnter the relaxation factor\n";
    cin >> relax;

    cout << "\nEnter acceptable error in terms of a percent\n";
    cin >> accError;
}

/*
 * creates the matrix based on the boundary conditions
 */
void Liebmann::setBoundaries() {
    if (!insulateT) { numRows--; }
    if (!insulateB) { numRows--; }
    if (!insulateL) { numCols--; }
    if (!insulateR) { numCols--; }

    for (int i = 0; i < NODES; i++) {
        vector<double> temp;
        for (int j = 0; j < NODES; j++) {
            temp.push_back(0);
        }
        T.push_back(temp);
    }

    for (int i = 0; i < NODES; i++) {
        T[0][i] = top;
        T[i][NODES-1] = right;
        T[NODES-1][i] = bottom;
        T[i][0] = left;
    }

    T[0][0] = -1;
    T[NODES-1][NODES-1] = -1;
    T[NODES-1][0] = -1;
    T[0][NODES-1] = -1;

    if (insulateL) {
        T[0][0] = top;
        T[NODES-1][0] = bottom;
    }
    if (insulateR) {
        T[0][NODES-1] = top;
        T[NODES-1][NODES-1] = bottom;
    }
    if (insulateT) {
        T[0][0] = left;
        T[0][NODES-1] = right;
    }
    if (insulateB) {
        T[NODES-1][0] = left;
        T[NODES-1][NODES-1] = right;
    }
}


void Liebmann::extraHeat() {
    xtrHt = true;

    cout << "\nEnter the diameter of the rod\n";
    cin >> rad;
    rad /= 2 * step;

    cout << "\nEnter the temperature of the rod\n";
    cin >> centerTemp;

    fixCenter();
}

/*
 * maintains the center of the plate at the temperature of the rod
 */
void Liebmann::fixCenter() {
    int center = NODES / 2;
    int k = 0;
    for (int i = center - rad; i <= center; i++) {
        for (int j = center - k; j <= center + k; j++) {
            T[i][j] = centerTemp;
            T[i + 2*rad - 2*k][j] = centerTemp;
        }
        if (k < rad) { k++; }
    }
}


/*
 * solves for the temperature of the plate at equilibrium
 */
void Liebmann::solve() {
    reset();
    getInfo();

    double oldT, newT, error;
    int divide = 2;
    if (xtrHt) { divide *= rad * 2; }

    int lStart, rEnd, tStart, bEnd;
    if (insulateL) { lStart = 0; }
    else { lStart = 1; }
    if (insulateR) { rEnd = NODES; }
    else { rEnd = NODES - 1; }
    if (insulateT) { tStart = 0; }
    else { tStart = 1; }
    if (insulateB) { bEnd = NODES; }
    else { bEnd = NODES - 1; }

    int test = (bEnd - tStart) / divide;

    do {
        oldT = T[test][test];
        for (int i = tStart; i < bEnd; i++) {
            for (int j = lStart; j < rEnd; j++) {
                if (insulateL && j == 0) {
                    newT = (T[i - 1][j] + T[i + 1][j] + (2 * T[i][j + 1])) / 4.0;
                }
                else if (insulateR && j == NODES - 1) {
                    newT = (T[i - 1][j] + T[i + 1][j] + (2 * T[i][j - 1])) / 4.0;
                }
                else if (insulateT && i == 0) {
                    newT = ((2 * T[i + 1][j]) + T[i][j - 1] + T[i][j + 1]) / 4.0;
                }
                else if (insulateB && i == NODES - 1) {
                    newT = ((2 * T[i - 1][j]) + T[i][j + 1] + T[i][j - 1]) / 4.0;
                }
                else {
                    newT = (T[i - 1][j] + T[i + 1][j] + T[i][j - 1] + T[i][j + 1]) / 4.0;
                }
                T[i][j] = relax * newT + (1 - relax) * T[i][j];

                if (xtrHt) { fixCenter(); }
            }
        }
        newT = T[test][test];
        error = abs((newT-oldT)/newT)*100;
    } while (error > accError);

    printTemp();
    getCoordinate();
}


/*
 * prints the temperature matrix
 */
void Liebmann::printTemp() {
    cout << endl << endl;
    int width = 15;

    for (int i = 0; i < NODES * width - NODES; i++) {
        cout << "-";
    }
    cout << endl;
    for (int i = 0; i < NODES; i++) {
        cout << "|";
        for (int j = 0; j < NODES; j++) {
            if (j != 0) {cout << setw(width);}
            if (T[i][j] == -1) {
                cout << "XX";
            }
            else {
                cout << setprecision(5) << T[i][j];
            }
        }
        cout << "|" << endl;
    }
    for (int i = 0; i < NODES * width - NODES; i++) {
        cout << "-";
    }
    cout << endl;
}



void Liebmann::getCoordinate() {
    int x, y;
    do {
        cout << "\nEnter a coordinate for which you want to know the temperature: (Enter '-1' and '-1' to exit)";
        cout << "\n(Starting from the bottom left corner, X is measure from left to right and Y is measured bottom to top)";
        cout << "\nX: ";
        cin >> x;
        cout << "Y: ";
        cin >> y;

        if (x != -1 && y != -1) {
            cout << "\nThe Temperature at (" << x << "," << y << ") = " << T[numRows - (y/step)][(x/step)] << endl;
        }
        cout << endl << endl;
    } while (x != -1 && y != -1);
}

#endif //HW9_4_5_LIEBMANN_H
