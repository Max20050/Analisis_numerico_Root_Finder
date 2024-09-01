#pragma once
#include <math.h>

// prueba Sin(x) a = 2 , b = 4
double pi = 3.14159265359, e = 2.7182818284;

float CalcularError(double anterior, double punto) {
	return(abs(((punto - anterior) / punto)) * 100);
}