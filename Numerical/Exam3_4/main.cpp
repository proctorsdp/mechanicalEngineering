#include <iostream>
#include "euler.h"
#include "rungeKutta.h"

using namespace std;

int main() {

    Euler E;
    RungeKutta R;

    cout << endl << endl;

    cout << "******************************************\n";
    cout << "SOLVING 2ND-ORDER ODE USING EULER'S METHOD\n";
    cout << "******************************************\n";

    E.solve();

    cout << endl;

    cout << "Euler Solver Complete!\n";


    cout << endl << endl;

    cout << "**********************************************************\n";
    cout << "SOLVING 2ND-ORDER ODE USING RUNGE KUTTA'S 4TH-ORDER METHOD\n";
    cout << "**********************************************************\n";

    R.solve();

    cout << endl;

    cout << "Runge Kutta Solver Complete!\n";


    return 0;
}