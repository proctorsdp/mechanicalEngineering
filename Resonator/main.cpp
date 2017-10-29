//
// main.cpp
// Resonators - Vibrations
//
// Created by Steven Proctor on 10/22/16.
// Copyright © 2016 Steven Proctor. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <vector>
#include "driving_frequency.h"

using namespace std;

void cinProperties(double &, double &, double &, double &, double &, double &, double &);
void cinProperties(double &, double &, double &, double &, double &, double &, double &, double &);
string outputResults(int, Resonator, double, double, double, double, double, double, double);
void plotOutput(int);
void plotResults(double [], double [], int);
void toCSV(vector<double>, vector<double>, int, string, double, double, double, double, double, double, string var);
void saveToFile(stringstream &);

int main() {

    double m, k1, k2, c1, c2, Y, r;
    char entry;
    int i = 0;
    stringstream singleFreq, temp;

    singleFreq.str("");

    cout << "Type any key to solve a Resonator System with a driving frequency.\n(Type 'q' to skip)\n";
    cin >> entry;
    cout << endl;

    while (entry != 'q') {

        Resonator singleInput;
        temp.str("");

        cinProperties(m, k1, k2, c1, c2, r, Y);
        singleInput.solveResonator(m, k1, k2, c1, c2, r, Y);
        temp << outputResults(i, singleInput, m, k1, k2, c1, c2, r, Y);
        cout << temp.str();

        singleFreq << temp.str();

        i++;
        cout << "Type any key to enter another system ('q' to quit): ";
        cin >> entry;
        cout << endl << endl;

    }
    saveToFile(singleFreq);

    cout << "Type any key to solve a Resonator System with a range of frequencies.\n(Type 'q' to skip)\n";
    cin >> entry;
    cout << endl;

    int run = 0;
    while (entry != 'q') {
        plotOutput(run++);
        cout << "Type any key to enter another system ('q' to quit): ";
        cin >> entry; cout << endl << endl;
    }

    return 0;

}

void cinProperties(double &m, double &k1, double &k2, double &c1, double &c2, double &r, double &Y) {

    cout << "Enter mass: ";
    cin >> m;
    cout << "Enter k1: ";
    cin >> k1;
    cout << "Enter k2: ";
    cin >> k2;
    cout << "Enter c1: ";
    cin >> c1;
    cout << "Enter c2: ";
    cin >> c2;
    cout << "Enter r: ";
    cin >> r;
    cout << "Enter Amplitude: ";
    cin >> Y;

}


void cinProperties(double &m, double &k1, double &k2, double &c1, double &c2, double &Y, double & r_i, double & r_f) {

    cout << "Enter mass: ";
    cin >> m;
    cout << "Enter k1: ";
    cin >> k1;
    cout << "Enter k2: ";
    cin >> k2;
    cout << "Enter c1: ";
    cin >> c1;
    cout << "Enter c2: ";
    cin >> c2;
    cout << "Enter Amplitude: ";
    cin >> Y;
    cout << "Enter the range of r: \n";
    cout << "r_i: ";
    cin >> r_i;
    cout << "r_f: ";
    cin >> r_f;

}

string outputResults(int i, Resonator R, double m, double k1, double k2, double c1, double c2, double r, double Y) {
    stringstream ss;

    ss << endl;
    ss << "Mass: " << m << ", r: " << r << ", Amp: " << Y << endl;
    ss << "k1: " << k1 << ", k2: " << k2 << ", c1: " << c1 << ", c2: " << c2 << endl;
    ss << "********* Solution *********" << endl;
    ss << "Natural Frequency: " << R.get_w_n() << endl;
    ss << "Damping Ratio: " << R.get_z() << endl;
    ss << "Static Amplitude: " << R.get_d_st() << endl;
    ss << "Frequency Response: " << R.get_H() << endl;
    ss << "Phase Angle: " << R.get_phi() << endl;
    ss << "Displacement Transmissibility: " << R.get_T_d() << endl;
    ss << "Force Transmissibility to the base: " << R.get_Ft_base() << endl;
    ss << "Force Transmissibility to the wall: " << R.get_Ft_wall() << endl;
    ss << endl;

    return ss.str();

}

void plotOutput(int run) {
    int numPoints = 1000;
    vector<double> r, H, phi, T_d, Ft_base, Ft_wall, X_p, Fmax_wall;
    double m, k1, k2, c1, c2, Y, r_i, r_f;
    double step = 0;
    stringstream H_title, phi_title, T_d_title, Ft_base_title, Ft_wall_title, X_p_title, Fmax_wall_title;

    r.clear();
    H.clear();
    phi.clear();
    T_d.clear();
    Ft_base.clear();
    Ft_wall.clear();
    X_p.clear();

    cinProperties(m, k1, k2, c1, c2, Y, r_i, r_f);
    step = (r_f - r_i) / double(numPoints);

    for (int i = 0; i <= numPoints; i ++) {
        r.push_back(r_i + (step * i));
    }

    for (int i = 0; i <= numPoints; i++) {

        Resonator Loop;
        Loop.solveResonator(m, k1, k2, c1, c2, r[i], Y);
        H.push_back(Loop.get_H());
        phi.push_back(Loop.get_phi());
        T_d.push_back(Loop.get_T_d());
        Ft_base.push_back(Loop.get_Ft_base());
        Ft_wall.push_back(Loop.get_Ft_wall());
        X_p.push_back(Loop.get_X_p());
        Fmax_wall.push_back(Loop.get_FT_wall());

    }

    H_title << "Frequency_Response" << run << ".csv";
    phi_title << "Phase_Angle" << run << ".csv";
    T_d_title << "Displacement_Transmissibility" << run << ".csv";
    Ft_base_title << "Force_Transmissibility_Base" << run << ".csv";
    Ft_wall_title << "Force_Transmissibility_Wall" << run << ".csv";
    X_p_title << "Max_Amplitude" << run << ".csv";
    Fmax_wall_title << "Max_Force_Wall" << run << ".csv";

    toCSV(r, H, numPoints, H_title.str(), m, k1, k2, c1, c2, Y, "H");
    toCSV(r, phi, numPoints, phi_title.str(), m, k1, k2, c1, c2, Y, "phi");
    toCSV(r, T_d, numPoints, T_d_title.str(), m, k1, k2, c1, c2, Y, "Disp. Trans.");
    toCSV(r, Ft_base, numPoints, Ft_base_title.str(), m, k1, k2, c1, c2, Y, "Force Trans. Base");
    toCSV(r, Ft_wall, numPoints, Ft_wall_title.str(), m, k1, k2, c1, c2, Y, "Force Trans. Wall");
    toCSV(r, X_p, numPoints, X_p_title.str(), m, k1, k2, c1, c2, Y, "X_p");
    toCSV(r, Fmax_wall, numPoints, Fmax_wall_title.str(), m, k1, k2, c1, c2, Y, "Max Force Wall");

    cout << endl << "******** Solution printed to CSV file ********\n" << endl;
}

void toCSV(vector<double> r, vector<double> y, int size, string fileName, double m, double k1, double k2, double c1, double c2, double Y, string var) {

    ofstream fout; fout.open(fileName);

    fout << fileName << ",\n\n\n";
    fout << "mass: " << m << ",";
    fout << "k1: " << k1 << ",";
    fout << "k2: " << k2 << ",";
    fout << "c1: " << c1 << ",";
    fout << "c2: " << c2 << ",";
    fout << "amp: " << Y << ",\n\n\n";

    fout << "r," << var << ",\n";
    for (int i = 0; i <= size; i++) {
        fout << r[i];
        fout << ",";
        fout << y[i];
        fout << ",";
        fout << "\n";
    }

    fout.close();
}

void saveToFile(stringstream & ss) {

    ofstream fout;
    fout.open("Driving_Frequency_Response.txt");
    fout << ss.str();
    fout.close();
}