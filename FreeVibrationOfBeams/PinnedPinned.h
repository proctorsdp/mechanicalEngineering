//
// PinnedPinned.h
// Beam Theory
//
// Created by Steven Proctor on 12/4/16.
// Copyright © 2016 Steven Proctor. All rights reserved.
//

#ifndef PinnedPinned_h
#define PinnedPinned_h

#include <iostream>
#include <math.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>

const double pi = 3.14159265359;

using namespace std;

class PinnedPinned {

private:

    string fileName = "PinnedPinned.csv";
    double width;
    double length;
    double thickness;
    double modulus;
    double density;
    double area;
    double volume;
    double mass;
    double inertia;

    double betaL[4] = { 1 * pi, 2 * pi, 3 * pi, 4 * pi };
    double beta[4];
    double naturalFreq[4];
    double modeShape[4][21];

    void findNatFreq() {
        for (int i = 0; i < 4; i++) {
            naturalFreq[i] = pow(betaL[i], 2.0) * sqrt((modulus * inertia) / (density * area * pow(length, 4.0)));
        }
    }

    void findBeta() {
        for (int i = 0; i < 4; i++) {
            beta[i] = betaL[i] / length;
        }
    }

    void findMode() {
        double x; for (int i = 0; i < 4; i++) { double increment = 0;
            for (int j = 0; j < 21; j++) {
                x = increment * length; modeShape[i][j] = sin(beta[i] * x);
                if (modeShape[i][j] < .00001 && modeShape[i][j] > -.00001) {
                    modeShape[i][j] = 0;
                }
                increment += .05;
            }
        }
    }

    string modeTable() {
        stringstream ss;
        double incr = 0;
        ss << "                          Mode\n";
        ss << " x/L    ----------------------------------------\n";
        ss << "            1          2          3          4\n";
        ss << "------------------------------------------------\n";
        for (int i = 0; i < 21; i++) {
            ss << setw(4) << incr << " ";
            for (int j = 0; j < 4; j++) {
                ss << setw(10) << setprecision(4) << modeShape[j][i] << " ";
            }
            ss << endl;
            incr += .05;
        }
        return ss.str();
    }

    string freqTable() {
        stringstream ss;
        ss << "Mode       Beta        Freq\n";
        ss << "-----------------------------\n";
        for (int i = 0; i < 4; i++) {
            ss << i << ":   " << setprecision(6) << beta[i] << "   " << setprecision(6) << naturalFreq[i] << endl;
        }
        return ss.str();
    }

    string title() {
        stringstream ss;
        ss << "Pinned - Pinned Beam Results\n";
        ss << "****************************\n";
        return ss.str();
    }



    void toCSV() {
        ofstream fout; fout.open(fileName);
        fout << title() << endl;
        fout << "Mode,Beta,Freq\n";
        for (int i = 0; i < 4; i++) {
            fout << i << "," << setprecision(6) << beta[i] << "," << setprecision(6) << naturalFreq[i] << endl;
        }
        fout << endl << endl;
        double incr = 0; fout << ",Mode\n";
        fout << "x/L,1,2,3,4\n";
        for (int i = 0; i < 21; i++) {
            fout << setw(4) << incr << ",";
            for (int j = 0; j < 4; j++) {
                fout << setw(10) << setprecision(4) << modeShape[j][i] << ",";
            }
            fout << endl;
            incr += .05;
        }
        fout.close();
    }

        public:

        PinnedPinned(double E, double row, double L, double h, double b) {
            modulus = E * 1000000000;
            density = row;
            length = L;
            width = b;
            thickness = h;

            area = width * thickness;
            volume = area * length;
            mass = density * volume;
            inertia = width * pow(thickness, 3) / 12;

            findBeta(); findNatFreq(); findMode();
            cout << title() << endl; cout << freqTable() << endl; cout << modeTable() << endl; toCSV();
        }
    };

#endif /* PinnedPinned_h */