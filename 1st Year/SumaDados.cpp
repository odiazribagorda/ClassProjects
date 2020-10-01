#include <iostream>
using namespace std;

// Programa que dados 4 valores de unos dados, los suma dos a dos e indica el mayor.

int main() {

	// Declaración de variables.
	int j1 = 0, j2 = 0, jT = 0, a1 = 0, a2 = 0, aT = 0, numVeces = 0;

	cin >> numVeces;

	// Bucle para repetir la operación un numVeces.
	for (int i = 0; i < numVeces; ++i) {
		cin >> j1 >> j2 >> a1 >> a2;
		jT = j1 + j2;
		aT = a1 + a2;

		// Devuelve la solución en función del resultado.
		if ((jT - aT) < 0) {
			cout << "ANA " << aT << " JORGE " << jT << endl;
		}
		if ((jT - aT) > 0) {
			cout << "JORGE " << jT << " ANA " << aT << endl;
		}
		if ((jT - aT) == 0) {
			cout << "EMPATE " << jT << endl;
		}
	}

	return 0;
}