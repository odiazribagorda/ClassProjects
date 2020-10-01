// Oscar Diaz Ribagorda DG05.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void resolucion() {
	vector<long int> lista;
	vector<int> resultados;
	long int num = 0, max = 0, min = 0;
	int cont = 0;

	cin >> num;
	while (num != -1) {
		lista.push_back(num);
		cin >> num;
	}

	cin >> min >> max;
	while (min != 0 || max != 0) {
		cont = 0;
		for (int i = 0; i < lista.size(); ++i) {
			if (lista[i] <= max && lista[i] >= min) ++cont;
		}
		resultados.push_back(cont);
		cin >> min >> max;
	}
	cout << resultados[0];
	for (int i = 1; i < resultados.size(); ++i) {
		cout << ' ' << resultados[i];
	}
	cout << '\n';
}

int main() {
	int numVeces = 0;

	cin >> numVeces;

	for (int i = 0; i < numVeces; ++i) resolucion();

	return 0;
}