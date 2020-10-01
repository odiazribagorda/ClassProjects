// Oscar Diaz Ribagorda (DG05)

#include <iostream>

using namespace std;

const int MAX_COLUMNAS = 1000, MAX_FILAS = 1000;

// Funciones con la misma estructura para comprobar que el valor es el mayor/menor de la fila/columna.

bool maximoDeSuFila(int f, int c, const int matriz[MAX_FILAS][MAX_COLUMNAS], int numCol) {
	bool esMax = true;
	int cont = 0;

	while (cont < numCol && esMax)
		if (matriz[f][c] < matriz[f][cont]) esMax = false;
		else ++cont;

	return esMax;
}

bool minimoDeSuColumna(int f, int c, const int matriz[MAX_FILAS][MAX_COLUMNAS], int numFil) {
	bool esMin = true;
	int cont = 0;

	while (cont < numFil && esMin)
		if (matriz[f][c] > matriz[cont][c]) esMin = false;
		else ++cont;

	return esMin;
}

bool minimoDeSuFila(int f, int c, const int matriz[MAX_FILAS][MAX_COLUMNAS], int numCol) {
	bool esMin = true;
	int cont = 0;

	while (cont < numCol && esMin)
		if (matriz[f][c] > matriz[f][cont]) esMin = false;
		else ++cont;

	return esMin;
}

bool maximoDeSuColumna(int f, int c, const int matriz[MAX_FILAS][MAX_COLUMNAS], int numFil) {
	bool esMax = true;
	int cont = 0;

	while (cont < numFil && esMax)
		if (matriz[f][c] < matriz[cont][c]) esMax = false;
		else ++cont;

	return esMax;
}


int main() {
	int numCol = 0, numFil = 0, c = 0, f = 0;
	int matriz[MAX_FILAS][MAX_COLUMNAS];
	bool enc = false;

	cin >> numFil >> numCol;

	while (numFil > 0 && numCol > 0) {

		for (int i = 0; i < numFil; ++i) // Para cada caso lee la matriz entera.
			for (int j = 0; j < numCol; ++j)
				cin >> matriz[i][j];

		while (f < numFil && c < numCol && !enc) { // Va comprobando valor a valor si es un valor silla, si no, avanza en la matriz.
			if (maximoDeSuFila(f, c, matriz, numCol) && minimoDeSuColumna(f, c, matriz, numFil)) enc = true;
			else if (minimoDeSuFila(f, c, matriz, numCol) && maximoDeSuColumna(f, c, matriz, numFil)) enc = true;
			else if (c == numCol - 1) {
				++f; c = 0;
			}
			else ++c;
		}

		if (enc) cout << "SI\n"; // Saca SI si ha encontrado 1 valor silla y NO si no ha encontrado ninguno.
		else cout << "NO\n";

		enc = false; f = 0; c = 0; // Inicializa de nuevo los valores para la siguiente vuelta.

		cin >> numFil >> numCol; // Lee siguiente valor.
	}

	return 0;
}