#pragma once
#include "Utils.h"
#include <vector>


namespace LU {
	void mostrarMatriz(std::vector<std::vector<double>> a) {
		int n = a.size();
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				std::cout << a[i][j] << "  ";
			}
			std::cout<<std::endl;
		}
	}



	void CalcularLU(std::vector<std::vector<double>> &matrix,std::vector<std::vector<double>> &factors) {
		const int n = matrix.size();

		for (int k = 0; k < n; ++k) {
			for (int i = k + 1; i < n; ++i) {
				double factor = matrix[i][k] / matrix[k][k];
				factors[i][k] = factor;
				for (int j = k; j < n; ++j) {
					matrix[i][j] -= factor * matrix[k][j];
				}
			}
		}
		for (int i = 0; i < factors.size(); i++)
		{
			factors[i][i] = 1;
		}
	}


	void calcularY(std::vector<std::vector<double>> L,std::vector<double> b,std::vector<double> &y) {
		double sum = 0;
		for (int i = 0; i < b.size(); i++)
		{
			if (i == 0)
			{
				sum = 0;
			}
			else {
				for (int j = 0; j < i; j++)
				{
					sum += L[i][j]*y[j];
				}
			}
			y[i] = (b[i] - (sum));
			sum = 0;
		}
	}

	void calcularX(std::vector<std::vector<double>> U, std::vector<double> b, std::vector<double>& x) {
		int n = U.size();
		double sumatoria = 0;

		for (int i = n - 1; i >= 0; --i)
		{
			if (i == n - 1) {
				sumatoria = 0;
			}
			else
			{
				for (int j = i + 1; j < n; j++)
				{
					sumatoria += x[j] * U[i][j];
				}
			}
			x[i] = ((b[i] - sumatoria) / U[i][i]);
			sumatoria = 0;
		}
	}

}


/*

1 a1 a2 <- sum = a1*x2 + a2*x3
0 1 a <- sum = a*x2
0 0 1 <- sum = 0 
*/


