// Oscar Diaz Ribagorda (DG05)

#include <iostream>
#include <vector>

using namespace std;

// Funcion que ordena de menor a mayor los elementos de un vector de enteros.
void ordenar(vector<int> & pilas) {
	int pilaAux = 0, puntero = 0;
	for (int i = 1; i < pilas.size(); ++i) {
		pilaAux = pilas[i];
		puntero = i;
		while (puntero > 0 && pilas[puntero - 1] > pilaAux) {
			pilas[puntero] = pilas[puntero - 1];
			--puntero;
		}
		pilas[puntero] = pilaAux;
	}
}

/* Funcion que a partir de un vector de enteros y un valor fijo determina el 
numero de parejas (sin repeticiones) maximo que superan ese valor. */
int contarCoches(vector<int> const& pilas, int voltaje) {
	int contInf = 0, contSup = pilas.size() - 1, numCoches = 0;
	while (contInf != contSup) {
		if (pilas[contInf] + pilas[contSup] >= voltaje) {
			++numCoches;
			--contSup;
			if(contSup != contInf) 
				++contInf;
		}
		else ++contInf;
	}

	return numCoches;
}

int main() {
	int pila = 0, numVeces = 0, voltaje = 0, numPilas = 0, numCoches = 0;

	cin >> numVeces;

	for (int i = 0; i < numVeces; ++i) {
		cin >> numPilas >> voltaje;

		// Se crea y lee el vector de enteros de un tamaño dado.
		vector<int> pilas(numPilas);
		for (int j = 0; j < numPilas; ++j) {
			cin >> pilas[j];
		}

		ordenar(pilas);
		numCoches = contarCoches(pilas, voltaje);
		cout << numCoches << '\n';
	}

	return 0;
}