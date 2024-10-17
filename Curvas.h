#pragma once
#include <vector>
#include <math.h>
#include "Utils.h"
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
	void run() {

	}
}