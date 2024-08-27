#pragma once
#include "Utils.h"
#include<iostream>

namespace biseccion {
	
	// 1 . detectar en cual de los 2 intervalos esta la funcion.

	double Error = 0.00001, a = 2.8, b = 2.9, e = NULL;
	template<typename Func>
	void CalcularIntervalo(double &a, double &b,double &anterior,Func F) {
		double m = ((a + b) / 2);
		if (F(a) * F(m) < 0)
		{
			b = m;
			anterior = m;
		}
		if (F(m) * F(b) < 0) {
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