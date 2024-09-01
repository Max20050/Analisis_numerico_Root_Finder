#pragma once
#include "Utils.h"

namespace newton {

	double error = 0.00001;
	template<typename Func,typename Derived>
	double run(double&x0,Func F,Derived F´) {
		double x1;
		x1 = (x0 - ((F(x0)) / (F´(x0))));
		double er = CalcularError(x0, x1);
		if (er < error)
		{
			return x1;
		}
		else
		{
			return run(x1,F,F´);
		}
	}
}
