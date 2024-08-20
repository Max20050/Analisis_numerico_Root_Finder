#pragma once
#include "Utils.h"


namespace pfijo {
	
	double a=0, b=1,error=0.0001;
	
	float run(float &x0){
			float x1;
			x1 = evaluarG(x0);
			float er = CalcularError(x0, x1);
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


