#pragma once
#include <iostream>
#include "Utils.h"
#include <math.h>
namespace ecuaciones {
	class point
	{
	public:
		double x;
		double y;
		point(double x, double y) {
			this->x = x;
			this->y = y;
		} // constructor end
	}; // Class end

	// constantes

	double error = 0.0001;

	// Inicio recursiva
	template<typename Func, typename Func2>
	void run(point &p,double x0,double y0,Func ec1,Func2 ec2) {
		double x1, y1;
		x1 = ec1(x0,y0);
		y1 = ec2(y0,x1);
		if ((CalcularError(x0, x1) < error) && (CalcularError(y0, y1) < error))
		{
			p.x = x1; p.y = y1;
		}
		else
		{
			run(p, x1, y1,ec1,ec2);
		}
	}
}


