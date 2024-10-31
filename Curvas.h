#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include "Utils.h"
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;
namespace reg_lineal {

	float sumatoria1(std::vector<float> x, std::vector<float> y) { // (X*Y)
		float sum = 0;
		for (size_t i = 0; i < x.size(); i++)
		{
			sum += (x.at(i) * y.at(i));
		}
		return sum;
	}

	float sumatoria2(std::vector<float> x) { // (X) (Y) 
		float sum = 0;
		for (size_t i = 0; i < x.size(); i++)
		{
			sum += (x.at(i));
		}
		return sum;
	}

	float sumatoria3(std::vector<float> x) { // X^2
		float sum = 0;
		for (size_t i = 0; i < x.size(); i++)
		{
			sum += (pow(x.at(i),2));
		}
		return sum;
	}

	float sumatoria4(std::vector<float> x) { //(X)^2
		float sum = 0;
		for (size_t i = 0; i < x.size(); i++)
		{
			sum += (x.at(i));
		}
		return (pow(sum,2));
	}

	void run(std::vector<float> x, std::vector<float> y, float &a1, float& a0) {
		int n = x.size();
		float _X, _Y;
		_X = sumatoria2(x) / n;
		_Y = sumatoria2(y) / n;
		a1 = (n * sumatoria1(x, y) - (sumatoria2(x) * sumatoria2(y))) / ( n*sumatoria3(x) - sumatoria4(x));
		a0 = _Y - a1 * _X;
	}
}


namespace mod_exp {

	void toln(std::vector<float> &y) {
		for (int i = 0; i < y.size(); i++)
		{
			y.at(i) = log(y.at(i));
		}
	}

	void run(std::vector<float> x, std::vector<float> y,float &A, float& B) {
		float a0, a1;
		toln(y);
		reg_lineal::run(x, y, a1, a0);
		
		B = a1;
		A = pow(e, a0);
	}
}


namespace mod_pot {

	void tolog(std::vector<float> &y) {
		for (int i = 0; i < y.size(); i++)
		{
			y.at(i) = log10(y.at(i));
		}
	}


	void run(std::vector<float> x, std::vector<float> y, float& A, float& B) {
		float a0, a1;
		tolog(x);
		tolog(y);
		reg_lineal::run(x,y,a1,a0);
		A = pow(10, a0);
		B = a1;
	}

}


namespace pol_newton {
	vector<double> newtonInterpolation(const vector<double>& x, const vector<double>& y, vector<vector<double>>& dividedDifferences) {
		int n = x.size();
		vector<double> coeffs(n);

		// Inicializa la primera columna con los valores y
		for (int i = 0; i < n; i++) {
			dividedDifferences[i][0] = y[i];
		}

		// Calcula las diferencias divididas
		for (int j = 1; j < n; j++) {
			for (int i = 0; i < n - j; i++) {
				dividedDifferences[i][j] = (dividedDifferences[i + 1][j - 1] - dividedDifferences[i][j - 1]) / (x[i + j] - x[i]);
			}
		}

		// Los coeficientes del polinomio son las diferencias divididas
		for (int i = 0; i < n; i++) {
			coeffs[i] = dividedDifferences[0][i];
		}

		return coeffs;
	}

	// Función para evaluar el polinomio de Newton en un punto x
	double evaluateNewtonPolynomial(const vector<double>& coeffs, const vector<double>& x, double x_value) {
		double result = coeffs[0];
		double term = 1;

		for (int i = 1; i < coeffs.size(); i++) {
			term *= (x_value - x[i - 1]);
			result += coeffs[i] * term;
		}

		return result;
	}

	// Función para imprimir el polinomio en forma simplificada
	void printPolynomial(const vector<double>& coeffs, const vector<double>& x) {
		int n = coeffs.size();
		cout << "P(x) = ";

		for (int i = 0; i < n; i++) {
			if (i > 0) cout << " + ";
			cout << fixed << setprecision(4) << coeffs[i];

			for (int j = 0; j < i; j++) {
				cout << "(x - " << x[j] << ")";
			}
		}
		cout << endl;
	}

	// Función para imprimir la tabla de diferencias divididas
	void printDividedDifferences(const vector<vector<double>>& dividedDifferences) {
		int n = dividedDifferences.size();
		cout << "Tabla de Diferencias Divididas:\n";

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n - i; j++) {
				cout << fixed << setprecision(4) << dividedDifferences[i][j] << "\t";
			}
			cout << endl;
		}
	}
}


namespace pol_lagrange {
	void calcularLn(std::vector<std::string>& L, std::vector<double>& x, double num) {
		std::string expresion = "";
		int n = x.size();
		int coun = 0;
		expresion += "((";
		for (int i = 0; i < n; i++)
		{
			if (!(x.at(i) == num))
			{
				if (coun > 0)
				{
					expresion += "*";
				}
				expresion += "(x";
				if (x.at(i) >= 0)
				{
					expresion += "-";
				}
				else
				{
					expresion += "+";
				} expresion += std::to_string(x.at(i));
				expresion += ")";
				coun++;
			}

		}
		expresion += ")/(";
		int count = 0;
		for (int i = 0; i < n; i++)
		{
			if (!(x.at(i) == num))
			{
				if (count > 0)
				{
					expresion += "*";
				}

				expresion += "(";
				expresion += std::to_string(num - x.at(i));
				expresion += ")";
				count++;
			}
		} expresion += "))";
		L.push_back(expresion);
	};

	void calcularProductorias(std::vector<std::string>& L, std::vector<double>& x) {
		for (int i = 0; i < x.size(); i++)
		{
			calcularLn(L, x, (x.at(i)));
		}
	}

	void mostrarPolinomio(std::vector<std::string> L, std::vector<double> y) { // el polinomio no esta simplificado, la expresion se debe pasar por el evaluador
		for (int i = 0; i < y.size(); i++)
		{
			if (i > 0)
			{
				std::cout << "+";
			}
			std::cout << y.at(i) << "*" << L.at(i);
		}

	}
}						  