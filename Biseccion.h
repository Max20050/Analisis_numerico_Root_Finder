#pragma once
#include "Utils.h"
#include<iostream>
#include <iomanip>
namespace biseccion {
    using namespace std;

    template <typename Func>
    void biseccion(Func f, double a, double b, double E) {
        double c, e = 1;
        while (e >= E) {
            c = (a + b) / 2;
            if ((f(a) * f(c)) < 0) {
                b = c;
                c = (a + b) / 2;
                e = abs(a - c);
                cout << "error actual: " << e << endl;
                cout << "el intervalo actual es: (" << a << "," << c << ")\n";
            }

            else {
                a = c;
                c = (a + b) / 2;
                e = abs(b - c);
                cout << "error actual: " << e << endl;
                cout << "el intervalo actual es: (" << b << "," << c << ")\n";
            }
        }

        cout << "la funcion tiene raiz en: " << (a + c) / 2 << endl;
    }
    template <typename Func>
    void barrido(Func f, double ampl) {
        double i = -20;
        double a = -20;
        double b = a + ampl;
        while (i < 21) {
            if ((f(a)*f(b)<0)) {
                cout << "Hay una raiz en el intervalo: " << a << " y " << b << endl;
                a = a + ampl;
                b = b + ampl;
            }
            else {
                a = a + ampl;
                b = b + ampl;
            }
            i += ampl;
        }
    }
}