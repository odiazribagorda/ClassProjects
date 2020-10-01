//DG05 Oscar Diaz Ribagorda

#include <iostream>

using namespace std;

int main() {
	int dividendo = 0, divisor = 0, resto = 0, numVeces = 0;

	cin >> numVeces;

	for (int i = 0; i < numVeces; ++i) {
		cin >> dividendo >> divisor;
		if (divisor > dividendo) {
			resto = dividendo; dividendo = divisor; divisor = resto;
		}

		while (divisor != 0) {
			resto = dividendo % divisor;
			dividendo = divisor;
			divisor = resto;
		}
		cout << dividendo << '\n';
	}
	return 0;
}