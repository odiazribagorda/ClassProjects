// Oscar Diaz Ribagorda (DG05)

#include <iostream>

using namespace std;

enum tParcela { Sol, Sombra, Arbol };

const int MAX_TAM = 500;

int rellenarSombra(tParcela camping[MAX_TAM][MAX_TAM], int numArboles, int f, int c) {
	int numSombras = 0, col = 0, fila = 0;

	for (int i = 0; i < numArboles; ++i) {
		cin >> fila >> col;
		--fila; --col;
		camping[fila][col] = Arbol;

		if (fila != 0) {
			if(camping[fila - 1][col] != Arbol)
				camping[fila - 1][col] = Sombra;
			if (col != 0 && camping[fila - 1][col - 1] != Arbol)
				camping[fila - 1][col - 1] = Sombra;
			if (col != c - 1 && camping[fila - 1][col + 1] != Arbol)
				camping[fila - 1][col + 1] = Sombra;
		}
		if (fila != f + 1) {
			if (camping[fila + 1][col] != Arbol)
				camping[fila + 1][col] = Sombra;
			if (col != 0 && camping[fila + 1][col - 1] != Arbol)
				camping[fila + 1][col - 1] = Sombra;
			if (col != c - 1 && camping[fila + 1][col + 1] != Arbol)
				camping[fila + 1][col + 1] = Sombra;
		}
		if (col != 0 && camping[fila][col - 1] != Arbol)
			camping[fila][col - 1] = Sombra;
		if (col != c - 1 && camping[fila][col + 1] != Arbol)
			camping[fila][col + 1] = Sombra;
	}

	for (int i = 0; i < f; ++i)
		for (int j = 0; j < c; ++j)
			if (camping[i][j] == Sombra)
				++numSombras;

	return numSombras;
}

int main() {
	tParcela camping[MAX_TAM][MAX_TAM];
	int f = 0, c = 0, numArboles = 0, numSombras = 0;

	cin >> f >> c >> numArboles;

	while ((f != 0 && c != 0) | numArboles != 0) {
		if (numArboles != 0) {
			for (int i = 0; i < f; ++i)
				for (int j = 0; j < c; ++j)
					camping[i][j] = Sol;
			numSombras = rellenarSombra(camping, numArboles, f, c);
			cout << numSombras << '\n';
		}
		else cout << 0 << '\n';

		cin >> f >> c >> numArboles;
	}
	return 0;
}