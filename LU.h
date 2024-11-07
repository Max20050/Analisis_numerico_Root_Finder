#pragma once
#include "Utils.h"
#include <vector>


namespace LU {
	void mostrarMatriz(std::vector<std::vector<double>> a) {
		int n = a.size();
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				std::cout << a[i][j] << "  ";
			}
			std::cout<<std::endl;
		}
	}



	void CalcularLU(std::vector<std::vector<double>> &matrix,std::vector<std::vector<double>> &factors) {
		const int n = matrix.size();

		for (int k = 0; k < n; ++k) {
			for (int i = k + 1; i < n; ++i) {
				double factor = matrix[i][k] / matrix[k][k];
				factors[i][k] = factor;
				for (int j = k; j < n; ++j) {
					matrix[i][j] -= factor * matrix[k][j];
				}
			}
		}
		for (int i = 0; i < factors.size(); i++)
		{
			factors[i][i] = 1;
		}
	}


	void calcularY(std::vector<std::vector<double>> L,std::vector<double> b,std::vector<double> &y) {
		double sum = 0;
		for (int i = 0; i < b.size(); i++)
		{
			if (i == 0)
			{
				sum = 0;
			}
			else {
				for (int j = 0; j < i; j++)
				{
					sum += L[i][j]*y[j];
				}
			}
			y[i] = (b[i] - (sum));
			sum = 0;
		}
	}

	void calcularX(std::vector<std::vector<double>> U, std::vector<double> b, std::vector<double>& x) {
		int n = U.size();
		double sumatoria = 0;

		for (int i = n - 1; i >= 0; --i)
		{
			if (i == n - 1) {
				sumatoria = 0;
			}
			else
			{
				for (int j = i + 1; j < n; j++)
				{
					sumatoria += x[j] * U[i][j];
				}
			}
			x[i] = ((b[i] - sumatoria) / U[i][i]);
			sumatoria = 0;
		}
	}

}


namespace condicion {
    using namespace std;

    // Función para calcular el determinante de una matriz de tamaño n usando el método de cofactores
    double determinante(const vector<vector<double>>& A, int n) {
        if (n == 1) {
            return A[0][0];
        }

        double det = 0;
        vector<vector<double>> temp(n, vector<double>(n));  // Submatriz temporal para el cálculo

        for (int p = 0; p < n; p++) {
            int h = 0; // Índice para filas
            for (int i = 1; i < n; i++) { // Formamos la submatriz
                int k = 0;
                for (int j = 0; j < n; j++) {
                    if (j == p) continue;
                    temp[h][k] = A[i][j];
                    k++;
                }
                h++;
            }
            // Cofactor y expansión por la primera fila
            det += pow(-1, p) * A[0][p] * determinante(temp, n - 1);
        }
        std::cout << "Det:" << det << std::endl;
        return det;
    }

    // Función para calcular la norma 2 de una matriz de tamaño n (espectral) usando la suma de los cuadrados
    double norma2(const vector<vector<double>>& A, int n) {
        double sum = 0.0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                sum += A[i][j] * A[i][j];
            }
        }
        return sqrt(sum);
    }

    // Función para calcular la inversa de una matriz de tamaño n usando el método de la matriz adjunta
    bool inversa(const vector<vector<double>>& A, vector<vector<double>>& A_inv, int n) {
        double det = determinante(A, n);
        if (det == 0) {
            return false;  // La matriz no es invertible
        }

        // Calculamos la matriz adjunta (transpuesta de la matriz de cofactores)
        vector<vector<double>> adj(n, vector<double>(n));

        // Calculamos la matriz de cofactores
        vector<vector<double>> temp(n, vector<double>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // Formar la submatriz al eliminar la fila i y columna j
                int h = 0, k = 0;
                for (int r = 0; r < n; r++) {
                    if (r == i) continue;
                    k = 0;
                    for (int c = 0; c < n; c++) {
                        if (c == j) continue;
                        temp[h][k] = A[r][c];
                        k++;
                    }
                    h++;
                }
                adj[j][i] = pow(-1, i + j) * determinante(temp, n - 1);  // Cofactor transpuesto
            }
        }

        // Multiplicamos por 1/determinante para obtener la inversa
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A_inv[i][j] = adj[i][j] / det;
            }
        }

        return true;
    }

    // Función para calcular el número de condición de una matriz de tamaño n
    double numeroDeCondicion(const vector<vector<double>>& A, int n) {
        // Determinante de A
        double detA = determinante(A, n);
        if (detA == 0) {
            cout << "La matriz no es invertible. El número de condición no puede ser calculado." << endl;
            return -1;
        }

        // Calcular la norma 2 de A
        double normaA = norma2(A, n);

        // Calcular la inversa de A
        vector<vector<double>> A_inv(n, vector<double>(n));
        if (!inversa(A, A_inv, n)) {
            cout << "No se pudo calcular la inversa de la matriz." << endl;
            return -1;
        }

        // Calcular la norma 2 de A_inv
        double normaA_inv = norma2(A_inv, n);

        // El número de condición es el producto de las normas
        return normaA * normaA_inv;
    }
}

