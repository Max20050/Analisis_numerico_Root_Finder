#pragma once
#include <iostream>
#include "Utils.h"
#include <math.h>
#include <vector>
namespace gauss {

	void mostrarMatriz(std::vector<std::vector<double>> a, std::vector<double> b) {
		int n = a.size();
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				std::cout << a[i][j]<<"  ";
			}
			std::cout << b[i] << std::endl;
		}
	}


	void triangulateMatrix(std::vector<std::vector<double>>& matrix,std::vector<double> &raices,std::vector<double> &b) {
		const int n = matrix.size();

		for (int k = 0; k < n; ++k) {
			for (int i = k + 1; i < n; ++i) {
				double factor = matrix[i][k] / matrix[k][k];
				for (int j = k; j < n; ++j) {
					matrix[i][j] -= factor * matrix[k][j];
				}
				b[i] -= factor * b[k];
			}
		}

		double sumatoria = 0;

		for (int i = n - 1; i >= 0; --i)
		{
			if (i == n - 1) {
				sumatoria = 0;
			}
			else
			{
				for (int j = i+1; j < n; j++)
				{
					sumatoria += raices[j]*matrix[i][j];
				}
			}
			std::cout << "i: " << i << std::endl;
			raices[i] = ((b[i] - sumatoria) / matrix[i][i]);
			sumatoria = 0;
		}
	}

	const void mostrarRaices(std::vector<double> raices) {
		std::cout << "La solucion del sistema es la siguiente: " << std::endl;
		for (int i = 0; i < raices.size(); i++)
		{
			std::cout << "X" << i << ": " << raices[i]<<std::endl;
		}
	}
}



namespace seidel {
	
	class point
	{
	public:
		double x, y, z;
		point(double x, double y, double z) { this->x = x; this->y = y; this->z = z; };
	};

	double error = 0.0001;
	template<typename Func, typename Func2, typename Func3>
	void run(Func E1, Func2 E2, Func3 E3,std::vector<double> &x, point &p) {
		double x1, y1, z1;
		x1 = E1(x[0], x[1], x[2]);
		y1 = E2(x1, x[1], x[2]);
		z1 = E3(x1, y1, x[2]);
		if ((CalcularError(x[0], x1) < error) && (CalcularError(x[1], y1) < error) && (CalcularError(x[2], z1) < error))
		{
			p.x = x1; p.y = y1; p.z = z1;
		}
		else {
			x[0] = x1; x[1] = y1; x[2] = z1;
			run(E1, E2, E3, x, p);
		}

	}

}



