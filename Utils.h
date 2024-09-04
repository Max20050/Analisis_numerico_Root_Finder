#pragma once
#include <math.h>
#include <vector>
#include <iostream>

// prueba Sin(x) a = 2 , b = 4
double pi = 3.14159265359, e = 2.7182818284;

float CalcularError(double anterior, double punto) {
	return(abs(((punto - anterior) / punto)) * 100);
}

template<class T>
void printVec(std::vector<T> a) {
	for (int i = 0; i < a.size(); i++)
	{
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
}