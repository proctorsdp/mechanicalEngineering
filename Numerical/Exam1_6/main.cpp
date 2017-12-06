#include <iostream>
#include <complex>
#include <valarray>
#include <vector>
#include <fstream>

using namespace std;

const double PI = 3.141592653589793238460;

typedef complex<double> Complex;
typedef valarray<Complex> CArray;

// Cooley–Tukey FFT (in-place, divide-and-conquer)
void fft(CArray& x)
{
    const size_t N = x.size();
    if (N <= 1) return;

    // divide
    CArray even = x[slice(0, N/2, 2)];
    CArray  odd = x[slice(1, N/2, 2)];

    // conquer
    fft(even);
    fft(odd);

    // combine
    for (size_t k = 0; k < N/2; ++k)
    {
        Complex t = polar(1.0, -2 * PI * k / N) * odd[k];
        x[k    ] = even[k] + t;
        x[k+N/2] = even[k] - t;
    }
}

double ft(double first, double w, double a[], double b[], double t) {
    double val;
    val = first;
    for (int i = 1; i <= 4; i++) {
        val += a[i]*cos(i*w*t) + b[i]*sin(i*w*t);
    }
    //+ a[1]*cos(w*t) + b[1]*sin(w*t) +
      //      a[2]*cos(2*w*t) + b[2]*sin(2*w*t) +
        //    a[3]*cos(3*w*t) + b[3]*sin(3*w*t) +
          //  a[4]*cos(4*w*t) + b[4]*sin(4*w*t);
    return val;
}

int main() {

    const Complex f[] = {1.9295, 0.4634, -2.1835, 1.1660, 0.8435, 1.4096, -0.3635, -1.0530};
    const int N = 8;
    CArray data(f, N);
    double A[N], B[N];
    double T = .4;
    double w0 = 2*PI/T;
    vector<double> y, t;
    double Bi, Ar;

    // forward fft
    fft(data);

    cout << "fft" << endl;
    for (int i = 0; i < 8; ++i)
    {
        cout << data[i] << endl;
    }

    double A0_2 = real(data[0])/N;
    for (int i = 1; i < N/2; i++) {
        Ar = real(data[i]);
        Bi = imag(data[i]);
        A[i] = (2/double(N)) * Ar;
        B[i] = (-2/double(N)) * Bi;
    }
    Ar = real(data[N/2]);
    Bi = imag(data[N/2]);
    A[N/2] = (1/double(N)) * Ar;
    B[N/2] = (-1/double(N)) * Bi;

    for (double i = 0; i <= .36; i+=.01) {
        y.push_back(ft(A0_2, w0, A, B, i));
        t.push_back(i);
    }

    fstream fout;
    fout.open("fourierTransform.csv");

    if(!fout.is_open()) {exit(1);}

    double x = 0;
    for (int i = 0; i < N; i++) {
        fout << x << "," << real(f[i]) << endl;
        x+=.05;
    }

    fout << endl << endl << endl << endl;

    for (int i = 0; i < y.size(); i++) {
        fout << t[i] << "," << y[i] << endl;
    }

    fout.close();

    cout << endl << endl;
    cout << "A0_2 = " << A0_2 << endl;

    for (int i = 1; i <= N/2; i++) {
        cout << "A" << i << " = " << A[i] << endl;
        cout << "B" << i << " = " << B[i] << endl;
    }

    return 0;
}