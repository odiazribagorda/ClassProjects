// Oscar Diaz Ribagorda (DG04)

#include <iostream>
#include "PriorityQueue.h"

using namespace std;

void calcularSumaMinima(PriorityQueue<long long int> & pq, long long int & numFans) {
	long long int equipo1 = 0, equipo2 = 0;
	while (!pq.empty()) {
		pq.pop(equipo1);
		if (!pq.empty()) {
			pq.pop(equipo2);
			pq.push(equipo1 + equipo2);
			numFans += equipo1 + equipo2;
		}
	}
}

int main() {
	int numEquipos = 0;

	cin >> numEquipos;
	while (numEquipos != 0) {
		PriorityQueue<long long int> pq;
		long long int numFans = 0;
		for (int i = 0; i < numEquipos; ++i) {
			cin >> numFans;
			pq.push(numFans);
		}
		numFans = 0;
		calcularSumaMinima(pq, numFans);
		cout << numFans << '\n';
		cin >> numEquipos;
	}

}