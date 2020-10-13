// Oscar Diaz Ribagorda (DG04)

#include <iostream>
#include "PriorityQueue.h"

using namespace std;

struct Grupo {
	int numInst;
	int numPartituras;
};
bool operator>(Grupo const& g1, Grupo const& g2) {
	int ratio1 = g1.numInst / g1.numPartituras;
	if (g1.numInst % g1.numPartituras != 0) ++ratio1;
	int ratio2 = g2.numInst / g2.numPartituras;
	if (g2.numInst % g2.numPartituras != 0) ++ratio2;
	return  ratio1 > ratio2;
}


int main() {
	int numPartituras = 0, numInstrumentos = 0;
	while (cin >> numPartituras >> numInstrumentos) {
		PriorityQueue<Grupo, std::greater<Grupo>> grupos;
		Grupo grupo;
		for (int i = 0; i < numInstrumentos; ++i) {
			cin >> grupo.numInst;
			grupo.numPartituras = 1;
			grupos.push(grupo);
		}
		numPartituras -= numInstrumentos;
		while (numPartituras > 0) {
			grupos.pop(grupo);
			--numPartituras;
			++grupo.numPartituras;
			grupos.push(grupo);
		}
		grupo = grupos.top();
		int maxPartituras = grupo.numInst / grupo.numPartituras;
		if (grupo.numInst % grupo.numPartituras != 0) ++maxPartituras;
		cout << maxPartituras << '\n';
	}
	return 0;
}