//
// driving_frequency.h
// Resonators - Vibrations
//
// Created by Steven Proctor on 10/24/16.
// Copyright © 2016 Steven Proctor. All rights reserved.
//

#ifndef driving_frequency_h
#define driving_frequency_h

#include <stdio.h>
#include <iostream>
#include <math.h>

using namespace std;

class Resonator {

public:

    double m, k1, k2, c1, c2, r, Y;

    Resonator();
    ~Resonator();

    void solveResonator(double, double, double, double, double, double, double);
    double get_w_n() { return w_n; }
    double get_z() { return z; }
    double get_d_st() { return d_st; }
    double get_H() { return H; }
    double get_phi() { return phi; }
    double get_T_d() { return T_d; }
    double get_Ft_base() { return Ft_base; }
    double get_Ft_wall() { return Ft_wall; }
    double get_X_p() { return X_p; }
    double get_FT_wall() { return FT_wall; }

private:

    double k_eq, c_eq, w_n, w, z, F_0, alpha, X_p, phi;
    double T_d, H, FT_base, Ft_base, FT_wall, Ft_wall, d_st;

    double springEquivilent();
    double damperEquivilent();
    double naturalFrequency();
    double drivingFrequency();
    double dampingRatio();
    double staticAmplitude();
    double initialForce();
    double phaseAngle_force();
    double amplitude_particularSolution();
    double phaseAngle_particularSolution();
    double displacementTransmissibility();
    double frequencyResponse();
    double maxForce_base();
    double forceTransmissibility_base();
    double maxForce_wall();
    double forceTransmissibility_wall();

};

#endif /* driving_frequency_h */

