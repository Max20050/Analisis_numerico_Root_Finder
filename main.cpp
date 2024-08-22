#include <iostream>
#include <windows.h>
#include "Biseccion.h"
#include "PuntoFijo.h"
#include "ui.h"
#include "Newton-r.h"
#include "Secante.h"
using namespace std;


int main() {

	/*
	BISECCION
	double r;
	try
	{
		r = biseccion::run(NULL);
	}
	catch (bad_alloc& ex)
	{
		std::cout << "Memoria insuficiente, pruebe con un numero menor de error" << std::endl;
	};
	std::cout << r << std::endl;
	*/

	/*
	PUNTO FIJO
	float x0 = 1.2;
	float r;

	__try {
		r = pfijo::run(x0);
	}
	__except (GetExceptionCode() == EXCEPTION_STACK_OVERFLOW) {
		std::cerr << "Programa sin memoria" << std::endl;
		_resetstkoflw();
		return 0;
	}
	std::cout << r << std::endl;
	*/

	/*
	* NEWTON RAPHSON
	double r, x0;
	x0 = 0;
	r = newton::run(x0);
	std::cout << r << std::endl;
	*/

	/*
	* SECANTE
	double r,x0=0,x1=1;

	r = secante::run(x0,x1);
	std::cout<<"Raiz encontrada en x = " << r << std::endl;

	*/

	return 0;
}