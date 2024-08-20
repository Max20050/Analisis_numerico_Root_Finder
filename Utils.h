#pragma once
#include <math.h>

// prueba Sin(x) a = 2 , b = 4
double pi = 3.14159265359, e = 2.7182818284;



float evaluar(float x) {
	return (pow(x,2)-1); // 	return (sin(x)+cos(pow(x,2))); <- biseccion
}

float evaluarG(float x) {
	std::cout << x << std::endl;
	return (1/x);
}



float CalcularError(double anterior, double punto) {
	return(abs(((punto - anterior) / punto)) * 100);
}