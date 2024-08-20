#pragma once
#include "Utils.h"
#include<iostream>

namespace biseccion {
	
	// 1 . detectar en cual de los 2 intervalos esta la funcion.

	double Error = 0.00001, a = 2.8, b = 2.9, e = NULL;
	void CalcularIntervalo(double &a, double &b,double &anterior) {
		double m = ((a + b) / 2);
		if (evaluar(a) * evaluar(m) < 0)
		{
			b = m;
			anterior = m;
		}
		if (evaluar(m) * evaluar(b) < 0) {
			a = m;
			anterior = m;
		}
	}

	double run(double anterior) {
		double er;
		CalcularIntervalo(a, b, anterior);
		std::cout << "Nuevo intervalo" << a << " " << b << std::endl;
		double raiz = ((a + b) / 2);
		if (evaluar(raiz) == 0)
		{
			return raiz;
		}
			if (anterior != NULL)
			{
				er = CalcularError(anterior, raiz);
				std::cout <<"El error actual es " << er << std::endl;
				if (er < Error)
				{
					return raiz;
				}
				else
				{
					return run(anterior);
				}
			}
	}
}