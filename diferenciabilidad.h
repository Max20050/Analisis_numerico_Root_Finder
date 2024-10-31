#pragma once
#include<vector>
#include<iostream>

namespace derivada3puntos {
    template <typename Func>
    void EvaluarInicio(std::vector<double>& evaluaciones, Func F, double a, double b, double h) {
        for (double i = a; i <= b; i += h)
        {
            evaluaciones.push_back((F(i)));
        }
    };
    void derivar(std::vector<double> evaluaciones, std::vector<double>& derivadasPuntuales, double a, double b, double h) {
        int n = evaluaciones.size();
        for (int i = 0; i < n; i++)
        {
            if (i == 0)
            {
                derivadasPuntuales.push_back((-3 * evaluaciones.at(i) + 4 * evaluaciones.at(i + 1) - evaluaciones.at(i + 2)) / (2 * h));
            }
            if (i == evaluaciones.size() - 1)
            {
                derivadasPuntuales.push_back(((evaluaciones.at(i - 2) - 4 * evaluaciones.at(i - 1) + 3 * evaluaciones.at(i)) / 2 * h));
            } if (i > 0 && i < (evaluaciones.size() - 1))
            {
                derivadasPuntuales.push_back((evaluaciones.at(i + 1) - evaluaciones.at(i - 1)) / (2 * h));
            }
        }
    };

    void printDerivada(std::vector<double> derivadasPuntuales, std::vector<double> evaluaciones, double a, double b, double h) {
        int n = derivadasPuntuales.size();
        int count = 0;
        for (double i = a; i <= b; i += h)
        {
            std::cout << "Xi:" << i << " | F(x):" << evaluaciones.at(count) << " | F'(x):" << derivadasPuntuales.at(count) << std::endl;
            count++;
        }
    }
}

namespace derivada5puntos {
    template <typename Func>
    void EvaluarInicio(std::vector<double>& evaluaciones, Func F, double a, double b, double h) {
        for (double i = a; i <= b; i += h)
        {
            evaluaciones.push_back((F(i)));
        }
    };
    void derivar(std::vector<double> evaluaciones, std::vector<double>& derivadasPuntuales, double a, double b, double h) {
        int n = evaluaciones.size();
        for (int i = 0; i < n; i++)
        {
            if (i == 0 || i == 1)
            {
                derivadasPuntuales.push_back((-25 * evaluaciones.at(i) + 48 * evaluaciones.at(i + 1) - 36 * evaluaciones.at(i + 2) + 16 * evaluaciones.at(i + 3) - 3 * evaluaciones.at(i + 4)) / (12 * h));
            }
            if (i > evaluaciones.size() - 3)
            {
                derivadasPuntuales.push_back(((evaluaciones.at(i - 2) - 4 * evaluaciones.at(i - 1) + 3 * evaluaciones.at(i)) / 2 * h));
            } if (i > 2 && i < (evaluaciones.size() - 1))
            {
                derivadasPuntuales.push_back((evaluaciones.at(i + 1) - evaluaciones.at(i - 1)) / (2 * h));
            }
        }
    };

    void printDerivada(std::vector<double> derivadasPuntuales, std::vector<double> evaluaciones, double a, double b, double h) {
        int n = derivadasPuntuales.size();
        int count = 0;
        for (double i = a; i <= b; i += h)
        {
            std::cout << "Xi:" << i << " | F(x):" << evaluaciones.at(count) << " | F'(x):" << derivadasPuntuales.at(count) << std::endl;
            count++;
        }
    }
}


namespace trapecios {
    double calcularH(double a, double b, int n) {
        return((b - a) / n);
    }


    template <typename Func>
    void trapecios(double a, double b, Func F, int n,double passed_h,bool table) {
        double h = passed_h;
        if (table == false)
        {
            h = calcularH(a, b, n);
        }
        
        std::cout << "H:" << h << std::endl;
        std::vector<double> trapecios;
        for (int i = 0; i <= n; i++)
        {
            std::cout << "i:" << i << " | Xi:" << i * h << " | F(Xi):" << F(a + i * h) << std::endl;
            trapecios.push_back(F(a + i * h));
        }
        double sum = 0;
        for (int i = 1; i < trapecios.size() - 1; i++)
        {
            sum += trapecios.at(i);
        }
        std::cout << sum << std::endl;
        std::cout << "El resultado de la integral por el metodo de los trapecios es:" << std::endl;
        std::cout << "It: " << ((b - a) * (F(a) + 2 * sum + F(b))) / (2 * n);
        std::cout << " u.a"<<std::endl;
    }
  
}


namespace simpson {
    double calcularH(double a, double b, int n) {
        return((b - a) / n);
    }


    template <typename Func>
    void simpson(double a, double b, Func F, int n,double passed_h,bool table) {
        double h = passed_h;
        if (table == false)
        {
            h = calcularH(a, b, n);
        }
        std::cout << "H:" << h << std::endl;
        std::vector<double> sim;
        for (int i = 0; i <= n; i++)
        {
            std::cout << "i:" << i << " | Xi:" << i * h << " | F(Xi):" << F(a + i * h) << std::endl;
            sim.push_back(F(a + i * h));
        }
        double sumpar = 0;
        double sumimpar = 0;
        for (int i = 1; i < sim.size() - 1; i++)
        {
            if (i % 2 == 0)
            {
                sumpar += sim.at(i);
            }
            else
            {
                sumimpar += sim.at(i);
            }
        }
        std::cout << "Suma par: " << sumpar << " Suma Impar: " << sumimpar << std::endl;
        std::cout << "La integral por el metodo de simpson es: ";
        std::cout << "Is:" << ((b - a) * (F(a) + 4 * sumimpar + 2 * sumpar + F(b))) / (3 * n);
        std::cout << " u.a";
    }
}


namespace euler {
    double f(double x, double y) {
        return pow(2.718281828, 0.8 * x) - 0.5 * y;
    }

    void euler(double a, double b, double h, double y0) {
        double x = a;
        double y = y0;

        std::cout << "Puntos calculados:" << std::endl;
        std::cout << "x\t\ty" << std::endl;
        int i = 0;
        while (x <= b) {
            y += h * f(x, y);
            x += h;
            std::cout<<i<<" " << x << "\t\t" << y << std::endl;
            i++;
        }
    }
}


namespace heun {
    double f(double x, double y) {
        return pow(2.718281828, 0.8 * x) - 0.5 * y;
    }
    void heun(double a, double b, double h, double y0) {
        double x = a;
        double y = y0;
        double y_0 = y0;
        std::cout << "Puntos calculados:" << std::endl;
        std::cout << "x\t\ty0\t\ty" << std::endl;

        while (x <= b) {
            double k1 = h * f(x, y);
            y_0 += k1;
            double k2 = h * f(x + h, y + k1);
            y += (0.5 * (k1 + k2));
            x += h;

            std::cout << x << "\t\t" << y_0 << "\t\t" << y << std::endl;
        }
    }

}


namespace kutta {
    // Función que define la EDO: dy/dx = f(x, y)
    double f(double x, double y) {
        return pow(2.718281828, 0.8 * x) - 0.5 * y; // Ejemplo: y' = xy
    }

    // Método de Runge-Kutta de segundo orden para resolver la EDO
    void rungeKutta(double a, double b, double h, double y0) {
        double x = a;
        double y = y0;

        std::cout << "Puntos calculados:" << std::endl;
        std::cout << "x\t\ty\t\tk1\t\tk2" << std::endl;
        double sumk1 = 0;
        double sumk2 = 0;
        while (x <= b) {
            double k1 = h * f(x, y);
            double k2 = h * f(x + h / 2.0, y + k1 / 2.0);
            y += k2;
            x += h;
            sumk1 += k1;
            sumk2 += k2;
            std::cout << x << "\t\t" << y << "\t\t" << sumk1 << "\t\t" << sumk2 << std::endl;
        }
    }
}