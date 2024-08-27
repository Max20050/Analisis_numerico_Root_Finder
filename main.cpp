#include <iostream>
#include <math.h>
#include <windows.h>
#include "Biseccion.h"
#include "PuntoFijo.h"
#include "ui.h"
#include "Newton-r.h"
#include "Secante.h"
#include "ecuaciones.h"
using namespace std;

void MenuBi() {
	double r;
	auto F = [](double x) {return (sin(x) + cos(pow(x, 2))); }; // <- Remplazar return para cada funcion que se quiere pasar
	try
	{
		r = biseccion::run(NULL,F);
	}
	catch (bad_alloc& ex)
	{
		std::cout << "Memoria insuficiente, pruebe con un numero menor de error" << std::endl;
	};
	std::cout << r << std::endl;
}

void MenuPFijo() {
	double x0 = 0.7;
	double r;
	auto g = [](double x) {return(cos(x)); };
	__try {
		r = pfijo::run(x0,g);
	}
	__except (GetExceptionCode() == EXCEPTION_STACK_OVERFLOW) {
		std::cerr << "Su funcion G(x) es divergente, considere cambiarla." << std::endl;
		_resetstkoflw();
	}
	std::cout << r << std::endl;
}


int main() {

	UiMenu::Menu Menu1[]{
		{1,"Metodo de la biseccion"},
		{2,"Metodo del Punto Fijo"},
		{3,"Metodo de Newton Raphson"},
		{4,"Metodo de la secante"},
		{5,"Ec.No Lineal P.Fijo"},
		{6,"Ec.No Lineal N.Raphson"},
		{0,"Salir"}
	};

	UiMenu::MostrarMenu(7,Menu1);

	int option = UiMenu::selection(Menu1, 6);

	switch (option)
	{
	case 0: {
		return 0;
	}
	case 1: {
		MenuBi();
		break;
	}
	case 2: {
		MenuPFijo();
		break;
	}
	case 3: {
		double r, x0;
		x0 = 0;
		r = newton::run(x0);
		std::cout << r << std::endl;
		break;
	}
	case 4: {
		double r, x0 = 0, x1 = 1;
		r = secante::run(x0, x1);
		std::cout << "Raiz encontrada en x = " << r << std::endl;
		break;
	}
	case 5: {
		auto ec1 = [](double x, double y) {return (sqrt(10 - x * y)); }; // <- Remplazar ec1
		auto ec2 = [](double x, double y) {return (sqrt((57 - x) / (3 * y))); }; // <- Remplazar ec2
		ecuaciones::point p(0, 0);
		ecuaciones::run(p, 1.5, 3.5,ec1,ec2);
		std::cout << p.x << " " << p.y << std::endl;
		break;
	}
	default:
		break;
	}

	std::cin.ignore();

	// CODE SAVE


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

	/*
	* ECUACIONES LINEALES - P FIJO
	ecuaciones::point p(0, 0);
	ecuaciones::run(p, 1.5, 3.5);

	std::cout << p.x << " " << p.y << std::endl;
	*/



	return 0;
}