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
#include "Curvas.h"
#include "diferenciabilidad.h"
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
		{8,"Unidad 2"},
		{0,"Salir"}
	};

	bool unidad2 = false;

	std::cout << "--------------" << std::endl;
	std::cout << "UNIDAD 1" << std::endl;
	std::cout << "--------------" << std::endl;
	UiMenu::MostrarMenu(8,Menu1);

	int option = UiMenu::selection(Menu1, 8);

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
	case 8: {
		unidad2 = true;
		break;
	}
	default:
		break;
	}
	bool DyI = false;

	system("cls");

	if (unidad2 == true)
	{
		std::cout << "--------------" << std::endl;
		std::cout << "UNIDAD 2" << std::endl;
		std::cout << "--------------" << std::endl;
		UiMenu::Menu Menu2[]{
			{1,"Regresion Lineal"},
			{2,"Modelo Exponencial"},
			{3,"Modelo Potencial"},
			{4,"Modelo de crecimiento"},
			{5,"Interpolacion Polinomial de newton"},
			{6,"Polinomio de Lagrange"},
			{7,"Trazadoras cubicas"},
			{8,"Diferenciabilidad e integracion"},
			{0,"Salir"}
		};

		UiMenu::MostrarMenu(8, Menu2);
		int sel = UiMenu::selection(Menu2,8);
		switch (sel)
		{
		case 0: {
			return 0;
		}
		case 1: {
			float a0, a1;
			std::vector<float> x = {1,2,3,4,5,6,7}; // Valores de X
			std::vector<float> y = {0.5,2.5,2,4,3.5,6,5.5}; // Valores de Y
			reg_lineal::run(x,y,a0,a1);
			std::cout << "La funcin Lieal nos queda como: y = " << a0 << " + " << a1 << "x" << std::endl;
			break;
		}
		case 2: {
			std::vector<float> x = { 1,2,3,4,5 }; // Valores de X
			std::vector<float> y = { 0.5,1.7,3.4,5.7,8.4 }; // Valores de Y
			float A, B;
			mod_exp::run(x, y, A, B);
			std::cout << "La funcion exponencial nos queda como: y = " << A << "e^(" << B << "x)" << std::endl;
			break;
		}
		case 3: {
			std::vector<float> x = { 1,2,3,4,5 }; // Valores de X
			std::vector<float> y = { 0.5,1.7,3.4,5.7,8.4 }; // Valores de Y
			float A, B;
			mod_pot::run(x, y, A, B);
			std::cout << "La funcion potencial nos queda como: y = " << A << "X^(" << B <<")" << std::endl;
			break;
		}
		case 4: {
			// Modelo de crecimiento
			break;
		}
		case 5: { // Interpolacion de Newton
			std::vector<double> x = { 1.0000, 2.0000, 3.0000, 5.0000, 6.0000 };
			std::vector<double> y = { 4.7500, 4.0000, 5.2500, 19.7500, 36.0000 };
			int n = x.size();
			vector<vector<double>> dividedDifferences(n, vector<double>(n));
			vector<double> coeffs = pol_newton::newtonInterpolation(x, y, dividedDifferences);
			pol_newton::printDividedDifferences(dividedDifferences);
			std::cout << "El polinomio de newton sin hacer el algebra correspondiente es :" << std::endl;
			pol_newton::printPolynomial(coeffs, x);
			break;
		}
		case 6: { // Interpolacion de Lagrange
			std::vector<double> x = { 0.5000 ,1.0000 ,1.5000 ,2.0000 ,2.5000 ,3.0000 };
			std::vector<double> y = { 1.0000 ,2.1190 ,2.9100 ,3.9450 ,5.7200 ,8.6950 };
			std::vector<std::string> L;
			pol_lagrange::calcularProductorias(L, x);
			pol_lagrange::mostrarPolinomio(L, y);
			break;
		}
		case 7:
			break;
		case 8: {
			DyI = true;
			break;
		}
		default:
			break;
		}


	}
	

	if (DyI == true)
	{
		system("cls");
	UiMenu::Menu M3[]{
		{1,"Derivada 3 puntos"},
		{2,"Derivada 5 puntos"},
		{3,"Metodo de Trapecios"},
		{4,"Metodo de simpson"},
		{5,"EDO,Euler"},
		{6,"EDO,Huen"},
		{7,"Runge Kutta"},
		{0,"Salir"}
	};
	UiMenu::MostrarMenu(8, M3);
	int opcion = UiMenu::selection(M3, 8);
	switch (opcion)
	{
	case 0: {
		return 0;
	}
	case 1: {
		auto F = [](double x) {return pow(2.71, x) * cos(x);};
		double a = 0.0000, b = 2.0000, h = 0.5000;
		bool UsandoTabla = true;
		std::vector<double> evaluaciones = { 0.0000, 0.4207, 0.4546, 0.0706, -0.3784 };
		if (UsandoTabla == false)
		{
			derivada3puntos::EvaluarInicio(evaluaciones, F, a, b, h);
		}
		std::vector<double> derivadasPuntuales;
		derivada3puntos::derivar(evaluaciones, derivadasPuntuales, a, b, h);
		derivada3puntos::printDerivada(derivadasPuntuales, evaluaciones, a, b, h);
		break;
	}
	case 2: {
		auto F = [](double x) {return pow(2.71, x) * cos(x);};
		double a = 0.0000, b = 2.0000, h = 0.5000;
		bool UsandoTabla = true;
		std::vector<double> evaluaciones = { 0.0000, 0.4207, 0.4546, 0.0706, -0.3784 };
		if (UsandoTabla == false)
		{
			derivada5puntos::EvaluarInicio(evaluaciones, F, a, b, h);
		}
		std::vector<double> derivadasPuntuales;
		derivada5puntos::derivar(evaluaciones, derivadasPuntuales, a, b, h);
		derivada5puntos::printDerivada(derivadasPuntuales, evaluaciones, a, b, h);
		break;
	}
	case 3: {
		double a = 0, b = 2*3.14159265359/20;
		int n = 8;
		auto F = [](double x) {return sin(5*x+1);};
		trapecios::trapecios(a, b, F, n,0,false);
		break;
	}
	case 4: {
		double a = 0, b = 2*3.14159265359/20;
		int n = 8;
		auto F = [](double x) {return sin(5 * x + 1);};
		simpson::simpson(a, b, F, n,0,false);
		break;
	}
	case 5: {
		double a = 0.0; 
		double b = 4.0; 
		double h = 0.1; 
		double y0 = 2.0; 
		euler::euler(a, b, h, y0);
		break;
	}
	case 6: {
		double a = 0.0;
		double b = 4.0;
		double h = 0.1;
		double y0 = 2.0;
		heun::heun(a, b, h, y0);
		break;
	}
	case 7: {
		double a = 0.0; 
		double b = 4.0; 
		double h = 0.1; 
		double y0 = 2.0; 
		kutta::rungeKutta(a, b, h, y0);
		break;
	}
	default:
		break;
	}
	}
	system("pause");
	std::cin.ignore();
	return 0;
}