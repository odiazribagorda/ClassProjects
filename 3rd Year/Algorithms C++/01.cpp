// Oscar Diaz Ribagorda (DG04)

#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include "bintree_eda.h"

using namespace std;

bintree<char> leer(char parada) {
	char aux;
	cin >> aux;
	if (aux == parada) return {};
	else {
		auto iz = leer('.'),
			der = leer('.');
		return { iz, aux, der };
	}
}

bool equilibrado(bintree<char> const& arbol, int & altura) {
	if (arbol.empty()) {
		altura = 0;
		return true;
	}
	else {
		int alturaIz = 0, alturaDer = 0;
		bool equi = equilibrado(arbol.left(), alturaIz) &
					equilibrado(arbol.right(), alturaDer);
		altura = max(alturaIz, alturaDer) + 1;
		// Se comprueba aqui que el arbol sea equilibrado, porque si lo incluyo en el equi, no lo hace bien;
		return equi & abs((alturaIz - alturaDer)) <= 1;
	}
}

int main() {
	int numVeces = 0;

	cin >> numVeces;

	for (int i = 0; i < numVeces; ++i) {
		bintree<char> arbol = leer('.');
		int altura = 0;
		if (equilibrado(arbol, altura)) cout << "SI\n";
		else cout << "NO\n";
	}


	return 0;
};