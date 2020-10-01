// DG05 Oscar Diaz Ribagorda

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int size = 201;

void cuantasModas(const vector<int> & v, vector<int> & modas, bool & hayModa) {
	int max = 0;

	for (int i = 0; i < size; ++i) {
		if (v[i] > max) {
			if (max != 0) hayModa = true;
			max = v[i];
			modas.clear();
			modas.push_back(i - 100);
		}
		else if (v[i] == max) {
			modas.push_back(i - 100);
		}
		else if (v[i] != 0) hayModa = true;
	}
}

void resolucion() {
	int num = 0, numModas = 0;
	bool hayModa = false;
	long long unsigned int tam = 0;
	vector<int> v(size, 0), modas;

	cin >> tam;
	for (long long unsigned int i = 0; i < tam; ++i) {
		cin >> num;
		num += 100;
		++v[num];
	}

	cuantasModas(v, modas, hayModa);

	numModas = modas.size();

	if (hayModa) {
		switch (numModas) {
		case 1: cout << "MODA " << modas[0] << '\n'; break;
		case 2: cout << "BIMODAL " << modas[0] << ' ' << modas[1] << '\n'; break;
		case 3: cout << "TRIMODAL " << modas[0] << ' ' << modas[1] << ' ' << modas[2] << '\n'; break;
		default: {
			cout << numModas << "-MODAL";
			for (int j = 0; j < numModas; ++j)
				cout << ' ' << modas[j];
			cout << '\n'; }
		}
	}
	else cout << "NO HAY MODA\n";
}

int main()
{
	int numCasos = 0;
	cin >> numCasos;
	for (int i = 0; i < numCasos; ++i) resolucion();
	return 0;
}