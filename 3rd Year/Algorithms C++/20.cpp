// Oscar Diaz Ribagorda (DG04)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int numAgujeros = 0, tamParche = 0;
	while (cin >> numAgujeros >> tamParche) {
		int numParches = 0;
		int cubierto = 0;
		if (numAgujeros > 0) {
			int actual = 0, anterior = 0;
			cin >> actual;
			numParches = 1;
			cubierto = tamParche;
			for (int i = 1; i < numAgujeros; ++i) {
				anterior = actual;
				cin >> actual;
				cubierto -= (actual - anterior);
				if (cubierto < 0) {
					++numParches;
					cubierto = tamParche;
				}
			}
		}
		cout << numParches << '\n';
	}

	return 0;
}