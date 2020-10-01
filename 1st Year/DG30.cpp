// Oscar Diaz Ribagorda (DG05).

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool noesprimo(int numero) {
	bool noesprimo = false;
	int raiz = trunc(sqrt(numero)), j = 1;

	while (!noesprimo && j <= raiz) {
		if (numero % j == 0 && j != 1 && j != numero) noesprimo = true;
		++j;
	}

	return noesprimo;
}

int main() {
	int num = 0;

	cin >> num;

	vector<bool> numeros(num + 1, true);

	for (int i = 2; i <= num; ++i) {
		if (noesprimo(i)) numeros[i] = false;
	}
	for (int j = 2; j <= num; ++j) {
		if (numeros[j]) cout << j << '\n';
	}

	return 0;
}