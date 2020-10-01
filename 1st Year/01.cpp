//Oscar Diaz Ribagorda (DG05)

#include <iostream>
#include <fstream>

using namespace std;

const int TAM_MATRIZ = 9, SUMA = 45, MULTIPLICA = 362880;

typedef int tSudoku[TAM_MATRIZ][TAM_MATRIZ];


int main() {
	int numVeces = 0;
	tSudoku matriz;

	cin >> numVeces;


	for (int i = 0; i < numVeces; ++i) {
		int multiplicacion = 1, suma = 0, fila = 0, columna = 0, cuadrante = 0;
		bool ok = true;

		for (int f = 0; f < TAM_MATRIZ; ++f)
			for (int c = 0; c < TAM_MATRIZ; ++c)
				cin >> matriz[f][c];
		

		while (fila < TAM_MATRIZ && ok) {
			for (columna = 0; columna < TAM_MATRIZ; ++columna) {
				suma += matriz[fila][columna];
				multiplicacion *= matriz[fila][columna];
			}
			if (suma != SUMA || multiplicacion != MULTIPLICA) ok = false;
			suma = 0; multiplicacion = 1;
			++fila;
		}


		columna = 0;
		while (columna < TAM_MATRIZ && ok) {
			for (fila = 0; fila < TAM_MATRIZ; ++fila) {
				suma += matriz[fila][columna];
				multiplicacion *= matriz[fila][columna];
			}
			if (suma != SUMA || multiplicacion != MULTIPLICA) ok = false;
			suma = 0; multiplicacion = 1;
			++columna;
		}

		fila = 0; columna = 0;

		while (cuadrante < TAM_MATRIZ && ok) {
			switch (cuadrante) {

			case 0: for (columna = 0; columna < 3; ++columna) {
				for (fila = 0; fila < 3; ++fila) {
					suma += matriz[fila][columna];
					multiplicacion *= matriz[fila][columna];
				}
			}
					break;
			case 1: for (columna = 3; columna < 6; ++columna) {
				for (fila = 0; fila < 3; ++fila) {
					suma += matriz[fila][columna];
					multiplicacion *= matriz[fila][columna];
				}
			}
					break;
			case 2: for (columna = 6; columna < 9; ++columna) {
				for (fila = 0; fila < 3; ++fila) {
					suma += matriz[fila][columna];
					multiplicacion *= matriz[fila][columna];
				}
			}
					break;
			case 3: for (columna = 0; columna < 3; ++columna) {
				for (fila = 3; fila < 6; ++fila) {
					suma += matriz[fila][columna];
					multiplicacion *= matriz[fila][columna];
				}
			}
					break;
			case 4: for (columna = 3; columna < 6; ++columna) {
				for (fila = 3; fila < 6; ++fila) {
					suma += matriz[fila][columna];
					multiplicacion *= matriz[fila][columna];
				}
			}
					break;
			case 5: for (columna = 6; columna < 9; ++columna) {
				for (fila = 3; fila < 6; ++fila) {
					suma += matriz[fila][columna];
					multiplicacion *= matriz[fila][columna];
				}
			}
					break;
			case 6: for (columna = 0; columna < 3; ++columna) {
				for (fila = 6; fila < 9; ++fila) {
					suma += matriz[fila][columna];
					multiplicacion *= matriz[fila][columna];
				}
			}
					break;
			case 7: for (columna = 3; columna < 6; ++columna) {
				for (fila = 6; fila < 9; ++fila) {
					suma += matriz[fila][columna];
					multiplicacion *= matriz[fila][columna];
				}
			}
					break;
			case 8: for (columna = 6; columna < 9; ++columna) {
				for (fila = 6; fila < 9; ++fila) {
					suma += matriz[fila][columna];
					multiplicacion *= matriz[fila][columna];
				}
			}
					break;
			}
			if (suma != SUMA || multiplicacion != MULTIPLICA) ok = false;
			suma = 0; multiplicacion = 1;
			++cuadrante;
		}
		
		if (ok) cout << "SI\n";
		else cout << "NO\n";
	}

	return 0;
}