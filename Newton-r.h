#pragma once
#include "Utils.h"

namespace newton {

	double error = 0.00001;

	double run(double&x0) {
		double x1;
		x1 = (x0 - ((evaluar(x0)) / (evaluarDerivada(x0))));
		double er = CalcularError(x0, x1);
		if (er < error)
		{
			return x1;
		}
		else
		{
			return run(x1);
		}
	}
}
