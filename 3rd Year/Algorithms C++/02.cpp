// Oscar Diaz Ribagorda (MARP04)

#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include "bintree_eda.h"

using namespace std;

const int NUM_GRANDE = 100000;

template <class T>
bintree<T> leer(T parada) {
	T aux;
	cin >> aux;
	if (aux == parada) return{};
	else {
		auto iz = leer(parada),
			der = leer(parada);
		return{ iz, aux, der };
	}
}

bool esAvl(bintree<int> const& arbol, int & altura, int & max, int & min) {
	if (arbol.empty()) {
		altura = 0;
		max = 0;
		min = NUM_GRANDE;
		return true;
	}
	else {
		int alturaIz = 0, alturaDer = 0, maxIz = 0, minIz = 0, maxDer = 0, minDer = 0;
		bool aux = esAvl(arbol.left(), alturaIz, maxIz, minIz) &
			esAvl(arbol.right(), alturaDer, maxDer, minDer);
		altura = std::max(alturaIz, alturaDer) + 1;
		bool equilibrado = aux & abs((alturaIz - alturaDer)) <= 1;
		max = std::max(maxDer, arbol.root());
		min = std::min(minIz, arbol.root());
		return equilibrado & (minDer > arbol.root()) && (maxIz < arbol.root());
	}
}

int main() {
	int numVeces = 0;

	cin >> numVeces;

	for (int i = 0; i < numVeces; ++i) {
		bintree<int> arbol = leer(-1);
		int altura = 0, max = 0, min = 0;
		if (esAvl(arbol, altura, max, min)) cout << "SI\n";
		else cout << "NO\n";
	}


	return 0;
};