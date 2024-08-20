#include <iostream>
#include <windows.h>
#include "Biseccion.h"
#include "PuntoFijo.h"
#include "ui.h"
using namespace std;


int main() {

	/*
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

	float x0 = 1.2;
	float r;

	__try {
		r = pfijo::run(x0);
	}
	__except (GetExceptionCode() == EXCEPTION_STACK_OVERFLOW) {
		std::cerr << "Programa sin memoria" << std::endl;
		_resetstkoflw();

	}
	std::cout << r << std::endl;

	return 0;


}