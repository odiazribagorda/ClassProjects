// Oscar Diaz Ribagorda (DG05).

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool noesprimo(int numero) {
	bool noesprimo = false;
	int j = 1;
	int raiz = trunc(sqrt(numero));

	while (!noesprimo && j <= raiz) {
		if (numero % j == 0 && j != 1 && j != numero) noesprimo = true;
		++j;
	}

	return noesprimo;
}

int posprimerdivisor(int num, const vector<int> & primos) {
	int primerdivisor = 0, i = 0;;

	while (primerdivisor == 0) {
		if (num % primos[i] == 0) primerdivisor = primos[i];
		++i;
	}

	return i - 1;
}

const int MAX_NUM = 100000;

int main() {
	int num = 0;

	vector<int> primos;

	for (int i = 2; i < MAX_NUM; ++i) {
		if (!noesprimo(i)) primos.push_back(i);
	}
	
	cin >> num;

	while (num != 0) {
		if (noesprimo(num)) {
			int j = posprimerdivisor(num, primos);
			cout << primos[j];
			num /= primos[j];
			for (j + 1; j < num; ++j) {
				while (num != 0 && num % primos[j] == 0) {
					num /= primos[j];
					cout << ' ' << primos[j];
				}
			}
			cout << '\n';
		}
		else cout << num << '\n';
		
		cin >> num;
	}
	return 0;
}