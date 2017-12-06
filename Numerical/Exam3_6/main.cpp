#include <iostream>
#include "RK_4Order.h"

using namespace std;

int main() {
    
    RungeKutta R;

    cout << endl << endl;
    cout << "**********************************************************\n";
    cout << "SOLVING 2ND ORDER ODE USING RUNGE KUTTA'S 4TH ORDER METHOD\n";
    cout << "**********************************************************\n";

    R.solve();
    
    return 0;
}