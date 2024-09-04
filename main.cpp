#include <iostream>
#include <math.h>
#include <windows.h>
#include "Biseccion.h"
#include "PuntoFijo.h"
#include "ui.h"
#include "Newton-r.h"
#include "Secante.h"
#include "ecuaciones.h"
#include "LU.h"
#include <vector>
using namespace std;

void MenuBi() { // BISECCION
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


void MenuPFijo() { // PUNTO FIJO
	double x0 = 3;
	double r;
	auto g = [](double x) {return ((5 - 2 * pow(x, 3) + 11.7 * pow(x, 2)) / 17.7); };
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
		{5,"Sistema de Ecuaciones Gauss"},
		{6,"Gauss seidel"},
		{7,"LU"},
		{0,"Salir"}
	};

	UiMenu::MostrarMenu(8,Menu1);

	int option = UiMenu::selection(Menu1, 7);

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
	
	case 3: { // NEWTON RAPHSON
		double r, x0;
		x0 = 3;
		auto F = [](double x) {return (2 * pow(x, 3) - 11.7 * pow(x, 2) + 17.7 * x - 5); }; // Funcion F primitiva
		auto F´ = [](double x) {return (6 * pow(x, 2) - 23.4 * x + 17.7); }; // Funcion F derivada primera
		r = newton::run(x0,F,F´);
		std::cout << r << std::endl;
		break;
	}
	case 4: { // METODO SECANTE
		auto F = [](double x) {return (2 * pow(x, 3) - 11.7 * pow(x, 2) + 17.7 * x - 5); }; // Funcion F metodo secante
		double r, x0 = 3, x1 = 4;
		r = secante::run(x0, x1,F);
		std::cout << "Raiz encontrada en x = " << r << std::endl;
		break;
	}
	case 5: { // Gauss E.Lineal
		std::vector<std::vector<double>> a = {
			{3, -0.1, -0.2},
			{0.1, 7.0, -0.3},
			{0.3, -0.2, 10}
		};
		std::vector<double> b = {
			{7.85,19.30,71.40}
		};
		
		std::vector<double> raices;
		raices.resize(b.size());

		gauss::mostrarMatriz(a, b);
		gauss::triangulateMatrix(a,raices,b);
		std::cout << "La matriz triangulada queda como" << std::endl;
		gauss::mostrarMatriz(a, b);
		gauss::mostrarRaices(raices);
		break;
	}
	case 6: { // Gauss Siedel
		std::vector<double> x = { // Valores iniciales de X
			{0,0,0}
		};
		seidel::point p(0, 0, 0);
		auto E = [](double x0, double x1, double x2) {return((7.85 - (-0.1 * x1 - 0.2 * x2)) / 3); }; // Ecuacion 1 
		auto E1 = [](double x0, double x1, double x2) {return((19.30 - (0.1 * x0 - 0.3 * x2)) / 7); }; // Ecuacion 2 
		auto E2 = [](double x0, double x1, double x2) {return((71.40 - (0.3 * x0 - 0.2 * x1)) / 10); }; // Ecuacion 3 
		seidel::run(E, E1, E2, x, p);
		std::cout << p.x << " " << p.y << " " << p.z << std::endl;
		break;
	}
	case 7: {
	// Vectores y matrices
		std::vector<std::vector<double>> a = { // matriz a de coeficientes
			{3, -0.1, -0.2},
			{0.1, 7.0, -0.3},
			{0.3, -0.2, 10}
		};
		std::vector<double> b = { {7.85,19.30,71.40} }; // Terminos independientes principales
		std::vector<std::vector<double>> factors{ // Matriz de los multiplicadores m de gauss
			{0,0,0},
			{0,0,0},
			{0,0,0}
		};
		std::vector<double> y; // Valores de Y de [L]*[Y]
		y.resize(a.size());

		std::vector<double> x;
		x.resize(a.size());

		// Programa
		LU::CalcularLU(a, factors);
		std::cout << "La matriz U es: " << std::endl;
		LU::mostrarMatriz(a);
		std::cout << std::endl;
		std::cout << "La matriz L es: " << std::endl;
		LU::mostrarMatriz(factors);
		std::cout << std::endl;
		std::cout << "El vector [Y] es: " << std::endl;
		LU::calcularY(factors, b, y);
		printVec(y);
		LU::calcularX(a, y, x);
		std::cout << std::endl;
		std::cout << "La solucion al sistema es: " << std::endl;
		printVec(x);
		break;
	}	
	default:
		break;
	}

	std::cin.ignore();
	return 0;
}