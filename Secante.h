#pragma once
#include "Utils.h"


namespace secante {

	static const double error = 0.0001;
	double er;
	template<typename Func>
	double run(double &x0,double &x1,Func F) {
		double x2 = (x1 - ((F(x1) * (x0 - x1)) / (F(x0) - F(x1))));
		er = abs(F(x2));
		if (er < error)
		{
			return x2;
		}
		else {
			return run(x1, x2,F);
		}
	}
}




