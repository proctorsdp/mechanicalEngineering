//
//  main.cpp
//  Lift Coefficient
//
//  Created by Steven Proctor on 10/22/15.
//  Copyright © 2015 Steven Proctor. All rights reserved.
//

#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<math.h>
using namespace std;

void bottomIntegral(double, double, double, double, double &);
void topIntegral(double, double, double, double, double &);
void bottomPressureIntegral(double, double, double, double, double &);
void topPressureIntegral(double, double, double, double, double &);
void inIntegral(double, double, double, double, double, double, double &);
void outIntegral(double, double, double, double, double, double, double &);

int main()
{
    char garbage;
    string moreGarbage;
    double x1, x2, y1, y2, u1, u2, v1, v2, p1, p2, bottomValue, topValue, inValue, outValue, liftCoeff, topPressure, bottomPressure;
    int i = 0, j, k = 0;
    ifstream fin;

    fin.open("values.txt");

    if (!fin) {
        cout << "File Not Found\n";
        return 9;
    }

    while (k < 5)
    {
        fin >> garbage;
        k++;
    }

    while (i < 4)
    {
        j = 0;
        fin >> garbage;
        getline(fin, moreGarbage);

        fin >> x1;
        fin >> y1;
        fin >> u1;
        fin >> v1;
        fin >> p1;
        fin >> x2;
        fin >> y2;
        fin >> u2;
        fin >> v2;
        fin >> p2;

        switch (i)
        {
            case 0:
                bottomIntegral(x1, x2, v1, v2, bottomValue);
                bottomPressureIntegral(x1, x2, p1, p2, bottomPressure);
                break;
            case 1:
                topIntegral(x1, x2, v1, v2, topValue);
                topPressureIntegral(x1, x2, p1, p2, topPressure);
                break;
            case 2:
                inIntegral(y1, y2, u1, u2, v1, v2, inValue);
                break;
            case 3:
                outIntegral(y1, y2, u1, u2, v1, v2, outValue);
                break;
        }

        while (j < 49)
        {
            x1 = x2;
            y1 = y2;
            u1 = u2;
            v1 = v2;
            p1 = p2;
            fin >> x2;
            fin >> y2;
            fin >> u2;
            fin >> v2;
            fin >> p2;

            switch (i)
            {
                case 0:
                    bottomIntegral(x1, x2, v1, v2, bottomValue);
                    bottomPressureIntegral(x1, x2, p1, p2, bottomPressure);
                    break;
                case 1:
                    topIntegral(x1, x2, v1, v2, topValue);
                    topPressureIntegral(x1, x2, p1, p2, topPressure);
                    break;
                case 2:
                    inIntegral(y1, y2, u1, u2, v1, v2, inValue);
                    break;
                case 3:
                    outIntegral(y1, y2, u1, u2, v1, v2, outValue);
                    break;
            }

            j++;
        }

        i++;
    }

    liftCoeff = -2 * (outValue - inValue + topValue - bottomValue - bottomPressure + topPressure);
    cout << "LIFT COEFFICIENT CALCULATOR" << endl << endl;
    cout << "Momentum Integral, Top     =  " << topValue << endl;
    cout << "Momentum Integral, Bottom  =  " << bottomValue<< endl;
    cout << "Momentum Integral, Left    =  " << inValue << endl;
    cout << "Momentum Integral, Right   =  " << outValue << endl << endl;
    cout << "Pressure Integral, Top     =  " << topPressure << endl;
    cout << "Pressure Integral, Bottom  =  " << bottomPressure << endl << endl << endl;
    cout << "The Lift Coefficient (Cl) for the air foil = " << liftCoeff << endl << endl << endl << endl;

    fin.close();

    return 0;
}

void bottomIntegral(double x1, double x2, double v1, double v2, double & bottomValue) {
    bottomValue += (((x2 - x1) / 2) * (pow(v1, 2) + (pow(v2, 2))));
}

void topIntegral(double x1, double x2, double v1, double v2, double & topValue) {
    topValue += (((x2 - x1) / 2) * (pow(v1, 2) + (pow(v2, 2))));
}

void bottomPressureIntegral(double x1, double x2, double p1, double p2, double & bottomPressure) {
    bottomPressure += (((x2 - x1) / 2) * (p1 + p2));
}

void topPressureIntegral(double x1, double x2, double p1, double p2, double & topPressure) {
    topPressure += (((x2 - x1) / 2) * (p1 + p2));
}

void inIntegral(double y1, double y2, double u1, double u2, double v1, double v2, double & inValue) {
    inValue += (((y2 - y1) / 2) * ((u1 * v1) + (u2 * v2)));
}

void outIntegral(double y1, double y2, double u1, double u2, double v1, double v2, double & outValue) {
    outValue += (((y2 - y1) / 2) * ((u1 * v1) + (u2 * v2)));
}