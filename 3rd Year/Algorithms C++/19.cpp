// Oscar Diaz Ribagorda (DG04)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int numLibros = 0;
	while (cin >> numLibros) {
		vector<int> precios(numLibros);
		for (int i = 0; i < numLibros; ++i)	cin >> precios[i];
		sort(precios.begin(), precios.end());
		int descuento = 0;
		for (int i = numLibros - 3; i >= 0; i = i - 3) descuento += precios[i];
		cout << descuento << '\n';
	}

	return 0;
}