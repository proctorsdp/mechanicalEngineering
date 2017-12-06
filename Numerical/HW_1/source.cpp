// MAE 3210, HW 1, Problem 2.26
// Created by Steven Proctor on 1/11/17.
//
// Determine the height of a rocket given a specific time
// Based on the equations given in problem 2.26

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

//Returns the height (in feet) of the rocket
//given a specific time (in seconds)
double height(double);

//Source Code (Body)
int main() {
    double entry;

    //Obtain current time from the user
    cout << "********************************************************************\n";
    cout << "Enter the current time of the rocket's flight:\n";
    cin >> entry;

    //Prints the current height of rocket and repeats process until user quits
    while (entry != -99) {
        cout << endl << "The rocket's height at " << setprecision(2) << fixed << entry;
        cout << " seconds is: " << setprecision(1) << fixed << height(entry) << " feet\n";
        cout << "********************************************************************\n";
        cout << endl << endl << endl;

        cout << "********************************************************************\n";
        cout << "Enter the current time of the rocket's flight: (Enter '-99' to Exit)\n";
        cin >> entry;
    }

    return 0;
}

//Takes in time, returns rocket height
double height(double time) {
    double height;      //Stores the current height of the rocket

    if (time <= 0) {
        return 0;       //Returns height = 0 if time time is before rocket launch
    }
    else if (time < 15) {       //Returns height if time is between 0 to 15 seconds
        height = (38.1454 * time) + (0.13743 * pow(time, 3));
    }
    else if (time < 33) {       //Returns height if time is between 15 to 33 seconds
        height = 1036 + (130.909 * (time - 15)) + (6.18425 * pow(time - 15, 2)) - (0.428 * pow(time - 15, 3));
    }
    else {      //Returns height if time is greater than 33 seconds
        height = 2900 - (62.468 * (time - 33)) - (16.927 * pow(time - 33, 2)) + (0.41796 * pow(time - 33, 3));
    }

    if (height < 0) {
        height = 0;     //If equation gives a negative height, changes to height = 0
    }

    return height;
}