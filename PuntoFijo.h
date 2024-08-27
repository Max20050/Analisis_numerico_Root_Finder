#pragma once
#include "Utils.h"


namespace pfijo {
	
	double a=0, b=1,error=0.0001;
	template<typename Func>
	double run(double &x0,Func g){
			double x1;
			x1 = g(x0);
			double er = CalcularError(x0, x1);
			if (er > error)
			{
				return run(x1,g);
			}
			else
			{
				return x1;
			}
	};

}


