#include <iostream>
using namespace std;

int main() {

	// Declaramos variables.
	int a1 = 0, aN = 0, total = 0, N = 0, numVeces= 0;

	// Pedimos numero de datos a calcular.
	// cout << "Introduzca numero de datos a calcular: " << endl;
	cin >> numVeces;

	// Bucle que pide datos y devuelve soluciones (el numero de veces pedido).
	for (int i = 0; i < numVeces; ++i) {
		cin >> a1 >> aN;
		N = aN - a1 + 1;
		total = N * (a1 + aN) / 2;
		cout << total << endl;
	}
	// system("pause");

	return 0;
}