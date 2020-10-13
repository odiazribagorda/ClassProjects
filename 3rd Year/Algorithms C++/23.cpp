// Oscar Diaz Ribagorda (DG04)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int numCiudades = 0;
	while (cin >> numCiudades) {
		int numVictorias = 0;
		vector<int> atacantes(numCiudades);
		vector<int> defensores(numCiudades);
		for (int i = 0; i < numCiudades; ++i) cin >> atacantes[i];
		for (int i = 0; i < numCiudades; ++i) cin >> defensores[i];
		sort(atacantes.begin(), atacantes.end());
		sort(defensores.begin(), defensores.end());
		int i = 0, j = 0;
		while (j < numCiudades) {
			if (defensores[j] >= atacantes[i]) {
				++numVictorias;
				++i; ++j;
			}
			else ++j;
		}
		cout << numVictorias << '\n';
	}

	return 0;
}