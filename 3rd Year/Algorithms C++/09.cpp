// Oscar Diaz Ribagorda (DG04)

#include <iostream>
#include "Grafo.h"

using namespace std;

void dfsModif(Grafo const& G, vector<bool> & marked, int & count, int v) {
	++count;
	marked[v] = true;
	for (auto w : G.adj(v)) {
		if (!marked[w]) {
			dfsModif(G, marked, count, w);
		}
	}
}

int main() {
	int numCasos = 0;
	cin >> numCasos;
	for (int i = 0; i < numCasos; ++i) {
		int numPersonas = 0, numAmistades = 0;
		cin >> numPersonas >> numAmistades;
		Grafo amigos(numPersonas);
		int a = 0, b = 0;
		for (int j = 0; j < numAmistades; ++j) {
			cin >> a >> b;
			amigos.ponArista(a - 1, b - 1);
		}


		vector<bool> marked(numPersonas);
		for (int j = 0; j < numPersonas; ++j) marked[j] = false;

		int count = 0, max = 0;
		for (int j = 0; j < numPersonas; ++j) {
			if (!marked[j]) {
				dfsModif(amigos, marked, count, j);
			}
			if (count > max) max = count;
			count = 0;
		}

		cout << max << '\n';
	}

	return 0;
}