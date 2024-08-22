#pragma once
#include "Utils.h"


namespace secante {

	static const double error = 0.00001;
	double er;

	double run(double &x0,double &x1) {
		double x2 = (x1 - ((evaluar(x1) * (x0 - x1)) / (evaluar(x0) - evaluar(x1))));
		er = abs(evaluar(x2));
		if (er < error)
		{
			return x2;
		}
		else {
			return run(x1, x2);
		}
	}
}




