#pragma once
#include "Utils.h"
#include<iostream>
#include <iomanip>
namespace biseccion {
	
	// 1 . detectar en cual de los 2 intervalos esta la funcion.
	template<typename Func>
	void buscarIntervalo(double &a, double &b, Func F) {
		double fa = F(a);
		double fb;
		double paso = 0.05;
		for (double x = a + paso; x <= b; x += paso) {
			fb = F(x);
			if (fa * fb < 0) {
				std::cout << "Intervalo con cambio de signo: [" << a << ", "<< std::setprecision(16) << x << "]" << std::endl;
				a = fa;
				b = fb + paso;
				return;
			}
			fa = fb;
		}

		std::cout << "No se encontró un intervalo con cambio de signo en [" << a << ", " << b << "]" << std::endl;
	}


	double Error = 0.00001, a =-10, b = 5, e = NULL;
	template<typename Func>
	void CalcularIntervalo(double &a, double &b,double &anterior,Func F) {
		double m = ((a + b) / 2);
		if (F(a) * F(m) < 0)
		{
			b = m;
			anterior = m;
		}
		if (F(m) * F(b) < 0) {
			std::cout << "Intervalo de raiz" << std::endl;
			a = m;
			anterior = m;
		}
	}
	template<typename Func>
	double run(double anterior,Func F) {
		double er;

		CalcularIntervalo(a, b, anterior,F);
		double raiz = ((a + b) / 2);
		if (F(raiz) == 0)
		{
			return raiz;
		}
			if (anterior != NULL)
			{
				er = CalcularError(anterior, raiz);
				if (er < Error)
				{
					return raiz;
				}
				else
				{
					return run(anterior,F);
				}
			}
	}
}