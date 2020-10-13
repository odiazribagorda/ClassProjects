// Oscar Diaz Ribagorda (MARP04)

#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include "TreeMap_AVL(transformado).h"

using namespace std;

template <class T>
void leer(map<T, T> & arbol, int n) {
	T aux;
	for (int i = 0; i < n; ++i) {
		cin >> aux;
		arbol.insert(aux);
	}
}

template <class T>
void mostrar(queue<T> & lista) {
	if (!lista.empty())  {
		cout << lista.front();
		lista.pop();
	}
	while (!lista.empty()) {
		cout << ' ' << lista.front();
		lista.pop();
	}
}

int main() {
	int n = 0;
	cin >> n;
	while (n != 0) {
		map<int, int> arbol;
		leer(arbol, n);
		int c1, c2;
		cin >> c1 >> c2;

		queue<int> lista = arbol.sacarLista(c1, c2);
		mostrar(lista);
		cout << '\n';

		cin >> n;
	}


	return 0;
};