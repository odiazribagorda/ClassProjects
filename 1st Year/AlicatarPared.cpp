// DG05 Oscar Diaz Ribagorda.

#include <iostream>
using namespace std;

// Programa que calcula los azulejos (de un tamaño dado) necesarios para alicatar una pared (de un tamaño dado).

int main() {
	
	// Declaración de variables.
	int p1 = 0, p2 = 0, a1 = 0, a2 = 0;
	int total = 0, A = 0, B = 0;
	int numVeces = 0;

	cin >> numVeces;

	for (int i = 0; i < numVeces; ++i) {
		cin >> p1 >> p2 >> a1 >> a2;

		// Calculo de operaciones que cuando la division no es entera, se añade un azulejo mas que tendra que ser partido.
		A = p1 / a1;
		if (p1 % a1 != 0)
			A += 1;

		B = p2 / a2;
		if (p2 % a2 != 0)
			B += 1;

		total = A * B;

		// Condicional que reconoce si alguna de las divisiones no es entera y devuelve el valor en consecuencia.
		if (p1 % a1 == 0 && p2 % a2 == 0)
			cout << total << endl;
		else
			cout << total << " NECESITA COMPRAR MAQUINA" << endl;
	}
	return 0;
}