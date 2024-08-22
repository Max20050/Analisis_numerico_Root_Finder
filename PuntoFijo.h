#pragma once
#include "Utils.h"


namespace pfijo {
	
	double a=0, b=1,error=0.0001;
	
	double run(double &x0){
			double x1;
			x1 = evaluarG(x0);
			double er = CalcularError(x0, x1);
			if (er > error)
			{
				return run(x1);
			}
			else
			{
				return x1;
			}
	};

}


