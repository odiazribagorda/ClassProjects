#include <iostream>
#include <vector>

using namespace std;

ostream & operator<<(ostream & archSal, vector<int> solucion) {
	archSal << solucion[0];
	for (int i = 1; i < solucion.size(); ++i)
		archSal << ' ' << solucion[i];
	return archSal;
}

int main() {
	vector<int> solucion;
	int numeros[2500];
	int numVeces = 0, n = 0, num = 0, max = 0;

	cin >> numVeces;

	for (int i = 0; i < numVeces; ++i) {
		cin >> n;
		for (int j = 0; j < 2500; ++j)
			numeros[j] = 0;

		for (int j = 0; j < ((2 * n) - 1) * n; ++j) {
			cin >> num;
			if (num > max) max = num;
			++numeros[num];
		}

		for (int j = 0; j <= max; ++j) {
			if (numeros[j] % 2 == 1)
				solucion.push_back(j);
		}

		cout << "Case #" << i + 1 << ": " << solucion << '\n';
		solucion.clear();
	}

	return 0;
}