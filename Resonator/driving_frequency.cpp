//
// driving_frequency.cpp
// Resonators - Vibrations
//
// Created by Steven Proctor on 10/24/16.
// Copyright © 2016 Steven Proctor. All rights reserved.
//

#include "driving_frequency.h"

Resonator::Resonator() {
    m = 0;
    k1 = 0;
    k2 = 0;
    c1 = 0;
    c2 = 0;
    Y = 0;
    r = 0;
}

Resonator::~Resonator() = default;

void Resonator::solveResonator(double mass, double spring1, double spring2, double damper1, double damper2, double ratio, double amplitude) {

    m = mass;
    k1 = spring1;
    k2 = spring2;
    c1 = damper1;
    c2 = damper2;
    r = ratio;
    Y = amplitude;
    k_eq = springEquivilent();
    c_eq = damperEquivilent();
    w_n = naturalFrequency();
    w = drivingFrequency();
    z = dampingRatio();
    F_0 = initialForce();
    alpha = phaseAngle_force();
    X_p = amplitude_particularSolution();
    phi = phaseAngle_particularSolution();
    H = frequencyResponse();
    FT_base = maxForce_base();
    Ft_base = forceTransmissibility_base();
    FT_wall = maxForce_wall();
    Ft_wall = forceTransmissibility_wall();
    d_st = staticAmplitude();
    T_d = displacementTransmissibility();

}

double Resonator::springEquivilent() { return k1 + k2; }

double Resonator::damperEquivilent() { return c1 + c2; }

double Resonator::naturalFrequency() { return sqrt(k_eq / m); }

double Resonator::drivingFrequency() { return w_n * r; }

double Resonator::dampingRatio() { return (c_eq / (2 * sqrt(m * k_eq))); }

double Resonator::initialForce() { return Y * sqrt(k2 * k2 + pow((c2 * w), 2)); }

double Resonator::phaseAngle_force() { return atan(-(c2 * w) / k2); }

double Resonator::amplitude_particularSolution() { return (F_0 / k_eq) / sqrt(pow((1 - r * r), 2) + pow((2 * z * r), 2)); }

double Resonator::phaseAngle_particularSolution() { return atan((r * (2 * z * k2 - c2 * w_n * (1.0 - r * r))) / (k2 * (1 - r * r) + 2 * c2 * w_n * z * r * r)); }

double Resonator::displacementTransmissibility() { return X_p / Y; }

double Resonator::frequencyResponse() { return X_p / (F_0 / k_eq); }

double Resonator::maxForce_base() { return -X_p * sqrt(pow((k1 - k_eq * r * r), 2) + pow((c1 * w_n * r), 2)); }

double Resonator::forceTransmissibility_base() { return -FT_base / (Y * k2); }

double Resonator::maxForce_wall() { return X_p * sqrt(k1 * k1 + pow((c1 * r * w_n), 2)); }

double Resonator::forceTransmissibility_wall() { return FT_wall / (Y * k2); }

double Resonator::staticAmplitude() { return X_p * sqrt(pow((1 - r * r), 2) + pow((2 * z * r), 2)); }