// Oscar Diaz Ribagorda (DG05)

#include <iostream>

using namespace std;

const int TAM_MAX = 50;

void colocarGranos(int gallinero[TAM_MAX][TAM_MAX], int & filas, int & columnas) {
	int numPollos = 0;
	int posFila = 0, posCol = 0, resistencia = 0;
	char orientacion = ' ';
	int numDesplazamiento = 0, cont = 0;

	cin >> filas >> columnas >> numPollos;

	for (int i = 0; i < numPollos; ++i) {
		cin >> posFila >> posCol >> orientacion >> resistencia;
		--posFila; --posCol;


		if (0 <= posFila && posFila < filas && 0 <= posCol && posCol < columnas && 0 < resistencia)
			++gallinero[posFila][posCol];

		while (0 <= posFila && posFila < filas && 0 <= posCol && posCol < columnas && 0 < resistencia) {

			switch (orientacion) {
			case 'N': --posFila; ++cont; --resistencia;
				while (0 <= posFila && posFila < filas && 0 < resistencia && cont < (numDesplazamiento / 2) + 1) {
					++gallinero[posFila][posCol];
					--posFila; ++cont; --resistencia;
				}
				orientacion = 'E';
				break;
			case 'E': ++posCol; ++cont; --resistencia;
				while (0 <= posCol && posCol < columnas && 0 < resistencia && cont < (numDesplazamiento / 2) + 1) {
					++gallinero[posFila][posCol];
					++posCol; ++cont; --resistencia;
				}
				orientacion = 'S';
				break;
			case 'S': ++posFila; ++cont; --resistencia;
				while (0 <= posFila && posFila < filas && 0 < resistencia && cont < (numDesplazamiento / 2) + 1) {
					++gallinero[posFila][posCol];
					++posFila; ++cont; --resistencia;
				}
				orientacion = 'W';
				break;
			case 'W': --posCol; ++cont; --resistencia;
				while (0 <= posCol && posCol < columnas && 0 < resistencia && cont < (numDesplazamiento / 2) + 1) {
					++gallinero[posFila][posCol];
					--posCol; ++cont; --resistencia;
				}
				orientacion = 'N';
				break;
			}
			if (0 <= posFila && posFila < filas && 0 <= posCol && posCol < columnas)
				++gallinero[posFila][posCol];

			cont = 0;
			++numDesplazamiento;
		}

		numDesplazamiento = 0;
	}
}

void mostrar(int const gallinero[TAM_MAX][TAM_MAX], int & filas, int & columnas) {
	for (int i = 0; i < filas; ++i) {
		cout << gallinero[i][0];
		for (int j = 1; j < columnas; ++j)
			cout << ' ' << gallinero[i][j];
		cout << '\n';
	}
	cout << "---\n";
}

int main() {
	int numVeces = 0, filas = 0, columnas = 0;
	int gallinero[TAM_MAX][TAM_MAX] = { 0 };

	cin >> numVeces;

	for (int i = 0; i < numVeces; ++i) {
		colocarGranos(gallinero, filas, columnas);
		mostrar(gallinero, filas, columnas);
		for (int j = 0; j < TAM_MAX; ++j)
			for (int k = 0; k < TAM_MAX; ++k)
			gallinero[j][k] = 0;
	}

	return 0;
}