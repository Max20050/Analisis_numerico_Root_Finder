#pragma once
#include <math.h>

// prueba Sin(x) a = 2 , b = 4
double pi = 3.14159265359, e = 2.7182818284;

double evaluar(float x) {
	return ((pow(e, -x)) - x); // 	return (sin(x)+cos(pow(x,2))); <- biseccion
}

double evaluarG(float x) {
	std::cout << x << std::endl;
	return (1/x);
}

double evaluarDerivada(float x) {
	return(( - pow(e, -x)) - 1);
}

float CalcularError(double anterior, double punto) {
	return(abs(((punto - anterior) / punto)) * 100);
}