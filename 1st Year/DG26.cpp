// DG05: Oscar Diaz Ribagorda.

#include <iostream>
#include <vector>

using namespace std;

void resolucion();

int main() {
	int numVeces = 0;

	cin >> numVeces;

	for (int i = 0; i < numVeces; ++i) resolucion();
	return 0;
}

void resolucion() {
	int suma = 0, pos = 0;
	size_t tam = 0;
	bool noPasa = true;

	cin >> tam;

	vector<int> v(tam);
	for (int & num : v) cin >> num;

	int j = tam - 1;

	while (j >= 0 && noPasa) {
		if (v.at(j) == suma) {
			pos = j;
			noPasa = false;
		}
		suma += v.at(j);
		--j;
	}
	if (noPasa) { cout << "NO\n"; noPasa = true; }

	else cout << pos << '\n';
}