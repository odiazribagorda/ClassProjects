// Oscar Diaz Ribagorda (DG04)

#include <iostream>

using namespace std;

const int MAX_TAM = 100;

void leer(int area[MAX_TAM][MAX_TAM], int n) {
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			cin >> area[i][j];
}


/* En esta funcion se suma primero por filas de p en p y se almacena en una matriz auxiliar y despues se suman
	las columnas de esas sumas, asi se tiene la suma de todos los cuadrantes del area.
	*/
void sumarCuadrantes(int sumas[MAX_TAM][MAX_TAM], int const area[MAX_TAM][MAX_TAM], int n, int p) {
	int sumasAux[MAX_TAM][MAX_TAM] = { 0 };

	// El coste de recorrer esta matriz es: n * (p + (n - p)) = n^2.
	for (int i = 0; i < n; ++i) {
		for (int k = 0; k < p; ++k)
			sumasAux[i][0] += area[i][k];
		for (int j = 1; j < n - p + 1; ++j)
			sumasAux[i][j] = sumasAux[i][j - 1] - area[i][j - 1] + area[i][j + p - 1];
	}

	// El coste de recorrer esta matriz es: (n - p) * (p + (n - p)) = n^2 - np ~ n^2
	for (int j = 0; j < n - p + 1; ++j) {
		for (int k = 0; k < p; ++k)
			sumas[0][j] += sumasAux[k][j];
		for (int i = 1; i < n - p + 1; ++i)
			sumas[i][j] = sumas[i - 1][j] - sumasAux[i - 1][j] + sumasAux[i + p - 1][j];
	}
}

/* El coste total del algoritmo es 3 * n^2 ~ n^2 tiene coste cuadratico.
	Se podria haber reducido minimamente calculando el maximo a la vez que se hace la ultima suma
	pero se a preferido la claridad a ese pequeño aumento de eficiencia.
	*/
int calcularMaxPeces(int const area[MAX_TAM][MAX_TAM], int n, int p) {
	int sumas[MAX_TAM][MAX_TAM] = { 0 };

	// Coste total 2 * n^2
	sumarCuadrantes(sumas, area, n, p);

	int max = 0;

	// El coste para recorrer esta matriz y obtener el maximo de las sumas es: (n - p) * (n - p) = n^2 - 2*np - p^2 ~ n^2
	for (int i = 0; i < n - p + 1; ++i)
		for (int j = 0; j < n - p + 1; ++j)
			if (sumas[i][j] > max)
				max = sumas[i][j];
	
	return max;
}

int main() {
	int n = 0, p = 0;

	while (cin >> n >> p) {
		int area[MAX_TAM][MAX_TAM];

		leer(area, n);

		cout << calcularMaxPeces(area, n, p) << '\n';
	}

	return 0;
}