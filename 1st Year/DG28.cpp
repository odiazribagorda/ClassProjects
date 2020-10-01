// DG05 Oscar Diaz Ribagorda.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void calcularModa(vector<long long int> v, bool & hayModa, long long int & moda) {
	int cont = 1, max = 0;

	sort(v.begin(), v.end());
	for (int j = 0; j < v.size(); ++j) {
		while (j < v.size() - 1 && v[j] == v[j + 1]) {
			++cont;
			++j;
		}

		if (cont > max) {
			max = cont;
			moda = v[j];
			hayModa = true;
		}
		else if (cont == max) hayModa = false;

		cont = 1;
	}
	if (max == v.size()) hayModa = false;
}

void resolucion() {
	int tam = 0;
	long long int moda = 0;
	bool hayModa = true;

	cin >> tam;
	vector<long long int> v(tam);

	for (long long int & num : v) cin >> num;

	calcularModa(v, hayModa, moda);

	if (!hayModa) cout << "NO HAY MODA\n";
	else cout << "MODA " << moda << '\n';
}

int main() {
	int numVeces = 0;

	cin >> numVeces;

	for (int i = 0; i < numVeces; ++i) resolucion();

	return 0;
}