#pragma once
#include <iostream>
#include "Utils.h"
#include <math.h>
#include <vector>
namespace gauss {

	void cargarDatos(int n, std::vector<std::vector<double>> &a, std::vector<double> &b) {
		double dato;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				std::cout << i + 1 << j + 1 << std::endl;
				std::cin >> dato;
				a[i][j] = dato;
			}
			std::cout << "Ingrese el termino independiente" << std::endl;
			std::cin >> dato;
			b[i] = dato;
		}
	}
	void mostrarMatriz(int n, std::vector<std::vector<double>> a, std::vector<double> b) {
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				std::cout << a[i][j];
			}
			std::cout << b[i] << std::endl;
		}
	}

	void triangular(int n, std::vector<std::vector<double>> a, std::vector<double> b) {
		double m;
		for (int i = 0; i < n-1; i++)
		{
			for (int j = 0; j < n; j++)
			{

			}
		}
	}

}



